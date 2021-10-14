#ifndef DATA_ADJACENCY_GRAPH_H
#define DATA_ADJACENCY_GRAPH_H

#include "matrix.h"
#include "array_list.h"
#include "ordered_map.h"

typedef struct adjacency_graph_st
{
    void* data_;
    size_t capacity_;
    size_t nodes_;
    size_t node_element_size_;
    size_t edge_element_size_;
} adjacency_graph_t;

/*struct adjacency_node
{
    ordered_map_t edges_;
    char data[];
}; */

adjacency_graph_t create_adj_graph(size_t capacity, size_t node_element_size, size_t edge_element_size);
void destroy_adj_graph(adjacency_graph_t* graph);

void reserve_adj_graph(adjacency_graph_t* graph, size_t capacity);
//void reuse_adj_graph(adjacency_graph_t* graph, size_t capacity, size_t node_element_size, size_t edge_element_size);

size_t next_adj_graph_capacity(size_t current_capacity);

uint32_t get_node_id_adj(adjacency_graph_t* graph, const void* node);
void* get_node_adj_graph(const adjacency_graph_t* graph, uint32_t id);
void set_node_adj_graph(adjacency_graph_t* graph, uint32_t id, const void* data);
uint32_t add_node_adj_graph(adjacency_graph_t* graph, const void* node_data);
void extract_node_adj_graph(adjacency_graph_t* graph, uint32_t id, void* data);
void delete_node_adj_agraph(adjacency_graph_t* graph, uint32_t id);

ordered_map_t* get_edgelist_adj_graph(const adjacency_graph_t* graph, uint32_t id);
size_t edgelist_capacity_adj(size_t nodes);

void* get_edge_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination);
void set_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, const void* data);
void add_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, const void* data);
void extract_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, void* data);
void delete_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination);

void connect_allto_adj_graph(adjacency_graph_t* graph, uint32_t destination, const void* data);
void connect_allfrom_adj_graph(adjacency_graph_t* graph, uint32_t source, const void* data);
void disconnect_allto_adj_graph(adjacency_graph_t* graph, uint32_t destination);
void disconnect_allfrom_adj_graph(adjacency_graph_t* graph, uint32_t source);

typedef int (*CONNECT_PREDICATE_FUNC)(const void* node_data);
typedef int (*DISCONNECT_PREDICATE_FUNC)(const void* node_data, const void* edge_data);

void connect_allto_if_adj_graph(adjacency_graph_t* graph, uint32_t destination, const void* data, CONNECT_PREDICATE_FUNC predicate);
void connect_allfrom_if_adj_graph(adjacency_graph_t* graph, uint32_t source, const void* data, CONNECT_PREDICATE_FUNC predicate);
void disconnect_allto_if_adj_graph(adjacency_graph_t* graph, uint32_t destination, DISCONNECT_PREDICATE_FUNC predicate);
void disconnect_allfrom_if_adj_graph(adjacency_graph_t* graph, uint32_t source, DISCONNECT_PREDICATE_FUNC predicate);

typedef int (*SEARCH_PREDICATE_FUNC)(const void* node_data);

// array_list_t breadthsearch_for_adj_graph(adjacency_graph_t* graph, uint32_t source, SEARCH_PREDICATE_FUNC predicate);
// array_list_t depthsearch_for_adj_graph(adjacency_graph_t* graph, uint32_t source, SEARCH_PREDICATE_FUNC predicate);

matrix_t to_matrix_from_adj_graph(const adjacency_graph_t* graph, const void* no_connection_val);

int is_connected_to_adj(const adjacency_graph_t* graph, uint32_t source, uint32_t destination);
int is_valid_node_adj(const adjacency_graph_t* graph, uint32_t id);

#endif /* DATA_ADJACENCY_GRAPH_H */
