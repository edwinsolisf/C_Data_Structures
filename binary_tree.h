#ifndef DATA_BINARY_TREE
#define DATA_BINARY_TREE

#include <stdlib.h>

typedef struct data_binary_tree_st
{
    void* data_;
    long* meta_data_;
    size_t capacity_;
    size_t size_;
    size_t element_size_;
} binary_tree;

binary_tree create_binary_tree(size_t initial_capacity, size_t element_size);
binary_tree copy_binary_tree(const binary_tree* tree);
void destroy_binary_tree(binary_tree* tree);
void reuse_binary_tree(binary_tree* tree, size_t element_size);
void resize_binary_tree(binary_tree* tree, size_t new_size);
void reserve_binary_tree(binary_tree* tree, size_t reserve_capacity);

size_t next_capacity_binary_tree(size_t current_capacity);

int node_is_free(const binary_tree* tree, int node);
void node_occupate(binary_tree* tree, int node);
void node_free(binary_tree* tree, int node);

void push_binary_tree(binary_tree* tree, int node, const void* data);
void push_root_binary_tree(binary_tree* tree, const void* data);
void push_last_binary_tree(binary_tree* tree, const void* data);

void pop_binary_tree(binary_tree* tree, int node, void* data);
void pop_root_binary_tree(binary_tree* tree, void* data);
void pop_last_binary_tree(binary_tree* tree, void* data);

void* get_element_binary_tree(const binary_tree* tree, int node);
void set_element_binary_tree(binary_tree* tree, int node, const void* data);

int left_child_node_binary_tree(int parent_node);
int right_child_node_binary_tree(int parent_node);
int parent_node_binary_tree(int child_node);

void swap(void* left, void* right, size_t elem_size);
//void print_binary_tree_info(const binary_tree* tree);

#endif /* DATA_BINARY_TREE */