#include "graph_algorithm.h"

#include "stack.h"
#include "ordered_set.h"
#include "ordered_map.h"

#include <stdio.h>
#include <float.h>

matrix_t to_matrix_from_adj_graph(const adjacency_graph_t* graph, const void* no_connection_val)
{
    matrix_t out = create_matrix(graph->edge_element_size_, graph->nodes_, graph->nodes_, NULL);
    fill_matrix(&out, no_connection_val);

    for (size_t i = 0; i < graph->nodes_; ++i)
    {
        if (is_valid_node_adj(graph, i))
        {
            ordered_map_t* map = get_edgelist_adj_graph(graph, i);
            for (size_t j = 0; j < map->size_; ++j)
            {
                uint32_t dest = *(uint32_t*)get_key_ordered_map(map, j);
                set_element_matrix(&out, i, dest, get_edge_adj_graph(graph, i, dest));
            }
        }
    }

    return out;
}

array_list_t shortest_unweight_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination)
{
    array_list_t queue = create_array_list(graph->nodes_, sizeof(uint32_t));
    ordered_set_t visited = create_ordered_set(graph->nodes_, sizeof(uint32_t), index_compare_func);
    array_list_t previous = create_array_list(graph->nodes_, sizeof(uint32_t));

    resize_array_list(&previous, graph->nodes_);
    fill_array_list(&previous, &INVALID_ADJGRAPH_NODE);
    push_front_array_list(&queue, &source);
    insert_element_ordered_set(&visited, &source);
    while (queue.size_ != 0)
    {
        uint32_t current_node;
        pop_back_array_list(&queue, &current_node);

        if (current_node == destination)
            break;

        ordered_map_t* edge_list = get_edgelist_adj_graph(graph, current_node);
        for (size_t i = 0; i < edge_list->size_; ++i)
        {
            uint32_t adjacent_node = *(uint32_t*)get_key_ordered_map(edge_list, i);

            if (!contains_ordered_set(&visited, &adjacent_node))
            {
                push_front_array_list(&queue, &adjacent_node);
                set_element_array_list(&previous, adjacent_node, &current_node);
                insert_element_ordered_set(&visited, &adjacent_node);
            }
        }
    }

    if (*(uint32_t*)get_element_array_list(&previous, destination) != INVALID_ADJGRAPH_NODE)
    {
        reuse_array_list(&queue, graph->nodes_, sizeof(uint32_t));
        uint32_t current = destination;
        while (current != source)
        {
            push_front_array_list(&queue, &current);
            current = *(uint32_t*)get_element_array_list(&previous, current);
        }
        push_front_array_list(&queue, &source);
    }
    else
    {
        destroy_array_list(&queue);
    }

    destroy_ordered_set(&visited);
    destroy_array_list(&previous);

    return queue;
}

