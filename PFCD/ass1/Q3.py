class Chapter:
    def __init__(self, title, count):
        self.title = title
        self.count = count

    def display(self):
        print(self.title, self.count)

class Book:
    ch = []
    def __init__(self, chCount):
        for i in range(chCount):
            Book.ch.append(Chapter(input("Enter title: "), int(input("Enter page count: "))))
    
    
    def display(self):
        for c in Book.ch:
            c.display()


b = Book(3)
b.display()
