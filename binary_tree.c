#include "binary_tree.h"

#include <string.h>

static const int BASE_CAPACITY_BINARY_TREE = 8;

binary_tree create_binary_tree(size_t initial_capacity, size_t element_size)
{
    binary_tree out;
    
    out.capacity_ = initial_capacity != 0 ? initial_capacity : BASE_CAPACITY_BINARY_TREE;
    out.size_ = 0;
    out.element_size_ = element_size;
    out.data_ = malloc(out.capacity_ * out.element_size_);

    out.meta_data_ = (long*)malloc((out.capacity_ / (sizeof(long) * 8) + 1) * sizeof(long));
    memset(out.meta_data_, 0, (out.capacity_ / (sizeof(long) * 8) + 1) * sizeof(long));

    return out;
}

binary_tree copy_binary_tree(const binary_tree* tree)
{
    binary_tree out;

    out.capacity_ = tree->capacity_;
    out.size_ = tree->size_;
    out.element_size_ = tree->element_size_;

    out.data_ = malloc(tree->capacity_ * tree->element_size_);
    memcpy(out.data_, tree->data_, tree->size_ * tree->element_size_);

    out.meta_data_ = (long*)malloc((tree->capacity_ / (sizeof(long) * 8) + 1) * sizeof(long));
    memcpy(out.meta_data_, tree->meta_data_, (tree->capacity_ / (sizeof(long) * 8) + 1) * sizeof(long));

    return out;
}

void destroy_binary_tree(binary_tree* tree)
{
    free(tree->data_);
    tree->data_ = NULL;

    free(tree->meta_data_);
    tree->meta_data_ = NULL;

    tree->capacity_ = 0;
    tree->size_ = 0;
    tree->element_size_ = 0;
}

void reuse_binary_tree(binary_tree* tree, size_t element_size)
{
    tree->size_ = 0;
    tree->capacity_ = (tree->element_size_ * tree->capacity_) / element_size;
    tree->element_size_ = element_size;

    memset(tree->meta_data_, 0, (tree->capacity_ / (sizeof(long) * 8) + 1) * sizeof(long));
}

void resize_binary_tree(binary_tree* tree, size_t new_size)
{
    if (new_size > tree->capacity_)
        reserve_binary_tree(tree, next_capacity_binary_tree(tree->capacity_));
    tree->size_ = new_size;
}

void reserve_binary_tree(binary_tree* tree, size_t reserve_capacity)
{
    if (reserve_capacity > tree->capacity_)
    {
        void* new_data = realloc(tree->data_, reserve_capacity * tree->element_size_);
        tree->data_ = new_data;

        if (((tree->capacity_ / (sizeof(long) * 8) + 1) * sizeof(long) * 8) < reserve_capacity)
        {
            long* new_meta_data = (long*)realloc(tree->meta_data_, (reserve_capacity / (sizeof(long) * 8) + 1) * sizeof(long));
            tree->meta_data_ = new_meta_data;
            
            memset(tree->meta_data_ + (tree->capacity_ / (sizeof(long) * 8)) , 0, 
                ((reserve_capacity - tree->capacity_) / (sizeof(long) * 8)) * sizeof(long));
        }
        tree->capacity_ = reserve_capacity;
    }
}

size_t next_capacity_binary_tree(size_t current_capacity)
{
    return current_capacity != 0 ? current_capacity * 2 : BASE_CAPACITY_BINARY_TREE;
}

int node_is_free(const binary_tree* tree, int node)
{
    return !(tree->meta_data_[node / (sizeof(long) * 8)] & (1L << (node % (sizeof(long) * 8))));
}

void node_occupate(binary_tree* tree, int node)
{
    tree->meta_data_[node / (sizeof(long) * 8)] |= (1L << (node % (sizeof(long) * 8)));
}

void node_free(binary_tree* tree, int node)
{
    tree->meta_data_[node / (sizeof(long) * 8)] &= ~(1L << (node % (sizeof(long) * 8)));
}

void push_binary_tree(binary_tree* tree, int node, const void* data)
{
    if (node_is_free(tree, node) && !node_is_free(tree, parent_node_binary_tree(node)))
        set_element_binary_tree(tree, node, data);
}

void push_root_binary_tree(binary_tree* tree, const void* data)
{

}

void push_last_binary_tree(binary_tree* tree, const void* data)
{
    if (tree->size_ == tree->capacity_)
        reserve_binary_tree(tree, next_capacity_binary_tree(tree->capacity_));

    int index = 0;
    while (1)
    {
        if (node_is_free(tree, index))
        {
            set_element_binary_tree(tree, index, data);
            ++(tree->size_);
            return;
        }

        ++index;
    }
}

void pop_binary_tree(binary_tree* tree, int node, void* data)
{
    if (!node_is_free(tree, node))
    {
        void* node_data = get_element_binary_tree(tree, node);
        memcpy(data, node_data, tree->element_size_);
        node_free(tree, node);
        //memset(node_data, 0, tree->element_size_);
        --tree->size_;
    }
}

void pop_root_binary_tree(binary_tree* tree, void* data)
{

}

void pop_last_binary_tree(binary_tree* tree, void* data)
{

}

void* get_element_binary_tree(const binary_tree* tree, int node)
{
    return tree->data_ + (node * tree->element_size_);
}

void set_element_binary_tree(binary_tree* tree, int node, const void* data)
{
    if (node >= tree->capacity_ || tree->size_ == tree->capacity_)
        reserve_binary_tree(tree, next_capacity_binary_tree(tree->capacity_));
    memcpy(tree->data_ + (node * tree->element_size_), data, tree->element_size_);
    node_occupate(tree, node);
}

int left_child_node_binary_tree(int parent_node)
{
    return parent_node >= 0 ? (parent_node * 2 + 1): -1;
}

int right_child_node_binary_tree(int parent_node)
{
    return parent_node >= 0 ? (parent_node * 2 + 2): -1;
}

int parent_node_binary_tree(int child_node)
{
    return child_node > 0 ? ((child_node - 1) / 2): -1;
}

void swap(void* left, void* right, size_t elem_size)
{
    void* temp = alloca(elem_size);
    //void* temp = malloc(elem_size);
    memcpy(temp, left, elem_size);
    memcpy(left, right, elem_size);
    memcpy(right, temp, elem_size);
    //free(temp);
}