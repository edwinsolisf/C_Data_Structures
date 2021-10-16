#include "adjacency_graph.h"

#include <string.h>

static const size_t BASE_CAPACITY = 8;

const uint32_t INVALID_ADJGRAPH_NODE = UINT32_MAX;

adjacency_graph_t create_adj_graph(size_t capacity, size_t node_element_size, size_t edge_element_size)
{
    adjacency_graph_t out;

    out.node_element_size_ = node_element_size;
    out.edge_element_size_ = edge_element_size;
    out.capacity_ = capacity;
    out.nodes_ = 0;
    out.data_ = malloc((node_element_size + sizeof(ordered_map_t)) * capacity);

    return out;
}

void destroy_adj_graph(adjacency_graph_t* graph)
{
    for (size_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i))
            destroy_ordered_map(get_edgelist_adj_graph(graph, i));
    }
    graph->nodes_ = 0;
    graph->capacity_ = 0;
    graph->node_element_size_ = 0;
    graph->edge_element_size_ = 0;
    free(graph->data_);
    graph->data_ = NULL;
}

void reserve_adj_graph(adjacency_graph_t* graph, size_t capacity)
{
    if (capacity > graph->capacity_)
    {
        graph->data_ = realloc(graph->data_, (graph->node_element_size_ + sizeof(ordered_map_t)) * capacity);
        graph->capacity_ = capacity;
    }
}

void reuse_adj_graph(adjacency_graph_t* graph, size_t capacity, size_t node_element_size, size_t edge_element_size)
{
    if ((node_element_size + sizeof(ordered_map_t)) * capacity > (graph->node_element_size_ + sizeof(ordered_map_t)) * graph->capacity_)
    {
        graph->data_ = realloc(graph->data_, (node_element_size + sizeof(ordered_map_t)) * capacity);
        graph->capacity_ = capacity;
    }
    else
    {
        graph->capacity_ = ((graph->node_element_size_ + sizeof(ordered_map_t)) * graph->capacity_) / (node_element_size + sizeof(ordered_map_t));
    }

    for (size_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i))
            reuse_ordered_map(get_edgelist_adj_graph(graph, i), sizeof(uint32_t), edge_element_size, 1, index_compare_func);
    }

    graph->nodes_ = 0;
    graph->node_element_size_ = node_element_size;
    graph->edge_element_size_ = edge_element_size;
}

size_t next_adj_graph_capacity(size_t current_capacity)
{
    return current_capacity ? current_capacity * 2 : BASE_CAPACITY;
}

uint32_t get_node_id_adj(adjacency_graph_t* graph, const void* node)
{
    return ((uintptr_t)node - (uintptr_t)graph->data_) / (graph->node_element_size_ + sizeof(ordered_map_t));
}

void* get_node_adj_graph(const adjacency_graph_t* graph, uint32_t id)
{
    return (void*)get_edgelist_adj_graph(graph, id) + sizeof(ordered_map_t);
}

void set_node_adj_graph(adjacency_graph_t* graph, uint32_t id, const void* data)
{
    memcpy(get_node_adj_graph(graph, id), data, graph->node_element_size_);
}

int index_compare_func(const void* left, const void* right)
{
    return *(const uint32_t*)left < *(const uint32_t*)right;
}

uint32_t add_node_adj_graph(adjacency_graph_t* graph, const void* node_data)
{
    if (graph->nodes_ == graph->capacity_)
        reserve_adj_graph(graph, next_adj_graph_capacity(graph->capacity_));

    ordered_map_t* edge_list = get_edgelist_adj_graph(graph, graph->nodes_);
    *edge_list = create_ordered_map(sizeof(uint32_t), graph->edge_element_size_, edgelist_capacity_adj(graph->nodes_), index_compare_func);
    memcpy((void*)edge_list + sizeof(ordered_map_t), node_data, graph->node_element_size_);

    return graph->nodes_++;
}

ordered_map_t* get_edgelist_adj_graph(const adjacency_graph_t* graph, uint32_t id)
{
    return graph->data_ + ((graph->node_element_size_ + sizeof(ordered_map_t)) * id);
}

static size_t great_bit(size_t val)
{
    size_t count = 0;
    while (val)
    {
        val = val >> 1;
        ++count;
    }
    return count;
}

size_t edgelist_capacity_adj(size_t nodes)
{
    return nodes < BASE_CAPACITY ? BASE_CAPACITY : (BASE_CAPACITY + great_bit(nodes - BASE_CAPACITY));
}

void extract_node_adj_graph(adjacency_graph_t* graph, uint32_t id, void* data)
{
    memcpy(data, get_node_adj_graph(graph, id), graph->node_element_size_);
    destroy_ordered_map(get_edgelist_adj_graph(graph, id));
}

void delete_node_adj_agraph(adjacency_graph_t* graph, uint32_t id)
{
    disconnect_allto_adj_graph(graph, id);
    destroy_ordered_map(get_edgelist_adj_graph(graph, id));
    //memset(get_node_adj_graph(graph, id), 0, graph->node_element_size_);
    //--graph->nodes_;
}

