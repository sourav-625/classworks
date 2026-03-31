class Dog:
    def __init__(self):
        pass

    def speak(self):
        print("Dog Barks")

class Robot:
    def __init__(self):
        pass

    def speak(self):
        print("Robot Squeaks")

def describe(object):
    object.speak()

dog = Dog()
bot = Robot()
describe(dog)
describe(bot)