#ifndef DATA_LINKED_LIST_H
#define DATA_LINKED_LIST_H

#include <stdlib.h>

typedef void* linked_list_node;
/*
struct linked_list_node
{
    void* next_;
    char data_[element_size_];
}
*/

typedef struct
{
    size_t element_size_;
    size_t size_;
    linked_list_node head_;
} linked_list;

linked_list create_linked_list(size_t element_size);
void destroy_linked_list(linked_list* list);
linked_list begin_linked_list(size_t element_size, linked_list_node head);
linked_list copy_linked_list(const linked_list* list);

linked_list_node create_linked_list_node(size_t element_size, const void* data, const linked_list_node next);
void destroy_linked_list_node(linked_list_node node);

linked_list_node get_linked_list_node(const linked_list* list, int node);
void* get_llist_node_data(const linked_list_node node);
void set_llist_node_data(linked_list_node node, size_t element_size, const void* data);
linked_list_node get_llist_node_next(const linked_list_node node);
void set_llist_node_next(linked_list_node node, const linked_list_node next);

void* get_element_linked_list(const linked_list* list, int node);
void set_element_linked_list(linked_list* list, int node, const void* data);

void push_linked_list(linked_list* list, const void* data);
void pop_linked_list(linked_list* list, void* data);
void insert_linked_list(linked_list* list, int node, const void* data);
void remove_linked_list(linked_list* list, int node, void* data);

#endif /* DATA_LINKED_LIST_H */