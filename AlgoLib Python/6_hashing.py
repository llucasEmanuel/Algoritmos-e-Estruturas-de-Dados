class OpenHashTable:
    def __init__(self, size, h):
        self.size = size
        self.num_elements = 0
        self.table = [None for i in range(size)]
        for i in range(size):
            self.table[i] = []
        self.h = h

    def insert(self, k, e):
        if self.find(k) == None:
            ind = self.h(k)
            self.table[ind].append((k, e))  
            self.num_elements += 1

    def find(self, k):
        ind = self.h(k)
        for d in self.table[ind]:
            if k == d[0]:
                return d[1]
        return None
    
    def remove(self, k):
        ind = self.h(k)
        for d in self.table[ind]:
            if k == d[0]:
                self.table[ind].remove(d)
                self.num_elements -= 1
                return
    
    def print(self):
        print(self.table)


class ClosedHashTable:
    def __init__(self, size, h, p):
        self.size = size
        self.num_elements = 0
        self.table = [None for i in range(size)]
        self.h = h
        self.probe = p
    
    def insert(self, k, e):
        if self.num_elements >= self.size or self.find(k) != None:
            return
        ind = self.h(k)
        new_ind = ind
        i = 0
        while self.table[new_ind] != None and self.table[new_ind] != None:
            i += 1
            new_ind = (ind + self.probe(k, i)) % self.size
        self.table[new_ind] = (k, e)
        self.num_elements += 1
    
    def find(self, k):
        ind = self.h(k)
        new_ind = ind
        i = 0
        while self.table[new_ind] != None and self.table[new_ind][0] != k:
            i += 1
            new_ind = (ind + self.probe(k, i)) % self.size
        if self.table[new_ind] != None and self.table[new_ind][0] == k:
            return self.table[new_ind][1]
        return None
    
    def remove(self, k):
        ind = self.h(k)
        new_ind = ind
        i = 0
        while self.table[new_ind] != None and self.table[new_ind][0] != k:
            i += 1
            new_ind = (ind + self.probe(k, i)) % self.size
        if self.table[new_ind] != None and self.table[new_ind][0] == k:
            self.table[new_ind] = None
            self.num_elements -= 1
    
    def print(self):
        print(self.table)

