#ifndef DATA_ADJACENCY_GRAPH_H
#define DATA_ADJACENCY_GRAPH_H

/**
 * @file adjacency_graph.h
 * @author Edwin Solis (esolis6@gatech.edu)
 * @brief A type adjustable implementation of an adjacency list based directed graph
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ordered_map.h"

/**
 * @details Implementation
 * 
 * This adjacency graph is based on the adjacency list based directed graph with a few modification for cache friendliness
 * in at most two memory accesses.
 * 
 * The graph stores a continuous array of the following data struct:
 * struct adjacency_node {
 *     ordered_map_t edge_list;
 *     char data[];
 * };
 * 
 * where data are the bytes of the node data and edge_list is the list of edges where the connection is defined
 * as a directional arrow from the node owning the list to the node stored in the list of edges.
 * 
 * Each node has a unique id representing its position in the graph given by a uint32_t value.
 * 
 * The edge_list is an ordered map struct with the intend to access and search edge data in O(log N).
 * The key is the connected nodes' id and the value is the edge data.
 * 
 * The maximum number of valid nodes is given UINT32_MAX - 1.
 * 
 */

/**
 * @brief Struct representing an adjacency list directed graph
 * 
 * @var data_ pointer to the array of data.
 * @var capacity_ capacity of nodes that the graph should be able to store
 * @var nodes_ number of nodes currently stored
 * @var node_element_size_ size in bytes of the node's type
 * @var edge_element_size_ size in bytes of the edge's type
 */
typedef struct adjacency_graph_st
{
    void* data_;
    size_t capacity_;
    size_t nodes_;
    size_t node_element_size_;
    size_t edge_element_size_;
} adjacency_graph_t;

/**
 * @brief Value of an invalid node in a graph
 */
extern const uint32_t INVALID_ADJGRAPH_NODE;/* = UINT32_MAX; */

/**
 * @brief Create a adjacency_graph object with the given parameters
 * 
 * @param capacity initial capacity of nodes that the graph should be able store
 * @param node_element_size size in bytes of the node data to be stored
 * @param edge_element_size size in bytes of the edge data to be stored
 * @return adjacency_graph_t
 */
adjacency_graph_t create_adj_graph(size_t capacity, size_t node_element_size, size_t edge_element_size);

/**
 * @brief Destroys the given instance of the adjacency graph and releases its resources.
 * 
 * @param graph graph to be destroyed
 */
void destroy_adj_graph(adjacency_graph_t* graph);

/**
 * @brief Resizes the data buffer of the graph to the given capacity.
 * 
 * @param graph graph which buffer will be resized
 * @param capacity the new capacity
 */
void reserve_adj_graph(adjacency_graph_t* graph, size_t capacity);

/**
 * @brief Reuses a previously created adjacency graph and resets its parameters
 * 
 * @param graph graph to be reused
 * @param capacity the new desired capacity for the graph
 * @param node_element_size the new node data size in bytes
 * @param edge_element_size the new edge data size in bytes
 */
void reuse_adj_graph(adjacency_graph_t* graph, size_t capacity, size_t node_element_size, size_t edge_element_size);

/**
 * @brief Returns the next capacity for a resized buffer from a previous known capacity
 * 
 * @param current_capacity old capacity of the buffer
 * @return size_t new capacity of the buffer
 */
size_t next_adj_graph_capacity(size_t current_capacity);

/**
 * @brief Get the node id of the given node in the graph
 * 
 * @param graph graph where the node belongs to
 * @param node const pointer to the data of the node
 * @return uint32_t id of the passed node
 */
uint32_t get_node_id_adj(adjacency_graph_t* graph, const void* node);

/**
 * @brief Get the address of the node data in the adjacency graph
 * 
 * @param graph graph where the node will be retrieved
 * @param id the id of the node
 * @return void* pointer to the data
 */
void* get_node_adj_graph(const adjacency_graph_t* graph, uint32_t id);

/**
 * @brief Sets the value of the node with the given id
 * 
 * @param graph graph where the node data will be stored
 * @param id id of the node
 * @param data const pointer to the data to be stored
 */
void set_node_adj_graph(adjacency_graph_t* graph, uint32_t id, const void* data);

/**
 * @brief Creates a node in the adjacency graph with the given data and returns its id.
 * 
 * @param graph graph in which the node is added/created
 * @param node_data const pointer of the data to be stored in the node
 * @return uint32_t id of the added node
 */
