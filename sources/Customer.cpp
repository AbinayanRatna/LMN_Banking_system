// T. F. Nusha - 21/ENG/138

#include "Customer.h"
#include "Administrator.h"
#include "Transaction.h"
#include "Employee.h"
#include "Bank.h"

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;
void Customer::viewTransaction()
{
	int numberOfTransactions = this->transactions.size();
	for (int i = 0; i < numberOfTransactions; i++)
	{
		cout << this->transactions[i].getDescription() << endl;
	}
};

void Customer::depositMoneyFun(Bank &bank, ofstream &MyFile, ofstream &BankFile)
{
	int moneyAdded;
	cout << "Enter the amount of money to deposit: ";
	cin >> moneyAdded;
	this->moneyDeposit += moneyAdded;
	MyFile << this->date_tday << " - " << this->CustomerName << " : deposited " << to_string(moneyAdded)<<" Rs : Balance is "<<this->moneyDeposit << endl;
	Transaction transaction_now_1;
	transaction_now_1.setTransactionDate(this->date_tday);
	transaction_now_1.setDescription(this->CustomerName, "Money credited to customer account", moneyAdded);
	this->transactions.push_back(transaction_now_1);

	if (this->moneyDeposit >= 0)
	{
		bank.bank_balance += overDraftNow;
		BankFile << this->date_tday << " - " << this->CustomerName << " : overdraft credited to bank account : " << to_string(overDraftNow) << " Rs." << endl;
		BankFile << this->date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
		Transaction transaction_now_2;
		transaction_now_2.setTransactionDate(this->date_tday);
		transaction_now_2.setDescription(this->CustomerName, "overdraft credited to bank account", overDraftNow);
		bank.transactions.push_back(transaction_now_2);
		this->overDraftNow = 0;
	}
	else
	{
		bank.bank_balance += moneyAdded;
		BankFile << this->date_tday << " - " << this->CustomerName << " : overdraft credited to bank account : " << to_string(moneyAdded) << " Rs." << endl;
		BankFile << this->date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
		this->overDraftNow -= moneyAdded;
		Transaction transaction_now_2;
		transaction_now_2.setTransactionDate(this->date_tday);
		transaction_now_2.setDescription(this->CustomerName, "overdraft credited to bank account", moneyAdded);
		bank.transactions.push_back(transaction_now_2);
	}

	for (int i = 0; i <= bank.customerNameArray.size(); i++)
	{
		if (this->CustomerName == bank.customerNameArray[i])
		{
			bank.customerArray[i].moneyDeposit = this->moneyDeposit;
			bank.customerArray[i].overDraftNow = this->overDraftNow;
		}
	}
}

void Customer::setDate(Administrator & Admin)
{
	this->date_tday = Admin.getDate();
};

void Customer::withdrawMoney(Bank &bank, ofstream &MyFile, ofstream &BankFile)
{
	int moneyToWithdraw;
	cout << "Enter the amount of money to withdraw: ";
	cin >> moneyToWithdraw;
	if (this->isCurrentAccount == false && moneyToWithdraw > this->moneyDeposit)
	{
		cout << "Sorry insufficient balance" << endl;
	}
	else if (this->isCurrentAccount == false && moneyToWithdraw <= this->moneyDeposit)
	{
		this->moneyDeposit -= moneyToWithdraw;
		cout << "Successful withdrawal" << endl;
		MyFile << this->date_tday << " - " << this->CustomerName << " : Withdrawn " << to_string(moneyToWithdraw) <<" Rs : Balance is "<<this->moneyDeposit << endl;
		Transaction transaction_now_1;
		transaction_now_1.setTransactionDate(this->date_tday);
		transaction_now_1.setDescription(this->CustomerName, "Money withdrawn from customer account", moneyToWithdraw);
		this->transactions.push_back(transaction_now_1);
	}
	else if (this->isCurrentAccount == true && moneyToWithdraw > this->moneyDeposit)
	{
		if (((this->moneyDeposit - moneyToWithdraw) *(-1)) <= this->overdraftMaximum && ((this->moneyDeposit - moneyToWithdraw) *(-1)) <= bank.bank_balance)
		{
			this->overDraftNow = moneyToWithdraw - (this->moneyDeposit);
			bank.bank_balance -= this->overDraftNow;
			this->moneyDeposit -= moneyToWithdraw;
			cout << "Successful withdrawal" << endl;
			BankFile << this->date_tday << " - " << this->CustomerName << " : overdraft debited to bank account : " << to_string(this->overDraftNow) << " Rs." << endl;
			BankFile << this->date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
			MyFile << this->date_tday << " - " << this->CustomerName << " : Withdrawn " << to_string(moneyToWithdraw) <<" Rs : Balance is "<<this->moneyDeposit << endl;
			Transaction transaction_now_2;
			Transaction transaction_now_3;
			transaction_now_2.setTransactionDate(this->date_tday);
			transaction_now_3.setTransactionDate(this->date_tday);
			transaction_now_2.setDescription(this->CustomerName, "Money withdrawn from customer account", moneyToWithdraw);
			transaction_now_3.setDescription(this->CustomerName, "overdraft debited to bank account", this->overDraftNow);
			this->transactions.push_back(transaction_now_2);
			bank.transactions.push_back(transaction_now_3);
		}
		else if (((this->moneyDeposit - moneyToWithdraw) *(-1)) <= this->overdraftMaximum && ((this->moneyDeposit - moneyToWithdraw) *(-1)) > bank.bank_balance)
		{
			cout << "Sorry. Cannot withdraw amount greater than balance in the bank.";
		}
		else
		{
			cout << "Sorry. Cannot withdraw amount greater than maximum overdraft.";
		}
	}
	else if (this->isCurrentAccount == true && moneyToWithdraw <= this->moneyDeposit)
	{
		this->moneyDeposit -= moneyToWithdraw;
		cout << "Successful withdrawal" << endl;
		MyFile << this->date_tday << " - " << this->CustomerName << " : Withdrawn " << to_string(moneyToWithdraw) <<" Rs : Balance is "<<this->moneyDeposit << endl;
		Transaction transaction_now_4;
		transaction_now_4.setTransactionDate(this->date_tday);
		transaction_now_4.setDescription(this->CustomerName, "Money withdrawn from customer account", moneyToWithdraw);
		this->transactions.push_back(transaction_now_4);
	}

	for (int i = 0; i <= bank.customerNameArray.size(); i++)
	{
		if (this->CustomerName == bank.customerNameArray[i])
		{
			bank.customerArray[i].moneyDeposit = this->moneyDeposit;
			bank.customerArray[i].overDraftNow = this->overDraftNow;
		}
	}
};
