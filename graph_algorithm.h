#ifndef DATA_GRAPH_ALGORITHM_H
#define DATA_GRAPH_ALGORITHM_H

/**
 * @file graph_algorithm.h
 * @author Edwin Solis (esolis6@gatech.edu)
 * @brief Implementation of useful algorithm for graphs
 * @version 0.1
 * @date 2021-10-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "adjacency_graph.h"
#include "array_list.h"
#include "matrix.h"

/**
 * @brief Function signature used to determine the shortest unweighted path
 *        Takes in the edge data
 *        Returns a double value representing the weight of the edge in the graph
 */
typedef double (*EDGE_TO_WEIGHT_FUNC)(const void* edge);

/**
 * @brief Transform the given adjacency list graph to a adjacency matrix graph using the given edges.
 * 
 * @param graph graph to be transformed
 * @param no_connection_val value of edges where no connection exists
 * @return matrix_t representation of the graph
 */
matrix_t to_matrix_from_adj_graph(const adjacency_graph_t* graph, const void* no_connection_val);

/**
 * @brief Traverses the graph in breath first search fashion until a node that satisfies the predicate is found.
 *        If no node is found, it returns INVALID_ADJGRAPH_NODE
 * @param graph graph to be search in
 * @param source id of the node where the search starts
 * @param predicate pointer to the function evaluating the search condition
 * @return uint32_t id of the found node
 */
uint32_t breadthsearch_for_adj_graph(const adjacency_graph_t* graph, uint32_t source, SEARCH_PREDICATE_FUNC predicate);

/**
 * @brief Traverses the graph in depth first search fashion until a node that satisfies the predicate is found.
 *        If no node is found, it returns INVALID_ADJGRAPH_NODE
 * @param graph graph to be search in
 * @param source id of the node where the search starts
 * @param predicate pointer to the function evaluating the search condition
 * @return uint32_t id of the found node
 */
uint32_t depthsearch_for_adj_graph(const adjacency_graph_t* graph, uint32_t source, SEARCH_PREDICATE_FUNC predicate);

/**
 * @brief Returns a list with the shortest weighted path between the given source and destination nodes.
 *        The list includes the id of the nodes to be traveled through (including the source and destination).
 * 
 * @param graph graph to be traversed
 * @param source id of the source node
 * @param destination id of the destination node
 * @param weight_func pointer to the function transforming the edge data to weighted double values
 * @return array_list_t list with the path
 */
array_list_t shortest_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination, EDGE_TO_WEIGHT_FUNC weight_func);

/**
 * @brief Returns a list with the shortest unweighted (connection) path between the given source and destination nodes.
 *        The list includes the id of the nodes to be traveled through (including the source and destination).
 * 
 * @param graph graph to be traversed
 * @param source id of the source node
 * @param destination id of the destination node
 * @return array_list_t list with the path
 */
array_list_t shortest_unweight_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination);

#endif /* DATA_GRAPH_ALGORITHM_H */