uint32_t add_node_adj_graph(adjacency_graph_t* graph, const void* node_data);

/**
 * @brief Removes the node with the given id from the graph and returns its data.
 * 
 * @param graph graph from which the node will be removed
 * @param id id of the node to be removed
 * @param data pointer where the node's data will be copied to
 */
void extract_node_adj_graph(adjacency_graph_t* graph, uint32_t id, void* data);

/**
 * @brief Removes the node with the given id from the adjacency graph.
 * 
 * @param graph graph from which the node will be removed
 * @param id id of the node to be removed
 */
void delete_node_adj_agraph(adjacency_graph_t* graph, uint32_t id);

/**
 * @brief Get the list of edges with node with the given id as source.
 * 
 * @param graph graph from which the edges will be retrieved
 * @param id id of the source node of the edges
 * @return ordered_map_t* An ordered map with the connected nodes id as keys and edge data as values
 */
ordered_map_t* get_edgelist_adj_graph(const adjacency_graph_t* graph, uint32_t id);

/**
 * @brief Calculates the capacity for the edgelist of a newly created node.
 * 
 * @param nodes the current number of nodes in the graph.
 * @return size_t capacity for the list of edges.
 */
size_t edgelist_capacity_adj(size_t nodes);

/**
 * @brief Gets the address of the edge data of the given connection
 * 
 * @param graph graph from which the edge will be retrieved
 * @param source source node of the directed edge
 * @param destination destination node of the directed edge
 * @return void* pointer to the edge data
 */
void* get_edge_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination);

/**
 * @brief Set the data of the given edge
 * 
 * @param graph graph where the edge data will be stored
 * @param source id of the source node of the directed edge
 * @param destination id of the destination node of the directed edge
 * @param data const pointer of the data to be stored in the edge
 */
void set_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, const void* data);

/**
 * @brief Creates an edge in the adjacency graph from the given source node to the destination node
 *        and stores the data passed.
 * 
 * @param graph graph where the edge will be added
 * @param source id of the source node of the directed edge
 * @param destination id of the destination node of the directed edge
 * @param data const pointer of the data to be stored in the edge
 */
void add_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, const void* data);

/**
 * @brief Removes the edge between the given nodes from the adjacency graph and returns its data
 * 
 * @param graph graph from which the edge will be removed
 * @param source id of the source node of the directed edge
 * @param destination id of the destination node of the directed edge
 * @param data pointer where the data will be copied
 */
void extract_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination, void* data);

/**
 * @brief Removes the edge between the given nodes from the adjacency graph
 * 
 * @param graph graph from which the edge will be removed
 * @param source id of the source node of the directed edge
 * @param destination id of the destination node of the directed edge
 */
void delete_edge_adj_graph(adjacency_graph_t* graph, uint32_t source, uint32_t destination);

/**
 * @brief Creates an edge between all nodes (except the destination node) with each one as source and the given destination node
 *        initialized with the given data.
 * 
 * @param graph graph where the edges will be added
 * @param destination id of the destination node of the directed edges
 * @param data const pointer to the data to be stored in the edge
 */
void connect_allto_adj_graph(adjacency_graph_t* graph, uint32_t destination, const void* data);

/**
 * @brief Creates an edge between the given source node and all the nodes in the graph (except the source node) each one as
 *        destination nodes.
 * 
 * @param graph graph where the edges will be added
 * @param source id of the source node of the directed edges
 * @param data const pointer to the data to be stored in the edge
 */
void connect_allfrom_adj_graph(adjacency_graph_t* graph, uint32_t source, const void* data);

/**
 * @brief Removes all edges in the adjacency graph that have the given node as destination
 * 
 * @param graph graph from which the edges will be removed from
 * @param destination id of the destination node
 */
void disconnect_allto_adj_graph(adjacency_graph_t* graph, uint32_t destination);

/**
 * @brief Removes all edges in the adjacency graph that have the given node as source
 * 
 * @param graph graph from which the edges will be removed from
 * @param source id of the source node
 */
void disconnect_allfrom_adj_graph(adjacency_graph_t* graph, uint32_t source);

/**
 * @brief Function signature of the function as predicate in the connect_if function
 *        It takes in the data of the source node and destination node
 *        Returns 1 if the nodes should be connected
 *        Returns 0 if the nodes should not be connected
 */
typedef int (*CONNECT_PREDICATE_FUNC)(const void* source_node_data, const void* dest_node_data);

