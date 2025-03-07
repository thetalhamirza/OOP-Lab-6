#include<iostream>
using namespace std;

class BankAccount {
    string accNum;
    double balance, limit;
    bool frozen = false;


    protected:
    void setBalance(double bal) {balance = bal;}
    void setLimit(double amount)    {limit = amount;}
    void setStatus(bool status) {frozen = status;}

    public:
    BankAccount() {}
    BankAccount(string accnum, double bal) {
        this->accNum = accnum;
        this->balance = bal;
        this->limit = 25000;
    }

    void deposit(double amount) {
        if (!frozen) {
            this->balance += amount;
        }            
    }
    void withdraw(double amount) {
        if (!frozen) {
            if (balance >= 0 && amount <= limit) {
                if (amount <= balance) {
                    this->balance -= amount;
                    this->limit -= amount;
                    cout << "New Balance: " << balance << endl;
                } else {
                    cout << "Not enough funds." << endl;
                }
            } else {
                cout << "Balance is zero." << endl;
            }
        }    
    }
    double getBalance()   {return balance;}
    double getLimit()   {return limit;}
    double getStatus()   {return frozen;}


};


class SavingsAccount: public BankAccount {
    float interestRate = 1.05;
    public:
    
    void setInterestRate(float rate) {
        interestRate = rate;
    }
    float getInterestRate() {return interestRate;}

    void applyMonthlyInterest() {
        setBalance(getBalance()*interestRate);
    }
    
};

class CheckingAccount: public BankAccount {
    public:
    double overdraft, draftLimit=1000;
    void withdraw(double amount) {
        setBalance(getBalance() - amount);
        cout << "Withdrawn " << amount << endl;
        if (getBalance() < 0 && checkOverdraft() == 0) {
            overdraft = getBalance() * -1;
            setBalance(0);
        }
    }
    void deposit(double amount) {
        if (overdraft > 0) {
            amount -= overdraft;
            overdraft = 0;    
        }
        setBalance(getBalance()+amount);
    }
    int checkOverdraft() {
        if (overdraft >= draftLimit) {
            cout << "Overdraft Limit Exceeded!" << endl;
            return 1;
        } else {return 0;}
    }
};

class BusinessAccount: public BankAccount {
    float tax = 0.13;
    public:
    void deposit(double amount) {
        double taxAmount = amount*tax;
        amount -= taxAmount;
        cout << "Corporate tax deductions: " << taxAmount << endl;
        setBalance(getBalance()+amount);
    }
};



class Manager: public BankAccount {
    
    void adjustLimits(double amount)    {
        setLimit(amount);
    }

    protected:

    void setFreezeStatus(bool status) {setStatus(status);}

};

class Teller: public Manager {
    void setFreezeStatus(bool status) {setStatus(status);}

};

class Customer: public Teller {

};