import math

class Shape:
    def __init__(self):
        pass

    def area(self):
        print("This function prints the area of the shape")

class Circle(Shape):
    def __init__(self, radius):
        super().__init__()
        self.radius = radius
    
    def area(self):
        print("Area:", math.pi * (self.radius ** 2))

class Rectangle(Shape):
    def __init__(self, length, width):
        super().__init__()
        self.length = length
        self.width = width
    
    def area(self):
        print("Area:", self.length * self.width)


rect = Rectangle(3, 4)
circle = Circle(4)
rect.area()
circle.area()