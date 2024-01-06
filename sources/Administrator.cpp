// M. Lalithambigai - 21/ENG/075
#include "Administrator.h"
#include "Transaction.h"
#include "Employee.h"
#include "Bank.h"
#include "Customer.h"
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
int Administrator::employeeNumber(Bank & bank)
{
	return bank.employeeArray.size();
};

vector<string> Administrator::getEmployeeNameArray(Bank & bank)
{
	return bank.employeeNameArray;
};

void Administrator::createEmployee(Bank & bank)
{
	string startLetter = "";
	if (bank.employeeArray.size() < 9)
	{
		startLetter = "00";
	}
	else if (bank.employeeArray.size() < 99)
	{
		startLetter = "0";
	}

	string employeeName = ("employee" + startLetter + to_string((bank.employeeArray.size()) + 1));
	Employee employee;
	employee.setEmployeeName(employeeName);
	bank.employeeArray.push_back(employee);
	bank.employeeNameArray.push_back(employeeName);
	Employee lastCreatedEmployee = bank.employeeArray.back();
	cout << lastCreatedEmployee.getEmployeeName() + " : Employee created successfully" << endl;;
};

void Administrator::setDate()
{
	string date_tday;
	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);
	date_tday = to_string(1900 + local_time->tm_year) + ":" + to_string(1 + local_time->tm_mon) + ":" + to_string(local_time->tm_mday);
	this->date_tday = date_tday;
};

void Administrator::increaseDate()
{
	this->dateIncreased += 1;
	time_t ttime = time(0);
	ttime += (24 * 60 *60) *(this->dateIncreased);
	tm *local_time = localtime(&ttime);
	this->date_tday = to_string(1900 + local_time->tm_year) + ":" + to_string(1 + local_time->tm_mon) + ":" + to_string(local_time->tm_mday);
};

void Administrator::setAnnualSavingInterest()
{
	float annual_saving_interest;
	cout << "Enter the new annual saving interest : ";
	//cin >> annual_saving_interest;
	while(!(cin>>annual_saving_interest)){
        cout<<"Incorrect input! Enter the new annual saving interest : ";
        cin.clear();
        cin.ignore();
	}
	this->annual_saving_interest = annual_saving_interest;
	cout << "New annual savings interest is " << annual_saving_interest << endl;
};

void Administrator::setOverdraftCharge()
{
	float overdraftCharge;
	cout << "Enter the new overdraft charge(% per day) : ";
	cin >> overdraftCharge;
	this->overdraftCharge = overdraftCharge;
	cout << "New overdraft charge is " << overdraftCharge << endl;
};

void Administrator::updateCustomerOverdraft(Customer & customer)
{
	if (customer.overDraftNow > 0)
	{
		customer.overDraftNow += ((this->overdraftCharge) / 100) *(customer.overDraftNow);
		customer.moneyDeposit = (customer.overDraftNow) *(-1);
	}
}

void Administrator::updateCustomerInterest(Customer &customer, Bank &bank, ofstream &BankFile)
{
	float dailyInterest = (this->annual_saving_interest) / 365;
	if (customer.moneyDeposit > 0)
	{
		cout << "line-1" << endl;
		customer.moneyDeposit += ((dailyInterest) / 100) *(customer.moneyDeposit);
		bank.bank_balance -= ((dailyInterest) / 100) *(customer.moneyDeposit);
		BankFile << this->date_tday << " - " << customer.CustomerName << " : Interest debited in bank account : " << to_string(((dailyInterest) / 100) *(customer.moneyDeposit)) << " Rs." << endl;
		BankFile << this->date_tday << " - " << "Bank balance : " << bank.bank_balance << endl;
		Transaction transaction_now;
		transaction_now.setTransactionDate(this->date_tday);
		transaction_now.setDescription(customer.CustomerName, "Interest credited in customer account", ((dailyInterest) / 100) *(customer.moneyDeposit));
		bank.transactions.push_back(transaction_now);
		customer.transactions.push_back(transaction_now);
	}
}

string Administrator::getEmployeeName(Bank & bank)
{
	return bank.employeeArray.back().getEmployeeName();
}

string Administrator::getDate()
{
	return this->date_tday;
}

float Administrator::getAnnualSavingInterest()
{
	return (this->annual_saving_interest);
};

float Administrator::getOverdraftCharge()
{
	return (this->overdraftCharge);
};
