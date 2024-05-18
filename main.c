#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <math.h>
#include "doubly_linked_lists.h"

int main(void) {
    // Initialize the list where all of the values will be stored
    struct doubly_node *head = malloc(sizeof(struct doubly_node));
    struct doubly_node *tail = malloc(sizeof(struct doubly_node));

    head->previous = NULL;
    head->next = tail;
    head->info = 0; // The head will store the total ammount of values
    head->prefix_sum = 0;
    tail->previous = head;
    tail->next = NULL;

    // Pointers for storing the wanted subarrays
    struct doubly_node *first_pointer = NULL;
    struct doubly_node *second_pointer = NULL;

    // Variables for measuring process time
    clock_t start, end;

    // Take the number of elements
    int no_cases;
    printf("Input the number of array elements: ");
    scanf("%d", &no_cases);
    
    start = clock();
     // Generate the array and output it
    generate_elements(head, tail, no_cases);
    print_list(head, tail);

    // Print only the sum
    //print_sum(head, tail);

    // Pointers for separating the 3 subarrays
    struct doubly_node *left_pointer = head->next;
    struct doubly_node *right_pointer = tail->previous;

    // Array for calculating partial sums and variable for their difference
    unsigned long long int subarrays[3];
    float diff;

    float min_dif = LONG_MAX; // Value of the minimal difference/standard deviation

    // Go through the array from both sides
    while (left_pointer != right_pointer && left_pointer->previous != right_pointer) {
        // Calculate subarrays
        subarrays[0] = left_pointer->prefix_sum;
        subarrays[1] = right_pointer->previous->prefix_sum - left_pointer->prefix_sum;
        subarrays[2] = tail->previous->prefix_sum - right_pointer->previous->prefix_sum;

        // Calculate the standard deviation between them and compare with the current minimum
        float average = (subarrays[0] + subarrays[1] + subarrays[2]) / 3;

        diff = 0;
        for (int i = 0; i < 3; i++)
            diff += pow(subarrays[i] - average, 2);
        diff = sqrt(diff / 3);

        // Update the current minimum
        if (diff < min_dif) {
            min_dif = diff;
            first_pointer = left_pointer;
            second_pointer = right_pointer;
        }

        // Decide which pointer to move according to the current subarray values
        if (subarrays[0] >= subarrays[2])
            right_pointer = right_pointer->previous;
        else
            left_pointer = left_pointer->next;
    }
    end = clock();

    // Print the wanted subarrays
    print_list(head, first_pointer->next);
    print_list(first_pointer, second_pointer);
    print_list(second_pointer->previous, tail);

    // Print only the partial sums
    //print_sum(head, first_pointer->next);
    //print_sum(first_pointer, second_pointer);
    //print_sum(second_pointer->previous, tail);

    printf("\n Process done in %f seconds", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("\n========================");

    // Empty the allocated memory
    empty_list(head, tail);

    return 0;
}
