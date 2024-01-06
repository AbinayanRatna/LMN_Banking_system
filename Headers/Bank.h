//M. Lalithambigai - 21/ENG/075

#ifndef BANK_H
#define BANK_H
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include "Administrator.h"
#include "Transaction.h"
#include "Employee.h"
#include "Customer.h"
using namespace std;
class Customer;
class Transaction;
class Employee;
class Administrator;

class Bank
{
	public:
    vector<Employee> employeeArray;
	vector<string> employeeNameArray;
	vector<Customer> customerArray;
	vector<string> customerNameArray;
	vector<Transaction> transactions;
	long bank_balance = 1000000;
};

#endif
