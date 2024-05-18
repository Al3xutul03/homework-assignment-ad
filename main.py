import time
import math
from doubly_linked_lists import DoublyNode, generate_elements, print_list, empty_list

def main():
    # Initialize the list where all of the values will be stored
    head = DoublyNode()
    tail = DoublyNode()

    head.previous = None
    head.next = tail
    head.info = 0  # The head will store the total amount of values
    head.prefix_sum = 0
    tail.previous = head
    tail.next = None

    # Pointers for storing the wanted subarrays
    first_pointer = None
    second_pointer = None

    # Variables for measuring process time
    start = time.time()

    no_cases = int(input("Input the number of array elements: "))
    
    # Generate the array and output it
    generate_elements(head, tail, no_cases)
    print_list(head, tail)

    # Pointers for separating the 3 subarrays
    left_pointer = head.next
    right_pointer = tail.previous

    # Array for calculating partial sums and variable for their difference
    subarrays = [0] * 3
    diff = 0.0

    min_dif = float('inf')  # Value of the minimal difference/standard deviation

    # Go through the array from both sides
    while left_pointer != right_pointer and left_pointer.previous != right_pointer:
        # Calculate subarrays
        subarrays[0] = left_pointer.prefix_sum
        subarrays[1] = right_pointer.previous.prefix_sum - left_pointer.prefix_sum
        subarrays[2] = tail.previous.prefix_sum - right_pointer.previous.prefix_sum

        # Calculate the standard deviation between them and compare with the current minimum
        average = sum(subarrays) / 3

        diff = 0
        for i in range(3):
            diff += (subarrays[i] - average) ** 2
        diff = math.sqrt(diff / 3)

        # Update the current minimum
        if diff < min_dif:
            min_dif = diff
            first_pointer = left_pointer
            second_pointer = right_pointer

        # Decide which pointer to move according to the current subarray values
        if subarrays[0] >= subarrays[2]:
            right_pointer = right_pointer.previous
        else:
            left_pointer = left_pointer.next

    end = time.time()

    # Print the wanted subarrays
    print_list(head, first_pointer.next)
    print_list(first_pointer, second_pointer)
    print_list(second_pointer.previous, tail)

    print(f"\n Process done in {end - start} seconds")
    print("\n========================")

    # Empty the allocated memory
    empty_list(head, tail)

if __name__ == "__main__":
    main()