void* get_edge_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination)
{
    return get_ordered_map(get_edgelist_adj_graph(graph, source), &destination);
}

void set_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, const void* data)
{
    set_ordered_map(get_edgelist_adj_graph(graph, source), &destination, data);
}

void add_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, const void* data)
{
    insert_pair_ordered_map(get_edgelist_adj_graph(graph, source), &destination, data);
}

void extract_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, void* data)
{
    extract_pair_ordered_map(get_edgelist_adj_graph(graph, source), &destination, data);
}

void delete_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination)
{
    remove_pair_ordered_map(get_edgelist_adj_graph(graph, source), &destination);
}

void connect_allto_adj_graph(adjacency_graph_t* graph, uint32_t destination, const void* data)
{
    for (uint32_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i) && i != destination)
            add_edge_adj_graph(graph, i, destination, data);
    }
}

void connect_allfrom_adj_graph(adjacency_graph_t* graph, uint32_t source, const void* data)
{
    for (uint32_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i) && i != source)
            add_edge_adj_graph(graph, source, i, data);
    }
}

void disconnect_allto_adj_graph(adjacency_graph_t* graph, uint32_t destination)
{
    for (uint32_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i))
        {
            ordered_map_t* edge_list = get_edgelist_adj_graph(graph, i);
            if (contains_ordered_map(edge_list, &destination))
                remove_pair_ordered_map(edge_list, &destination);
        }
    }
}

void disconnect_allfrom_adj_graph(adjacency_graph_t* graph, uint32_t source)
{
    ordered_map_t* edge_list = get_edgelist_adj_graph(graph, source);
    for (size_t i = 0; i < edge_list->size_; ++i)
    {
        uint32_t dest = *(uint32_t*)get_key_ordered_map(edge_list, i);
        remove_pair_ordered_map(edge_list, &dest);
    }
}

void connect_allto_if_adj_graph(adjacency_graph_t* graph, uint32_t destination, const void* edge_data, CONNECT_PREDICATE_FUNC predicate)
{
    const void* dest_node = get_node_adj_graph(graph, destination);
    for (uint32_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i) && i != destination && predicate(get_node_adj_graph(graph, i), dest_node))
            add_edge_adj_graph(graph, i, destination, edge_data);
    }
}

void connect_allfrom_if_adj_graph(adjacency_graph_t* graph, uint32_t source, const void* edge_data, CONNECT_PREDICATE_FUNC predicate)
{
    const void* source_node = get_node_adj_graph(graph, source);
    for (uint32_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i) && i != source && predicate(source_node, get_node_adj_graph(graph, i)))
            add_edge_adj_graph(graph, source, i, edge_data);
    }
}

void disconnect_allto_if_adj_graph(adjacency_graph_t* graph, uint32_t destination, DISCONNECT_PREDICATE_FUNC predicate)
{
    const void* dest_node = get_node_adj_graph(graph, destination);
    for (uint32_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i))
        {
            ordered_map_t* edge_list = get_edgelist_adj_graph(graph, i);
            if (contains_ordered_map(edge_list, &destination) &&
                predicate(get_node_adj_graph(graph, i), dest_node, get_edge_adj_graph(graph, i, destination)))
                remove_pair_ordered_map(edge_list, &destination);
        }
    }
}

void disconnect_allfrom_if_adj_graph(adjacency_graph_t* graph, uint32_t source, DISCONNECT_PREDICATE_FUNC predicate)
{
    ordered_map_t* edge_list = get_edgelist_adj_graph(graph, source);
    const void* source_node = get_node_adj_graph(graph, source);
    for (size_t i = 0; i < edge_list->size_; ++i)
    {
        uint32_t dest = *(uint32_t*)get_key_ordered_map(edge_list, i);
        if (predicate(source_node, get_node_adj_graph(graph, dest), get_edge_adj_graph(graph, source, dest)))
            remove_pair_ordered_map(edge_list, &dest);
    }
}

uint32_t search_node_adj_graph(const adjacency_graph_t* graph, SEARCH_PREDICATE_FUNC predicate)
{
    for (size_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i) && predicate(get_node_adj_graph(graph, i)))
            return i;
    }
    return INVALID_ADJGRAPH_NODE;
}

uint32_t find_node_adj_graph(const adjacency_graph_t* graph, const void* node_data, EQUALS_FUNC func)
{
    for (size_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i) && func(node_data, get_node_adj_graph(graph, i)))
            return i;
    }
    return INVALID_ADJGRAPH_NODE;
}

int is_connected_to_adj(const adjacency_graph_t* graph, uint32_t source, uint32_t destination)
{
    if (is_valid_node_adj(graph, source) && is_valid_node_adj(graph, destination))
    {
        ordered_map_t* map = get_edgelist_adj_graph(graph, source);
        return contains_ordered_map(map, &destination);
    }
    return 0;
}

int is_valid_node_adj(const adjacency_graph_t* graph, uint32_t id)
{
    if (id < graph->nodes_)
    {
        ordered_map_t* edge_list = get_edgelist_adj_graph(graph, id);
        return edge_list->capacity_ != 0;
    }
    return 0;
}