#include "graph.h"

#include <string.h>

array_graph_t create_agraph(size_t total_nodes, size_t element_size, int directed_graph)
{
    array_graph_t out;

    out.total_nodes_ = total_nodes;
    out.total_edges_ = 0;
    out.element_size_ = element_size;
    if (directed_graph)
        out.capacity_ = total_nodes * total_nodes;
    else
        out.capacity_ = total_nodes * total_nodes / 2;
    out.data_ = malloc(element_size * out.capacity_);
    out.directed_ = directed_graph;

    return out;
}

void destroy_agraph(array_graph_t* graph)
{
    graph->total_nodes_ = 0;
    graph->total_edges_ = 0;
    graph->element_size_ = 0;
    graph->capacity_ = 0;
    graph->directed_ = 0;
    free(graph->data_);
    graph->data_ = NULL;
}

void reuse_agraph(array_graph_t* graph, size_t total_nodes, size_t element_size, int directed_graph)
{
    int new_capacity = directed_graph ? (total_nodes * total_nodes) : (total_nodes * total_nodes / 2);
    if (new_capacity * element_size > graph->capacity_ * graph_->element_size_)
        resize_agraph(graph, total_nodes)
}

void reserve_agraph(array_graph_t* graph, size_t capacity)
{

}

void resize_agraph(array_graph_t* graph, size_t total_nodes)
{

}

size_t next_capacity_agraph(size_t current_capacity)
{

}

void set_edge_agraph(array_graph_t* graph, int source_node, int destination_node, const void* value)
{
    if (source_node < graph_->total_nodes_ && destination_node < graph->total_nodes_)
    {
        memcpy(get_edge_agraph(graph, source_node, destination_node), value, graph->element_size_);
    }
}

void* get_edge_agraph(array_graph_t* graph, int source_node, int destination_node)
{
    if (source_node >= graph_->total_nodes_ || destination_node >= graph->total_nodes_)
        return NULL;
    if (graph_->directed_)
    {
        return graph->data_ + (source_node * graph_->total_nodes + destination_node) * graph->element_size_;
    }
    else
    {
        return
    }
}
