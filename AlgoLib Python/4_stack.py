class Node:
    def __init__(self, value=None, next_node=None):
        self.value = value
        self.next = next_node

class Stack:
    def __init__(self):
        self.top = None
        self.size = 0
    
    def push(self, value):
        self.top = Node(value, self.top)
        self.size += 1
    
    def pop(self):
        if self.top == None:
            return None
        removed = self.top.value
        self.top = self.top.next
        self.size -= 1
        return removed
    
    def clear(self):
        while self.size > 0:
            self.pop()

