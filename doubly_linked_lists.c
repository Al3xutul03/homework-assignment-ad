#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "doubly_linked_lists.h"

// Generate list elements
unsigned long int generate_elements(struct doubly_node *head, struct doubly_node *tail, int no_test_cases){
    time_t t;

    srand((unsigned) time(&t));
    for (int i = 0; i < no_test_cases; i++)
        push_element_end(head, tail, rand() % LONG_MAX);
}

// Push a new value to the end of the list
void push_element_end(struct doubly_node *head ,struct doubly_node *tail ,long int new_element_value){
    struct doubly_node *new_element = malloc(sizeof(struct doubly_node));
    struct doubly_node *last_element;
    new_element->info = new_element_value;

    last_element = tail->previous;
    if (last_element != NULL) {
        last_element->next = new_element;
    }

    new_element->previous = last_element;
    new_element->next = tail;
    new_element->prefix_sum = last_element->prefix_sum + new_element_value;
    tail->previous = new_element;
    head->info++;
}

// Print the list
void print_list(struct doubly_node *head, struct doubly_node *tail){
    struct doubly_node *iterator = head;

    printf("\n List: ");
    while (iterator->next != tail) {
        printf("%u ", iterator->next->info);
        iterator = iterator->next;
    }
    if (iterator == head)
        printf("%u ", iterator->next->info);
    printf("\n Sum: %u", tail->previous->prefix_sum - head->prefix_sum);

}

// Print the prefix sum between two elements
void print_sum(struct doubly_node *head, struct doubly_node *tail){
    printf("\n Sum: %u", tail->previous->prefix_sum - head->prefix_sum);
}

// Free the memory of the list
void empty_list(struct doubly_node *head, struct doubly_node *tail){
    struct doubly_node *iterator_left;
    struct doubly_node *iterator_right;

    assert(head->next != tail);
    iterator_left = head->next;
    iterator_right = tail->previous;

    while( 1 > 0){
        if (iterator_left == iterator_right){
            free(iterator_left);
            break;
        }
        if (iterator_left->next == iterator_right){
            free(iterator_left);
            free(iterator_right);
            break;
        }
        iterator_left = iterator_left->next;
        free(iterator_left->previous);
        iterator_right = iterator_right->previous;
        free(iterator_right->next);
    }

    head->next = tail;
    head->info = 0;
    tail->previous = head;
}
