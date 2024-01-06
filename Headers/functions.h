// T.F. Nusha - 21/ENG/138
// M. Lalithambigai - 21/ENG/075

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Customer.h"
#include "Bank.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
long checkTheMoneyInput(string numcheck);
string checkThePhoneNumberInput(string numcheck);
string getPassword();
void depositFromOutside(Bank &bank, Customer &customer, ofstream &MyFile, ofstream &BankFile);
#endif FUNCTIONS_H
