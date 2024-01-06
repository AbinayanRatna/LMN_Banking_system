// R.Abinayan - 21/ENG/116

#include <iostream>
#include "Administrator.h"
#include "Employee.h"
#include "Customer.h"
#include "Transaction.h"
#include "Bank.h"
#include "functions.h"
#include <conio.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	Bank bank;
	vector<string> employeeNameArray;
	vector<string> customerNameArray;
	ofstream BankFile("Bank.txt");
	ofstream CustomerFile("Customer_details.txt");
	fstream BankFile_handler;
	fstream CustomerFile_handler;

	BankFile_handler.open("Bank.txt", ios:: in | ios::out);
	CustomerFile_handler.open("Customer_details.txt", ios:: in | ios::out);
	cout<<"\t\tWelcome to LMN banking\n\n";
	if (!BankFile_handler)
	{
		cout << "Bank File did not open!";
		exit(1);
	}

	if (!CustomerFile_handler)
	{
		cout << "Customer details File did not open!";
		exit(1);
	}

	int input = 1, user_input_3;
	string user_input_1,user_input_2,user_input_6;
	Administrator Admin;
	Admin.setDate();
	string username, password;
	while (input != 0)
	{

		cout << "1. Deposit as an outside source." << endl;
		cout << "2. Login." << endl;
		cout<<"3. Exit"<<endl;
		cout << "Select an option above(1 or 2 or 3) : ";
		cin >> user_input_1;
		while(user_input_1!="1" && user_input_1!="2" && user_input_1!="3" ){
            cout<<"Incorrect input. Please Select an option above(1 or 2 or 3) : ";
		    cin >> user_input_1;
		}
		cout<<endl;
		if (user_input_1 == "2")
		{
			int login_checker = 0;
			while (login_checker != 1)
			{
				cout << "1. Enter as administrator ." << endl;
				cout << "2. Enter as customer ." << endl;
				cout << "3. Enter as employee ." << endl;
				cout << "4. Back" << endl;
				cout << "Select an option above : " ;

				cin >> user_input_2;
				while(user_input_2!="1" && user_input_2!="2" && user_input_2!="3" && user_input_2!="4"){
                cout<<"Incorrect input. Please Select an option above(1 or 2 or 3 or 4) : ";
		        cin >> user_input_2;
		    }
		        cout<<endl;
				if (user_input_2 == "1")
				{
					cout << "Enter the user name(Type as Admin) : ";
					cin >> username;
					password = getPassword();

					while (username != "Admin" || password != "Password@1234")
					{
						cout << "Incorrect credentials. Please try again.." << endl;
						cout << "Enter the user name (Type as Admin): ";
						cin >> username;
						password = getPassword();
					}
					cout << endl;
					cout << "Successful login" << endl;
					int checker_admin = 0;
					while (checker_admin != 1)
					{
						cout << "\ndate : " << Admin.getDate() << endl;
						float annualInterest = Admin.getAnnualSavingInterest();
						float overdraftCharge = Admin.getOverdraftCharge();
						cout << "Annual interest rate is " << annualInterest <<" percentage."<< endl;
						cout << "Overdraft charge is " << overdraftCharge <<" percentage."<< endl;
						cout << "Bank balance now :  " << bank.bank_balance <<" Rs."<< endl << endl;
						cout << "1. Create an employee" << endl;
						cout << "2. Increase the date" << endl;
						cout << "3. Change overdraft charge" << endl;
						cout << "4. Change annual savings interest" << endl;
						cout << "5. Logout" << endl;
						cout << "Select an option above : " ;
						cin>>user_input_6;
						while(user_input_6!="1"&&user_input_6!="2"&&user_input_6!="3"&&user_input_6!="4"&&user_input_6!="5"){
                            cout<<"Invalid input! Select an option above (1 or 2 or 3 or 4 or 5): ";
                            cin>>user_input_6;
						}
						cout<<endl;
						user_input_3=stoi(user_input_6);
						switch (user_input_3)
						{
							case 1:
								{
									Admin.createEmployee(bank);
									Employee employee;
									break;
								}

							case 2:
								{
									Admin.increaseDate();
									if (bank.customerArray.size() > 0)
									{
										for (int i = 0; i < bank.customerArray.size(); i++)
										{
											Admin.updateCustomerInterest(bank.customerArray[i], bank, BankFile);
											Admin.updateCustomerOverdraft(bank.customerArray[i]);
										}
									}

									break;
								}

							case 3:
								{
									Admin.setOverdraftCharge();
									break;
								}

							case 4:
								{
									Admin.setAnnualSavingInterest();
									break;
								}

							case 5:
								{
									input = 0;
									checker_admin = 1;
									break;
								}

							default: {}
						}
					}
				}
				else if (user_input_2 == "4")
				{
					login_checker = 1;
					input = 1;
					break;
				}
				else if (user_input_2 == "3")
				{

				}
				else if (user_input_2 == "2")
				{

				}
			}
		}
		else if (user_input_1 == "1")
		{
			string customerUserName;
			int isSuccess = 0;
			cout << "Enter the customer name : ";
			cin >> customerUserName;
			for (int i = 0; i < bank.customerArray.size(); i++)
			{
				if (customerUserName == bank.customerNameArray[i])
				{
					bank.customerArray[i].setDate(Admin);
					depositFromOutside(bank, bank.customerArray[i], CustomerFile, BankFile);
					isSuccess = 1;
					break;
				}
			}

			if (isSuccess == 0)
			{
				cout << "Transaction unsuccessful. Customer is not found." << endl<<endl;
			}
		}
		else if(user_input_1=="3"){
            input=0;
		}
	}

	return 0;
}
