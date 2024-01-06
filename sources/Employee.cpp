// R. Abinayan - 21/ENG/116

#include "Employee.h"
#include "Administrator.h"
#include "Transaction.h"
#include "Bank.h"
#include "Customer.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

void Employee::setDate(Administrator & Admin)
{
    this->date_tday = Admin.getDate();
};

void Employee::setEmployeeName(string employeeName)
{
    this->employeeName = employeeName;
};

void Employee::createCustomer(Customer &customerCreated, Bank &bank, ofstream &MyFile)
{
    string startLetter = "";
    if (bank.customerArray.size() < 9)
    {
        startLetter = "00";
    }
    else if (bank.customerArray.size() < 99)
    {
        startLetter = "0";
    }

    string customer_contact;
    int account_type;
    customerCreated.dateCreated = date_tday;
    string customerName = "customer" + startLetter + to_string((bank.customerArray.size()) + 1);
    cout << "Customer name : " << "customer" + startLetter + to_string((bank.customerArray.size()) + 1) << endl;
    cout << "Enter mobile number (10 digits) : ";
    cin >> customer_contact;
    customer_contact=checkThePhoneNumberInput(customer_contact);
    customerCreated.CustomerName = customerName;
    customerCreated.customerContact = customer_contact;
    cout << "\n1. Current account" << endl;
    cout << "2. Saving account" << endl;
    cout << "Select the account type : " ;
    cin >> account_type;

    while (account_type < 0 || account_type > 2)
    {
        cout << "Incorrect input! Select a proper account";
        cout << "\n1. Current account" << endl;
        cout << "2. Saving account" << endl;
        cout << "Select the account type : ";
        cin >> account_type;
    }
    long moneyDepositNow;
    string moneyDepositNowChecker;
    cout << "Enter the initial amount deposited : ";
    cin >> moneyDepositNowChecker;
    moneyDepositNow=checkTheMoneyInput(moneyDepositNowChecker);
    if (account_type == 1)
    {
        customerCreated.accountType = "Current";
        string overdraftChecker;
        customerCreated.isCurrentAccount = true;
        cout << "Enter the overdraft limit : ";
        cin>>overdraftChecker;
        customerCreated.overdraftMaximum=checkTheMoneyInput(overdraftChecker);
    }
    else if (account_type == 2)
    {
        customerCreated.accountType = "Saving";
    }

    customerCreated.moneyDeposit = moneyDepositNow;
    bank.customerNameArray.push_back(customerName);
    bank.customerArray.push_back(customerCreated);
    MyFile << customerCreated.date_tday << " - " << customerCreated.CustomerName << " : Account created." <<" Rs : Balance is "<<customerCreated.moneyDeposit << endl;
    MyFile << customerCreated.date_tday << " - " << customerCreated.CustomerName << " : Deposited " << moneyDepositNow <<" Rs : Balance is "<<customerCreated.moneyDeposit << endl;
    Transaction transaction_now_1;
    transaction_now_1.setTransactionDate(customerCreated.date_tday);
    transaction_now_1.setDescription(customerCreated.CustomerName, "Money credited to customer account", moneyDepositNow);
    customerCreated.transactions.push_back(transaction_now_1);
    bank.customerArray.back()=customerCreated;
};

void Employee::depositMoney(Customer &customer, Bank &bank, ofstream &MyFile, ofstream &BankFile)
{
    if (customer.isClosed == false)
    {
        long account_balance = customer.moneyDeposit;
        long now_deposited;
        string now_deposited_checker;
        cout << "Enter the amount to be deposited: ";
        cin >> now_deposited_checker;
        now_deposited=checkTheMoneyInput(now_deposited_checker);
        customer.moneyDeposit = account_balance + now_deposited;
        MyFile << customer.date_tday << " - " << customer.CustomerName << " : Deposited " << now_deposited <<" Rs : Balance is "<<customer.moneyDeposit << endl;
        Transaction transaction_now_1;
        transaction_now_1.setTransactionDate(customer.date_tday);
        transaction_now_1.setDescription(customer.CustomerName, "Money credited to customer account", now_deposited);
        customer.transactions.push_back(transaction_now_1);

        if (customer.moneyDeposit >= 0)
        {
            bank.bank_balance += customer.overDraftNow;
            BankFile << customer.date_tday << " - " << customer.CustomerName << " : overdraft credited to bank account : " << to_string(customer.overDraftNow) << " Rs." << endl;
            BankFile << customer.date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.date_tday);
            transaction_now_2.setDescription(customer.CustomerName, "overdraft credited to bank account", customer.overDraftNow);
            bank.transactions.push_back(transaction_now_2);
            customer.overDraftNow = 0;
        }
        else
        {
            bank.bank_balance += now_deposited;
            customer.overDraftNow -= now_deposited;
            BankFile << customer.date_tday << " - " << customer.CustomerName << " : overdraft credited to bank account : " << to_string(now_deposited) << " Rs." << endl;
            BankFile << customer.date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.date_tday);
            transaction_now_2.setDescription(customer.CustomerName, "overdraft credited to bank account", now_deposited);
            bank.transactions.push_back(transaction_now_2);
        }
    }
    else
    {
        cout << "Sorry. Account is already closed" << endl;
    }
};