/**
 * @brief Function signature of the function as predicate in the connect_if function
 *        It takes in the data of the source node, destination node, and their edge
 *        Returns 1 if the nodes should be disconnected
 *        Returns 0 if the nodes should not be disconnected
 */
typedef int (*DISCONNECT_PREDICATE_FUNC)(const void* source_node_data, const void* dest_node_data, const void* edge_data);

/**
 * @brief Creates an edge between all nodes (except the destination node) with each one as source and the given destination node
 *        initialized with the given data if they satisfy the predicate in each case.
 * 
 * @param graph graph where the edges will be added
 * @param destination id of the destination node of the directed edges
 * @param data const pointer to the data to be stored in the edge
 * @param predicate pointer to the function evaluating the connection
 */
void connect_allto_if_adj_graph(adjacency_graph_t* graph, uint32_t destination, const void* edge_data, CONNECT_PREDICATE_FUNC predicate);

/**
 * @brief Creates an edge between the given source node and all the nodes in the graph (except the source node) each one as
 *        destination nodes if they satisfy the predicate in each case.
 * 
 * @param graph graph where the edges will be added
 * @param source id of the source node of the directed edges
 * @param data const pointer to the data to be stored in the edge
 * @param predicate pointer to the function evaluating the connection
 */
void connect_allfrom_if_adj_graph(adjacency_graph_t* graph, uint32_t source, const void* edge_data, CONNECT_PREDICATE_FUNC predicate);

/**
 * @brief Removes all edges in the adjacency graph that have the given node as destination if they satisfy the predicate in each case.
 * 
 * @param graph graph from which the edges will be removed from
 * @param destination id of the destination node
 * @param predicate pointer to the function evaluating the disconnection
 */
void disconnect_allto_if_adj_graph(adjacency_graph_t* graph, uint32_t destination, DISCONNECT_PREDICATE_FUNC predicate);

/**
 * @brief Removes all edges in the adjacency graph that have the given node as source
 * 
 * @param graph graph from which the edges will be removed from
 * @param source id of the source node
 * @param predicate pointer to the function evaluating the disconnection
 */
void disconnect_allfrom_if_adj_graph(adjacency_graph_t* graph, uint32_t source, DISCONNECT_PREDICATE_FUNC predicate);

/**
 * @brief Function signature for the predicate function in search_node function.
 *        It takes in the data of the node
 *        Returns 1 if data in the node is a match
 *        Returns 0 if data in the node is not a match
 */
typedef int (*SEARCH_PREDICATE_FUNC)(const void* node_data);

/**
 * @brief Searches for the first node (in id order) that satisfies the given predicate and returns its id
 *        If no satisfying node is found, the function returns INVALID_ADJGRAPH_NODE
 * 
 * @param graph graph where the node will be search
 * @param predicate pointer to the function evaluating the search condition
 * @return uint32_t id of the found node
 */
uint32_t search_node_adj_graph(const adjacency_graph_t* graph, SEARCH_PREDICATE_FUNC predicate);

/**
 * @brief Finds the first node (in id order) in the graph that equals the given node
 *        If no satisfying node is found, the function returns INVALID_ADJGRAPH_NODE
 * @param graph graph where the node will be search
 * @param func pointer to the data equality function
 * @return uint32_t id of the found node
 */
uint32_t find_node_adj_graph(const adjacency_graph_t* graph, const void* node_data, EQUALS_FUNC func);

/**
 * @brief Returns if there is an edge between the two nodes.
 * 
 * @param graph graph where the nodes belong
 * @param source id of the source node of the directed edge
 * @param destination id of the destination of the directed edge
 * @return 1 if there is an edge, 0 if there is no edge
 */
int is_connected_to_adj(const adjacency_graph_t* graph, uint32_t source, uint32_t destination);

/**
 * @brief Returns if the given node id belongs to a valid node in the graph
 * 
 * @param graph graph where the node is verified in
 * @param id id of the node
 * @return 1 if valid, 0 if invalid
 */
int is_valid_node_adj(const adjacency_graph_t* graph, uint32_t id);

/**
 * @brief Comparison function for the keys in the edgelist (ordered_map)
 *        Returns 1 if left key < right key
 * 
 * @param left uint32_t id of the left
 * @param right uint32_t id of the right
 * @return int left < right
 */
int index_compare_func(const void* left, const void* right);

#endif /* DATA_ADJACENCY_GRAPH_H */
