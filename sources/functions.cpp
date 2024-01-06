// R. Abinayan - 21/ENG/116

#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include "functions.h"
#include "Customer.h"
#include "Bank.h"
using namespace std;
long checkTheMoneyInput(string numcheck){
    string num;
    int n=0;
    while(n==0){
    for(int i=0;i<numcheck.length();i++){
        int checker_ascii_num=numcheck[i];
        if(checker_ascii_num>=48 && checker_ascii_num<=57){
            num+=numcheck[i];
            n=1;
        }else{
            num="";
            cout<<"Incorrect number. Input the correct value of money : ";
            cin>>numcheck;
             n=0;
            break;
        }
     }
    }
    long number=stol(num);
    return number;
}

string checkThePhoneNumberInput(string numcheck){
    string num;
    int n=0;
    while(n==0){
    if(numcheck.length()<=10 && numcheck.length()>9 ){
    for(int i=0;i<numcheck.length();i++){
        int checker_ascii_num=numcheck[i];
        if(checker_ascii_num>=48 && checker_ascii_num<=57){
            num+=numcheck[i];
            n=1;
        }else{
            num="";
            cout<<"Incorrect number. Input the correct phone number(10 digits) : ";
            cin>>numcheck;
             n=0;
            break;
        }
     }
    }else{
        num="";
        cout<<"Incorrect number. Input the correct phone number(10 digits) : ";
        cin>>numcheck;
        n=0;
    }
    }
    return num;
}

void depositFromOutside(Bank &bank, Customer &customer, ofstream &MyFile, ofstream &BankFile)
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

		for (int i = 0; i < bank.customerArray.size(); i++)
		{
			if (customer.CustomerName == bank.customerArray[i].CustomerName)
			{
				bank.customerArray[i].moneyDeposit = customer.moneyDeposit;
				bank.customerArray[i].overDraftNow = customer.overDraftNow;
				break;
			}
		}

		cout << "Money successfully deposited" << endl;
		MyFile << customer.date_tday << " - " << customer.CustomerName << " : Deposited " << now_deposited <<" Rs : Balance is "<<customer.moneyDeposit <<  endl;
	}
	else
	{
		cout << "Sorry. Account is already closed" << endl;
	}
}

string getPassword() {
    std::cout << "Enter password (Type as Password@1234): ";

    std::string password;
    char ch;
    while (true) {
        ch = _getch();  // Read a single character without echoing

        // If Enter key is pressed, terminate the loop
        if (ch == '\r') {
            std::cout << std::endl;
            break;
        }
        else if (ch == 8) {  // Backspace key (ASCII value 8)
            if (!password.empty()) {
                // Remove the last character from the password
                password.pop_back();
                std::cout << "\b \b";  // Move the cursor back, erase the character on the screen
            }
        }else if ( ch == 224) {
            // Do nothing
        }
        else {
            password += ch;
            std::cout << '*';  // Show asterisk instead of the actual character
        }
    }

    return password;
}
