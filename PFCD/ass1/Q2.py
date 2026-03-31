class Bank:
    def __init__(self, st, name, amt):
        self.st = st
        self.name = name
        self.st[self.name] = amt
    
    def deposit(self, m):
        self.st[self.name] += m

    def withdraw(self, m):
        self.st[self.name] -= m
    
    def bal(self):
        return f"{self.st[self.name]}"
    
st: dict = {"Sourav": 20000, "Om": 15000, "Raj": 18000, "Guru": 5000}
bank = Bank(st, "Sourav", 20000)
bank.deposit(5000)
bank.withdraw(2000)
print(bank.bal())