void Employee::withDrawMoney(Customer &customer, Bank &bank, ofstream &MyFile, ofstream &BankFile)
{
    if (customer.isClosed == false)
    {
        long now_withdraw;
        string now_withdraw_checker;
        cout << "Enter the amount to be withdrawed: ";
        cin >> now_withdraw_checker;
        now_withdraw=checkTheMoneyInput(now_withdraw_checker);

        if (customer.isCurrentAccount == false && now_withdraw > customer.moneyDeposit)
        {
            cout << "Sorry insufficient balance" << endl;
        }
        else if (customer.isCurrentAccount == false && now_withdraw <= customer.moneyDeposit)
        {
            customer.moneyDeposit -= now_withdraw;
            cout << "Successful withdrawal" << endl;
            MyFile << customer.date_tday << " - " << customer.CustomerName << " : Withdrawn " << now_withdraw <<" Rs : Balance is "<<customer.moneyDeposit <<  endl;
            Transaction transaction_now_1;
            transaction_now_1.setTransactionDate(customer.date_tday);
            transaction_now_1.setDescription(customer.CustomerName, "Money debited from customer account", now_withdraw);
            bank.transactions.push_back(transaction_now_1);
        }
        else if (customer.isCurrentAccount == true && now_withdraw > customer.moneyDeposit)
        {
            if (((customer.moneyDeposit - now_withdraw) *(-1)) <= customer.overdraftMaximum && ((customer.moneyDeposit - now_withdraw) *(-1)) <= bank.bank_balance)
            {
                customer.overDraftNow = now_withdraw - (customer.moneyDeposit);
                bank.bank_balance -= customer.overDraftNow;
                customer.moneyDeposit -= now_withdraw;
                cout << "Successful withdrawal" << endl;
                BankFile << customer.date_tday << " - " << customer.CustomerName << " : overdraft debited to bank account : " << to_string(customer.overDraftNow) << " Rs." << endl;
                BankFile << customer.date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
                MyFile << customer.date_tday << " - " << customer.CustomerName << " : Withdrawn " << now_withdraw << " Rs : Balance is "<<customer.moneyDeposit << endl;
                Transaction transaction_now_2;
                Transaction transaction_now_3;
                transaction_now_2.setTransactionDate(customer.date_tday);
                transaction_now_3.setTransactionDate(customer.date_tday);
                transaction_now_2.setDescription(customer.CustomerName, "Money withdrawn from customer account", now_withdraw);
                transaction_now_3.setDescription(customer.CustomerName, "overdraft debited to bank account", customer.overDraftNow);
                customer.transactions.push_back(transaction_now_2);
                bank.transactions.push_back(transaction_now_3);
            }
            else if (((customer.moneyDeposit - now_withdraw) *(-1)) <= customer.overdraftMaximum && ((customer.moneyDeposit - now_withdraw) *(-1)) > bank.bank_balance)
            {
                cout << "Sorry. Cannot withdraw amount greater than balance in bank.";
            }
            else
            {
                cout << "Sorry. Cannot withdraw amount greater than maximum overdraft.";
            }
        }
        else if (customer.isCurrentAccount == true && now_withdraw <= customer.moneyDeposit)
        {
            customer.moneyDeposit -= now_withdraw;
            cout << "Successful withdrawal" << endl;
            MyFile << customer.date_tday << " - " << customer.CustomerName << " : Withdrawn " << now_withdraw <<" Rs : Balance is "<<customer.moneyDeposit <<  endl;
            Transaction transaction_now_4;
            transaction_now_4.setTransactionDate(customer.date_tday);
            transaction_now_4.setDescription(customer.CustomerName, "Money debited from customer account", now_withdraw);
            customer.transactions.push_back(transaction_now_4);
        }
    }
    else
    {
        cout << "Sorry. Account is already closed" << endl;
    }
};

void Employee::viewTransactions(Bank & bank)
{

    int numberOfBankTransactions = bank.transactions.size();
    if(numberOfBankTransactions>0)
    {
        cout << "Transaction related with money owned by bank" << endl << endl;
        for (int i = 0; i < numberOfBankTransactions; i++)
        {
            cout << bank.transactions[i].getDescription() << endl;
        }
    }
    for (int i = 0; i < bank.customerArray.size(); i++)
    {
        cout << "Transaction related with " + bank.customerArray[i].CustomerName << endl;
        for (int j = 0; j <bank.customerArray[i].transactions.size(); j++)
        {
            cout << bank.customerArray[i].transactions[j].getDescription() << endl;
        }
    }
};

string Employee::getEmployeeName()
{
    return this->employeeName;
};

void Employee::closeCustomerAccount(Customer &customer, ofstream &MyFile)
{
    if (customer.moneyDeposit == 0)
    {
        customer.isClosed = true;
        cout << "Account closed successfully." << endl;
        MyFile << customer.date_tday << " - " << customer.CustomerName << " : Account closed." << endl;
    }
    else if (customer.moneyDeposit > 0)
    {
        string userInputCloseAcc;
        cout << "Do you want to withdraw the remaining amount of " << customer.moneyDeposit << " and close the account." << endl;
        cout << "press 1 for yes \nPress 2 for no : " ;	////////////////////////////////////////////////////////////////
        cin >> userInputCloseAcc;
        while(userInputCloseAcc!="1" && userInputCloseAcc!="2")
        {
            cout << "Incorrect input. Please press 1 for yes or 2 for no : " ;	//
            cin>>userInputCloseAcc;
        }
        cout<<endl;
        if (userInputCloseAcc == "1")
        {
            customer.moneyDeposit == 0;
            customer.isClosed = true;
            cout << "Account closed successfully." << endl;
            MyFile << customer.date_tday << " - " << customer.CustomerName << " : remaining amount of" << customer.moneyDeposit << " is taken and Account is closed." << endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.date_tday);
            transaction_now_2.setDescription(customer.CustomerName, "Money debited from customer account", customer.moneyDeposit);
            customer.transactions.push_back(transaction_now_2);
        }
        else if (userInputCloseAcc == "2")
        {
            cout << "Account not closed." << endl;
        }
    }
    else if (customer.moneyDeposit < 0)
    {
        cout << "There is an overdraft in this account. So account cannot be closed." << endl;
    }
};

