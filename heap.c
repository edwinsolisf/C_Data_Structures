#include "heap.h"

heap create_heap(size_t initial_capacity, size_t element_size, LESS_THAN_FUNC less_than_func)
{
    heap out;

    out.tree_ = create_binary_tree(initial_capacity, element_size);
    out.order_func = less_than_func;

    return out;
}

heap copy_heap(const heap* heap_)
{
    heap out;

    out.tree_ = copy_binary_tree(&heap_->tree_);
    out.order_func = heap_->order_func;

    return out;
}

void destroy_heap(heap* heap_)
{
    destroy_binary_tree(&(heap_->tree_));
}

void reuse_heap(heap* heap_, size_t element_size)
{
    reuse_binary_tree(&(heap_->tree_), element_size);
}

void resize_heap(heap* heap_, size_t new_size)
{
    resize_binary_tree(&(heap_->tree_), new_size);
}

void reserve_heap(heap* heap_, size_t reserve_capacity)
{
    reserve_binary_tree(&(heap_->tree_), reserve_capacity);
}

void push_heap(heap* heap_, const void* data)
{
    binary_tree* tree = &(heap_->tree_);
    set_element_binary_tree(tree, tree->size_, data);

    heapify_up(heap_, tree->size_++);
}

void pop_last_heap(heap* heap_, void* data)
{
    pop_binary_tree(&heap_->tree_, --heap_->tree_.size_, data);
}

void pop_root_heap(heap* heap_, void* data)
{
    binary_tree* tree = &heap_->tree_;
    swap(get_element_heap(heap_, 0), get_element_heap(heap_, tree->size_ - 1), tree->element_size_);
    pop_binary_tree(tree, tree->size_ - 1, data);
    heapify_down(heap_, 0);
}

void* get_element_heap(const heap* heap_, int node)
{
    return get_element_binary_tree(&heap_->tree_, node);
}

const void* view_element_heap(const heap* heap_, int node)
{
    return NULL;
}

void set_element_heap(heap* heap_, int node, void* data)
{
    set_element_binary_tree(&heap_->tree_, node, data);
}

void heapify_down(heap* heap_, int node)
{
    int parent = node;
    void* parent_node = get_element_heap(heap_, parent);

    while (parent < heap_->tree_.size_)
    {
        int left_child = left_child_node_binary_tree(parent);
        int right_child = right_child_node_binary_tree(parent);

        if (left_child >= heap_->tree_.size_)
            break;

        void* left_node = get_element_heap(heap_, left_child);
        void* right_node = get_element_heap(heap_, right_child);

        if (heap_->order_func(left_node, parent_node) || heap_->order_func(right_node, parent_node))
        {
            if (right_child >= heap_->tree_.size_ || heap_->order_func(left_node, right_node))
            {
                swap(left_node, parent_node, heap_->tree_.element_size_);
                parent = left_child;
                parent_node = left_node;
            }
            else
            {
                swap(right_node, parent_node, heap_->tree_.element_size_);
                parent = right_child;
                parent_node = right_node;
            }
        }
        else
            break;
    }
}

void heapify_up(heap* heap_, int node)
{
    int child = node;
    void* child_node = get_element_heap(heap_, child);
    while (child != 0)
    {
        int parent = parent_node_binary_tree(child);
        void* parent_node = get_element_heap(heap_, parent);

        if (heap_->order_func(child_node, parent_node))
        {
            swap(child_node, parent_node, heap_->tree_.element_size_);
            child = parent;
            child_node = parent_node;
        }
        else
            break;
    }
}

int is_heap(const heap* heap_)
{
    for (int i = 0; i < heap_->tree_.size_; ++i)
    {
        int left = left_child_node_binary_tree(i);
        int right = right_child_node_binary_tree(i);

        if (heap_->order_func(get_element_heap(heap_, left), get_element_heap(heap_, i))
            || heap_->order_func(get_element_heap(heap_, right), get_element_heap(heap_, i)))
        {
            if (left < heap_->tree_.size_ && right < heap_->tree_.size_)
                return 0;
        }
    }
    return 1;
}