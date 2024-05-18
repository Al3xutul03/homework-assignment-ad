#ifndef CODE_DOUBLY_LINKED_LISTS_H
#define CODE_DOUBLY_LINKED_LISTS_H

#include <stdio.h>

// Struct for the book array
struct doubly_node{
    long long int info;
    unsigned long long int prefix_sum;
    struct doubly_node *next;
    struct doubly_node *previous;
};
void push_element_end(struct doubly_node *head ,struct doubly_node *tail ,long int new_element_value);
void print_list(struct doubly_node *head, struct doubly_node *tail);
void print_sum(struct doubly_node *head, struct doubly_node *tail);
void empty_list(struct doubly_node *head, struct doubly_node *tail);
unsigned long int generate_elements(struct doubly_node *head, struct doubly_node *tail, int no_test_cases);


#endif //CODE_DOUBLY_LINKED_LISTS_H
