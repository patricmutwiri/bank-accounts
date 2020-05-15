#include <iostream>
using namespace std;

class Account{
public:
    float accountBalance;

    Account (float);

    bool credit(float amount) {
        accountBalance = accountBalance+amount;
        cout<<"\nNew amount after credit "<< this->getBalance();
        accountBalance = this->getBalance();
        return true;
    }

    bool debit(float amount) {
        if (amount>accountBalance){
            cout<<"\nDebit amount exceeded account balance.";
            return false;
        } else {
            accountBalance = accountBalance-amount;
            cout<<"\nNew amount after debit "<< this->getBalance();
            return true;
        }
    }

    float getBalance(){
        return accountBalance;
    }

};

class SavingsAccount : public Account {
private:
    float interestRate, initialBalance, interest;
public:
    SavingsAccount(float, float);

    float calculateInterest(){
        interestRate = (interestRate/100);
        interest = interestRate*Account(initialBalance).accountBalance;
        return interest;
    }

};

class CheckingAccount : public Account {
public:
    float balMinFee,initialBalance;
    CheckingAccount(float, float);

    float chargeFee(float fee) {
        cout<<"\nBalance before charges "<< Account(initialBalance).getBalance();
        balMinFee = Account(initialBalance).getBalance()-fee;
        cout<<"\nCharge fee "<<fee<<" on balance "<<Account(initialBalance).getBalance()<<" to "<<balMinFee;
        this->accountBalance = balMinFee;
        return balMinFee;
    }

    float debit(float amount);

    float credit(float amount) {
        Account acc(initialBalance);
        cout<<"\nAmount to credit here "<<amount;
        transactionStatus = acc.credit(amount);
        if(transactionStatus) {

            cout<<"\nTransaction status "<<transactionStatus;
            return this->chargeFee(feeCharged);
        } else {
            cout<<"\nFee not charged on credit.";
            return 0;
        }
    }

    float feeCharged;
    bool transactionStatus;
};

SavingsAccount::SavingsAccount(float rate, float initBal) : Account(float (initialBalance)) {
    interestRate = rate;
    initialBalance = initBal;
};

CheckingAccount::CheckingAccount(float fee, float initBal) : Account(float (initialBalance)) {
    feeCharged = fee;
    initialBalance = initBal;
}

float CheckingAccount::debit(float amount) {
    transactionStatus = this->debit(amount);
    if(transactionStatus) {
        // charge fee
        return chargeFee(feeCharged);
    } else {
        cout<<"\nFee not charged on debit.";
        return 0;
    }
}

Account::Account(float initialBalance) {
  accountBalance = initialBalance;
  if(accountBalance<0){
      accountBalance=0.0;
      cout<<"\nThe initial balance is invalid. ";
  }
};

int main() {
    float drAmount = 7200, crAmount=200, initBal = 5000, intRate=10, feeAmount=33, interestAmt=0,newBal=0;
    cout << "\nBank Accounts & hierarchy. "<<endl;

    cout<<"\nTesting with initial balance of "<<initBal;

    cout<<"\n\n :: Savings A/c :: \n";
    cout<<"\nInitial balance "<<initBal;
    cout<<"\nInitial interest rate "<<intRate;
    Account acc(initBal);
    CheckingAccount cacc(feeAmount,initBal);
    SavingsAccount sacc(intRate,initBal);
    interestAmt = sacc.calculateInterest();

    newBal = acc.getBalance();
    initBal = newBal+interestAmt;

    cout<<"\nInterest Accrued : "<<interestAmt;
    cout<<"\nCurrent bal : "<<newBal;
    cout << "\n\n:: Credit Interest :: (of amount "<<interestAmt<<")";
    cacc.credit(interestAmt);
    cout<<"\nAfter interest credit : "<<acc.getBalance();


    //return 0;



    cout<<"\nBalance ("<<newBal<<") + Interest ("<<interestAmt<<") : "<<initBal;
    cout<<"\nMinus fee charges "<<feeAmount<<" should come to "<<initBal-feeAmount;
    cout << "\n\n:: Credit :: (of amount "<<interestAmt<<")";
    cacc.credit(crAmount);
    cout<<"\nAfter Credit : "<<cacc.accountBalance;



    //
    cout<<"\n\n :: Checking A/c :: \n";


    //cout<<"\nInterest Accrued : "<<cacc.chargeFee(feeAmount);
    //cout<<"\nBalance + Interest : "<<acc.getBalance()+sacc.calculateInterest();
    cout<<"\nCurrent Balance : "<<acc.accountBalance;



    cout << "\n\n :: Debit :: (Testing with amount "<<drAmount<<")";
    acc.debit(drAmount);
    cout<<"\nAfter Debit : "<<acc.getBalance();

    return 0;
}