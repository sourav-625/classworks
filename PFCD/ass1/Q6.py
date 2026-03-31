class Bank:
    def __init__(self, type, bal):
        self.__type = type
        self.__bal = bal
    
    def display(self):
        print("Account Type:", self.__type, "\nBalance:", self.__bal)
    
    def deposit(self, amt):
        self.__bal += amt

    def withdraw(self, amt):
        self.__bal -= amt
    
bank = Bank("Savings", 1000)
bank.display()
bank.deposit(2000)
bank.display()
print(bank.__bal) 