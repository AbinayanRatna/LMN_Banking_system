// R.Abinayan - 21/ENG/116

#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>

#include "Transaction.h"
#include "Employee.h"
#include "Bank.h"
#include "Customer.h"
using namespace std;
class Bank;
class Customer;
class Transaction;
class Employee;

class Administrator
{
	private:
	string date_tday;
	int dateIncreased = 0;

	public:
	void createEmployee(Bank & bank);
	void setDate();
	void increaseDate();
	void setAnnualSavingInterest();
	void setOverdraftCharge();
	void updateCustomerOverdraft(Customer & customer);
	void updateCustomerInterest(Customer &customer, Bank &bank, ofstream &BankFile);
	string getEmployeeName(Bank & bank);
	string getDate();

};

#endif // ADMINISTRATOR_H
