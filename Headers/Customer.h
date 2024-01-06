// T. F. Nusha - 21/ENG/138

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include "Administrator.h"
#include "Transaction.h"
#include "Employee.h"
#include "Bank.h"
using namespace std;
class Bank;
class Transaction;
class Employee;
class Administrator;
class Customer
{
	public:
	string CustomerName;
	string accountType;
	string customerContact;
	long moneyDeposit;
	bool isCurrentAccount = false;
	long overdraftMaximum = 0;
	bool isClosed = false;
	long overDraftNow = 0;
	string date_tday;
	string dateCreated;

	void depositMoneyFun(Bank &bank, ofstream &MyFile, ofstream &BankFile);
	void setDate(Administrator & Admin);
	void withdrawMoney(Bank &bank, ofstream &MyFile, ofstream &BankFile);
};
#endif
