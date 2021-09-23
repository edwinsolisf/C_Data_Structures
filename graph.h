#ifndef DATA_GRAPH_H
#define DATA_GRAPH_H

#include <stdio.h>

typedef struct data_array_graph_st
{
    size_t total_nodes_;
    size_t total_edges_;
    size_t element_size_;
    size_t capacity_;
    void* data_;
    int directed_;
} array_graph_t;

array_graph_t create_agraph(size_t total_nodes, size_t element_size, int directed_graph);
void destroy_agraph(array_graph_t* graph);

void reuse_agraph(array_graph_t* graph, size_t total_nodes, size_t element_size, int directed_graph);
void resize_agraph(array_graph_t* graph, size_t total_nodes);
void reserve_agraph(array_graph_t* graph, size_t capacity);
size_t next_capacity_agraph(size_t current_capacity);

void set_edge_agraph(array_graph_t* graph, int source_node, int destination_node, const void* value);
void* get_edge_agraph(array_graph_t* graph, int source_node, int destination_node);

#endif /* DATA_GRAPH_H */
