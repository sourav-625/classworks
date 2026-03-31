class Complex:
    def __init__(self, real, img):
        self.real = real
        self.img = img

    def __add__(self, other):
        return Complex(self.real + other.real, self.img + other.img)
    
    def __sub__(self, other):
        return Complex(self.real - other.real, self.img - other.img)
    
    def __mul__(self, other):
        return Complex(self.real * other.real - self.img * other.img)
    
    