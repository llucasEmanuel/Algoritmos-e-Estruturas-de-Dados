class Node:
    def __init__(self, value=None, next_node=None):
        self.value = value
        self.next = next_node

class Queue:
    def __init__(self):
        self.front = Node()
        self.rear = self.front
        self.size = 0
    
    def enqueue(self, value):
        self.rear.next = Node(value)
        self.rear = self.rear.next
        self.size += 1
    
    def dequeue(self):
        if self.size == 0:
            return None
        removed = self.front.next.value
        self.front.next = self.front.next.next
        if self.front.next == None:
            self.rear = self.front
        self.size -= 1
        return removed
    
    def clear(self):
        while self.size > 0:
            self.dequeue()
