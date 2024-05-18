import random

class DoublyNode:
    def __init__(self):
        self.previous = None
        self.next = None
        self.info = 0
        self.prefix_sum = 0

def generate_elements(head, tail, no_cases):
    # Function to generate elements and update the list
    current = head
    prefix_sum = 0
    for i in range(1, no_cases + 1):
        new_node = DoublyNode()
        new_node.info = random.randint(0, 1000)
        prefix_sum += new_node.info
        new_node.prefix_sum = prefix_sum
        new_node.previous = current
        current.next = new_node
        current = new_node
    current.next = tail
    tail.previous = current

def print_list(start, end):
    current = start.next
    while current != end:
        print(f"Info: {current.info}")
        current = current.next
    print(f"Prefix Sum: {current.previous.prefix_sum - start.prefix_sum}")

def empty_list(head, tail):
    current = head
    while current is not None:
        temp = current
        current = current.next
        del temp