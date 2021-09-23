#include "linked_list.h"

#include <string.h>
#include <assert.h>

linked_list create_linked_list(size_t element_size)
{
    linked_list list;
    
    list.element_size_ = element_size;
    list.size_ = 0;
    list.head_ = NULL;

    return list;
}

void destroy_linked_list(linked_list* list)
{
    list->element_size_ = 0;
    list->size_ = 0;
    
    linked_list_node current = list->head_;
    while (current != NULL)
    {
        linked_list_node temp = get_llist_node_next(current);
        destroy_linked_list_node(current);
        current = temp;
    }
}

linked_list begin_linked_list(size_t element_size, linked_list_node head)
{
    linked_list out;
    out.element_size_ = element_size;
    out.head_ = head;

    int i = 0;
    linked_list_node current = head;
    while(current != NULL)
    {
        current = get_llist_node_next(current);
        ++i;
    }
    out.size_ = i;

    return out;
}

linked_list copy_linked_list(const linked_list* list)
{
    linked_list out;

    out.size_ = 0;
    out.element_size_ = list->element_size_;
    out.head_ = NULL;

    if (list->size_ == 0)
        out.head_ = NULL;
    else if (list->size_ == 1)
        out.head_ = create_linked_list_node(list->element_size_, get_llist_node_data(list->head_), NULL);
    else
    {
        linked_list_node current = list->head_;
        while (current != NULL)
        {
            push_linked_list(&out, get_llist_node_data(current));
            current = get_llist_node_next(current);
        }
        assert(list->size_ == out.size_);
    }

    return out;
}

linked_list_node create_linked_list_node(size_t element_size, const void* data, const linked_list_node next)
{
    linked_list_node node = malloc(sizeof(void*) + element_size);
    set_llist_node_next(node, next);
    set_llist_node_data(node, element_size, data);
    return node;
}

void destroy_linked_list_node(linked_list_node node)
{
    free(node);
}

linked_list_node get_linked_list_node(const linked_list* list, int node)
{
    if (node < 0 || node >= list->size_)
        return NULL;

    linked_list_node current = list->head_;

    for (int i = 0; i < node; ++i)
        current = get_llist_node_next(current);
    return current;
}

void* get_llist_node_data(const linked_list_node node)
{
    return node + sizeof(void*);
}

void set_llist_node_data(linked_list_node node, size_t element_size, const void* data)
{
    if (node == NULL)
        return;
    memcpy(get_llist_node_data(node), data, element_size);
}

linked_list_node get_llist_node_next(const linked_list_node node)
{
    return (linked_list_node)(uintptr_t)node;
}

void set_llist_node_next(linked_list_node node, const linked_list_node next)
{
    if (node == NULL)
        return;
    memcpy(get_llist_node_next(node), &next, sizeof(void*));
}

void* get_element_linked_list(const linked_list* list, int node)
{
    if (node >= list->size_)
        return NULL;

    return get_llist_node_data(get_linked_list_node(list, node));
}

void set_element_linked_list(linked_list* list, int node, const void* data)
{
    if (node >= list->size_)
        return;

    memcpy(get_llist_node_data(get_linked_list_node(list, node)), data, list->element_size_);
}

void push_linked_list(linked_list* list, const void* data)
{
    if (list->size_ == 0)
        list->head_ = create_linked_list_node(list->element_size_, data, NULL);
    else
    {
        linked_list_node last = get_linked_list_node(list, list->size_ - 1);
        set_llist_node_next(last, create_linked_list_node(list->element_size_, data, NULL));
    }
    ++list->size_;
}

void pop_linked_list(linked_list* list, void* data)
{
    if (list->size_ == 0)
        return;
    else if (list->size_ == 1)
    {
        memcpy(data, get_llist_node_data(list->head_), list->element_size_);
        destroy_linked_list_node(list->head_);
        list->head_ = NULL;
    }
    else
    {
        linked_list_node prev_last = get_linked_list_node(list, list->size_ - 2);
        memcpy(data, get_llist_node_data(prev_last), list->element_size_);
        destroy_linked_list_node(get_llist_node_next(prev_last));
        set_llist_node_next(prev_last, NULL);
    }
    --list->size_;
}

void insert_linked_list(linked_list* list, int node, const void* data)
{
    if (node > list->size_)
        return;
    
    if (node == 0)
        list->head_ = create_linked_list_node(list->element_size_, data, list->head_);
    else
    {
        linked_list_node prev = get_linked_list_node(list, node - 1);
        set_llist_node_next(prev, create_linked_list_node(list->element_size_, data, get_llist_node_next(prev)));
    }
    ++list->size_;
}

void remove_linked_list(linked_list* list, int node, void* data)
{
    if (node >= list->size_ || list->size_ == 0)
        return;

    if (list->size_ == 1)
    {
        memcpy(data, get_llist_node_data(list->head_), list->element_size_);
        destroy_linked_list_node(list->head_);
        list->head_ = NULL;
    }
    else
    {
        linked_list_node prev = get_linked_list_node(list, node - 1);
        linked_list_node rm = get_llist_node_next(prev);
        memcpy(data, rm, list->element_size_);
        set_llist_node_next(prev, get_llist_node_next(rm));
        destroy_linked_list_node(rm);
    }

    --list->size_;
}
