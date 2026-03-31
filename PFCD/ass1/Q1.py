class Subject:
    def __init__(self, s1, s2, s3, mark1, mark2, mark3):
        self.s1 = s1
        self.s2 = s2
        self.s3 = s3
        self.mark1 = mark1
        self.mark2 = mark2
        self.mark3 = mark3
    
    def average(self):
        return (self.mark1 + self.mark2 + self.mark3) / 3
    
    def display(self):
        print(self.s1, self.mark1, self.s2, self.mark2, self.s3, self.mark3, sep="\n")
    
s = Subject("Maths", "Science", "English", 20, 21, 23)
print(s.average(), "\n")
s.display()