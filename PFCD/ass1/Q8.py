class Vehicle:
    def __init__(self, make, model):
        self.make = make
        self.model = model

    def display_info(self):
        print("Made in:", self.make, "\nModel:", self.model)

class Car(Vehicle):
    def __init__(self, make, model, num_doors):
        self.num_doors = num_doors
        super().__init__(make, model)
    
    def display_info(self):
        super().display_info()
        print("Number of Doors:", self.num_doors)


car = Car("India", "XYZ", 4)
vehicle = Vehicle("India", "XYZ")

vehicle.display_info()
print()
car.display_info()