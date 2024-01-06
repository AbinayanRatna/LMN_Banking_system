// R.Abinayan - 21/ENG/116
// T. F. Nusha - 21/ENG/138

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Administrator.h"
#include "Transaction.h"
#include "Bank.h"
#include "Customer.h"
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
class Bank;
class Customer;
class Transaction;
class Administrator;
using namespace std;
class Employee
{
	private:
	string employeeName;
	string date_tday;
	public:
	void setDate(Administrator & Admin);
	void setEmployeeName(string employeeName);
	string getEmployeeName();
	void createCustomer(Customer &customerCreated, Bank &bank, ofstream &MyFile);
	void depositMoney(Customer &customer, Bank &bank, ofstream &MyFile, ofstream &BankFile);
	void withDrawMoney(Customer &customer, Bank &bank, ofstream &MyFile, ofstream &BankFile);
        void viewTransactions(Bank & bank);
	void closeCustomerAccount(Customer &customer, ofstream &MyFile);
};
#endif
