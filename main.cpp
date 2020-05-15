#include <iostream>
using namespace std;

class Account{
public:
    double accountBalance;

    Account (double);

    void credit(double amount) {
        accountBalance +=amount;
    }

    void debit(double amount) {
        if (amount>accountBalance){
            cout<<"\nDebit amount exceeded account balance.";
        } else {
            accountBalance-=amount;
        }
    }

    double getBalance(){
        return accountBalance;
    }

};

class SavingsAccount : private Account {
private:
    double interestRate, initialBalance, interest;
public:
    SavingsAccount(double, double);

    double calculateInterest(){
        interestRate = (interestRate/100);
        interest = interestRate*Account(initialBalance).accountBalance;
        return interest;
    }

};

SavingsAccount::SavingsAccount(double rate, double initBal) : Account(initialBalance) {
    interestRate = rate;
    initialBalance = initBal;
};

class CheckingAccount : private Account {
private:
    double feeCharged;
    bool transactionStatus;
    string transactionType;

    void debit(double amount) {

    }

    void credit(double amount) {

    }

public:
    void chargeFee(){

    }
};


Account::Account(double initialBalance) {
  accountBalance = initialBalance;
  if(accountBalance<0){
      accountBalance=0.0;
      cout<<"\nThe initial balance is invalid. ";
  }
};

int main() {
    double drAmount = 7200, crAmount=200, initBal = 5000, intRate=10;
    cout << "\nBank Accounts & hierarchy. "<<endl;

    cout<<"\nTesting with initial balance of "<<initBal;
    Account acc(initBal);

    cout<<"\nCurrent Balance : "<<acc.accountBalance;

    cout << "\n\n:: Credit :: (Testing with amount "<<crAmount<<")";
    acc.credit(crAmount);
    cout<<"\nAfter Credit : "<<acc.getBalance();

    cout << "\n\n :: Debit :: (Testing with amount "<<drAmount<<")";
    acc.debit(drAmount);
    cout<<"\nAfter Debit : "<<acc.getBalance();

    cout<<"\n\n :: Savings A/c :: \n";
    cout<<"\nInitial balance "<<initBal;
    cout<<"\nInitial interest rate "<<intRate;

    SavingsAccount sacc(intRate,initBal);
    cout<<"\nInterest Accrued : "<<sacc.calculateInterest();
    cout<<"\nBalance + Interest : "<<acc.getBalance()+sacc.calculateInterest();

    return 0;
}