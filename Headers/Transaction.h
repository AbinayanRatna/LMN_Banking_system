// M. Lalithambigai - 21/ENG/075

#ifndef TRANSACTION_H
#define TRANSACTION_H


#include "Administrator.h"
#include "Employee.h"
#include "Bank.h"
#include "Customer.h"
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;
class Bank;
class Customer;
class Employee;
class Administrator;
class Transaction
{
	private:
	string date_tday;
	string description;
	public:

	void setTransactionDate(string date_tday)
	{
		this->date_tday = date_tday;
	}

	void setDescription(string customer_name, string debitOrCredit, long amount)
	{
		this->description = this->date_tday + " - " + customer_name + " : " + debitOrCredit + " : " + to_string(amount) + " Rs.";
	}

	string getDescription()
	{
		return this->description;
	}
};
#endif // TRANSACTION_H