array_list_t shortest_adj_graph(const adjacency_graph_t* graph, uint32_t source, uint32_t destination, EDGE_TO_WEIGHT_FUNC weight_func)
{
    ordered_set_t visited = create_ordered_set(graph->nodes_, sizeof(uint32_t), index_compare_func);//create_int_oset(node_count);
    array_list_t distances = create_array_list(graph->nodes_, sizeof(double));//vector_t distances = create_int_vector(node_count, NULL);

    resize_array_list(&distances, graph->nodes_);

    const double inf = DBL_MAX;
    const double zero = 0.0;
    fill_array_list(&distances, &inf);
    set_element_array_list(&distances, source, &zero);

    uint32_t current_node = source;
    while (!contains_ordered_set(&visited, &destination))
    {
        double current_distance = *(double*)get_element_array_list(&distances, current_node);//int current_distance = get_int_vector(&distances, current_node);
        double smallest_node = current_node;
        double smallest_dist = inf;

        ordered_map_t* edge_list = get_edgelist_adj_graph(graph, current_node);

        for (size_t i = 0; i < edge_list->size_; ++i)
        {
            uint32_t adjacent_node = *(uint32_t*)get_key_ordered_map(edge_list, i);
            //if (i == current_node) continue;
            if (contains_ordered_set(&visited, &adjacent_node)) continue;
            double node_weight = weight_func(get_edge_adj_graph(graph, current_node, adjacent_node));//get_int_matrix(matrix, current_node, i);
            //if (node_weight == 0) continue;

            double node_distance = *(double*)get_element_array_list(&distances, adjacent_node);//int node_distance = get_int_vector(&distances, i);

            double new_distance = current_distance + node_weight;
            if (new_distance < node_distance)
                set_element_array_list(&distances, adjacent_node, &new_distance);//set_int_vector(&distances, i, new_distance);

            double dist = *(double*)get_element_array_list(&distances, adjacent_node);
            if (smallest_dist > dist)//if (smallest_dist > get_int_vector(&distances, i))
            {
                smallest_dist = dist;//smallest_dist = get_int_vector(&distances, i);
                smallest_node = adjacent_node;//smallest_node = i;
            }
        }

        if (smallest_dist == inf)
            break;
        insert_element_ordered_set(&visited, &current_node);
        current_node = smallest_node;
    }

    destroy_ordered_set(&visited);

    return distances;
}

uint32_t breadthsearch_for_adj_graph(const adjacency_graph_t* graph, uint32_t source, SEARCH_PREDICATE_FUNC predicate)
{
    array_list_t queue = create_array_list(graph->nodes_, sizeof(uint32_t));
    ordered_set_t visited = create_ordered_set(graph->nodes_, sizeof(uint32_t), index_compare_func);
    uint32_t out = INVALID_ADJGRAPH_NODE;

    push_front_array_list(&queue, &source);
    insert_element_ordered_set(&visited, &source);

    while (queue.size_ != 0)
    {
        uint32_t current_node;
        pop_back_array_list(&queue, &current_node);

        if (predicate(get_node_adj_graph(graph, current_node)))
        {
            out = current_node;
            break;
        }

        ordered_map_t* edge_list = get_edgelist_adj_graph(graph, current_node);
        for (size_t i = 0; i < edge_list->size_; ++i)
        {
            uint32_t adjacent_node = *(uint32_t*)get_key_ordered_map(edge_list, i);

            if (!contains_ordered_set(&visited, &adjacent_node))
            {
                push_front_array_list(&queue, &adjacent_node);
                insert_element_ordered_set(&visited, &adjacent_node);
            }
        }
    }

    destroy_array_list(&queue);
    destroy_ordered_set(&visited);

    return out;
}

uint32_t depthsearch_for_adj_graph(const adjacency_graph_t* graph, uint32_t source, SEARCH_PREDICATE_FUNC predicate)
{
    array_stack_t stack = create_astack(graph->nodes_, sizeof(uint32_t));
    ordered_set_t visited = create_ordered_set(graph->nodes_, sizeof(uint32_t), index_compare_func);
    uint32_t out = INVALID_ADJGRAPH_NODE;

    push_astack(&stack, &source);
    insert_element_ordered_set(&visited, &source);

    while (stack.size_ != 0)
    {
        uint32_t current_node;
        pop_astack(&stack, &current_node);

        if (predicate(get_node_adj_graph(graph, current_node)))
        {
            out = current_node;
            break;
        }

        ordered_map_t* edge_list = get_edgelist_adj_graph(graph, current_node);

        for (size_t i = edge_list->size_; i > 0; --i)
        {
            uint32_t adjacent_node = *(uint32_t*)get_key_ordered_map(edge_list, i - 1);

            if (!contains_ordered_set(&visited, &adjacent_node))
            {
                push_astack(&stack, &adjacent_node);
                insert_element_ordered_set(&visited, &adjacent_node);
            }
        }
    }

    destroy_astack(&stack);
    destroy_ordered_set(&visited);

    return out;
}