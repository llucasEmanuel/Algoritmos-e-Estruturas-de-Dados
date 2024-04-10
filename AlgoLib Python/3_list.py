class Node:
    def __init__(self, value=None, next_node=None):
        self.value = value
        self.next = next_node

class LinkedList:
    def __init__(self):
        self.head = Node()
        self.curr = self.head
        self.tail = self.head
        self.size = 0

    def insert(self, value):
        self.curr.next = Node(value, self.curr.next)
        if self.tail == self.curr:
            self.tail = self.curr.next
        self.size += 1

    def move_to_start(self):
        self.curr = self.head
    
    def curr_prev(self):
        if self.curr == self.head:
            return
        temp = self.head
        while temp.next != self.curr:
            temp = temp.next
        self.curr = temp
    
    def curr_next(self):
        if self.curr != self.tail:
            self.curr = self.curr.next
    
    def remove(self):
        if self.curr.next == None:
            return None
        removed = self.curr.next.value
        if self.tail == self.curr.next:
            self.tail = self.curr
        self.curr.next = self.curr.next.next
        self.size -= 1
        return removed
    
    def clear(self):
        self.move_to_start()
        while self.size > 0:
            self.remove()
    
    def print(self):
        temp = self.head
        while temp != self.tail:
            temp = temp.next
            print(temp.value, end=' ')
        print()


