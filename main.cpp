// R.Abinayan - 21/ENG/116
// M.Lalithambigai - 21/ENG/075
// T.F.Nusha - 21/ENG/138

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
					cout << "Enter the employee user name  (eg: employee001) : ";
					cin >> username;
					password = getPassword();
					employeeNameArray = bank.employeeNameArray;
					Employee employeeNow;
					for (int i = 0; i < employeeNameArray.size(); i++)
					{
						if (username == employeeNameArray[i] && password == "Password@1234")
						{
							employeeNow = bank.employeeArray[i];
							login_checker = 0;
							break;
						}

						login_checker = 1;
					}

					if (login_checker == 1)
					{
						cout << "Login unsuccessful"<<endl<<endl;
						login_checker = 0;
					}
					else
					{
						cout << "Successful login" << endl ;
						int checker_employee = 0;
						while (checker_employee != 1)
						{
						    string user_input_7;
							cout << "\ndate : " << Admin.getDate() << endl;
							float annualInterest = Admin.getAnnualSavingInterest();
							float overdraftCharge = Admin.getOverdraftCharge();
							cout << "Annual interest rate is " << annualInterest<<" percentage." << endl;
							cout << "Overdraft charge is " << overdraftCharge <<" percentage."<< endl;
							cout<<"Bank balance available : "<<bank.bank_balance<<" .Rs"<<endl<<endl;
							cout << "1. Create a customer account" << endl;
							cout << "2. Close the customer account" << endl;
							cout << "3. Deposit money in account" << endl;
							cout << "4. Withdraw money from account" << endl;
							cout << "5. View transactions" << endl;
							cout << "6. Logout" << endl;
							cout << "Select an option above : " ;
							cin >> user_input_7;
							while(user_input_7!="1"&&user_input_7!="2"&&user_input_7!="3"&&user_input_7!="4"&&user_input_7!="5"&&user_input_7!="6"){
                            cout<<"Invalid input! Select an option above (1 or 2 or 3 or 4 or 5 or 6): ";
                            cin>>user_input_7;
                            }
                            cout<<endl;
							user_input_3=stoi(user_input_7);
							switch (user_input_3)
							{
								case 1:
									{
										Customer customerCreated;
										customerCreated.setDate(Admin);
										employeeNow.createCustomer(customerCreated, bank, CustomerFile);
										break;
									}

								case 2:
									{
										string customerName;
										cout << "Enter the name of the customer: ";
										cin >> customerName;
										int customerNameCheck=0;
										for (int i = 0; i < bank.customerArray.size(); i++)
										{
											if (customerName == bank.customerArray[i].CustomerName)
											{
												bank.customerArray[i].setDate(Admin);
												employeeNow.closeCustomerAccount(bank.customerArray[i], CustomerFile);
												customerNameCheck=1;
												break;
											}
										}
										if(customerNameCheck==0){
                                            cout<<"No customer found with that name !"<<endl;
										}
										break;
									}

								case 3:
									{
										string customerName;
										int customerNameCheck=0;
										cout << "Enter the name of the customer: ";
										cin >> customerName;
										for (int i = 0; i < bank.customerArray.size(); i++)
										{
											if (customerName == bank.customerArray[i].CustomerName)
											{
												bank.customerArray[i].setDate(Admin);
												employeeNow.depositMoney(bank.customerArray[i], bank, CustomerFile, BankFile);
												customerNameCheck=1;
												break;
											}
										}
										if(customerNameCheck==0){
                                            cout<<"No customer found with that name !"<<endl;
										}
										break;
									}

								case 4:
									{
										string customerName;
										int customerNameCheck=0;
										cout << "Enter the name of the customer: ";
										cin >> customerName;
										for (int i = 0; i < bank.customerArray.size(); i++)
										{
											if (customerName == bank.customerArray[i].CustomerName)
											{
												bank.customerArray[i].setDate(Admin);
												employeeNow.withDrawMoney(bank.customerArray[i], bank, CustomerFile, BankFile);
												customerNameCheck=1;
												break;
											}
										}
										if(customerNameCheck==0){
                                            cout<<"No customer found with that name !"<<endl;
										}
										break;
									}

								case 5:
									{
										employeeNow.viewTransactions(bank);
										break;
									}

								case 6:
									{
										input = 0;
										checker_employee = 1;
										break;
									}

								default: {}
							}
						}
					}
				}
				else if (user_input_2 == "2")
				{
				    
					int customerArrayElement;
					cout << "Enter the customer user name (eg: customer001): ";
					cin >> username;
					password = getPassword();
					customerNameArray = bank.customerNameArray;
					Customer customer;
					login_checker = 1;
					for (int i = 0; i < customerNameArray.size(); i++)
					{
						if (username == customerNameArray[i] && password == "Password@1234")
						{
							customer = bank.customerArray[i];
							customerArrayElement = i;
							login_checker = 0;
							break;
						}

					}

					if (login_checker == 1)
					{
						cout << "Login unsuccessful"<<endl<<endl;
						login_checker = 0;
					}
					else
					{
						cout << "Successful login" << endl ;
						int checker_customer = 0;
						while (checker_customer != 1)
						{
							cout << "\ndate : " << Admin.getDate() << endl;
							float annualInterest = Admin.getAnnualSavingInterest();
							float overdraftCharge = Admin.getOverdraftCharge();
							cout << "Annual interest rate is " << annualInterest<<" percentage." << endl;
							cout << "Overdraft charge is " << overdraftCharge <<" percentage."<< endl;
							cout << "Account name : " << customer.CustomerName << endl;
							cout << "Account type : " << customer.accountType << endl;
							cout << "Account Contact details : " << customer.customerContact << endl;
							cout << "Account balance : " << customer.moneyDeposit << endl;
							cout << "Account overdraft : " << customer.overDraftNow << endl<<endl;
							string user_input_8;
							cout << "1. Deposit money in account" << endl;
							cout << "2. Withdraw money from account" << endl;
							cout << "3. View transactions" << endl;
							cout << "4. Logout" << endl;
							cout << "Select an option above : ";
							cin >> user_input_8;
							while(user_input_8!="1"&&user_input_8!="2"&&user_input_8!="3"&&user_input_8!="4"){
                            cout<<"Invalid input! Select an option above (1 or 2 or 3 or 4): ";
                            cin>>user_input_8;
                            }
							user_input_3=stoi(user_input_8);
							switch (user_input_3)
							{
								case 1:
									{
										if (customer.isClosed == false)
										{
											customer.setDate(Admin);
											customer.depositMoneyFun(bank, CustomerFile, BankFile);
											bank.customerArray[customerArrayElement] = customer;
										}
										else
										{
											cout << "Cannot do transaction. Account closed already." << endl;
										}

										break;
									}

								case 2:
									{
										if (customer.isClosed == false)
										{
											customer.setDate(Admin);
											customer.withdrawMoney(bank, CustomerFile, BankFile);
											bank.customerArray[customerArrayElement] = customer;
										}
										else
										{
											cout << "Cannot do transaction. Account closed already." << endl;
										}

										break;
									}

								case 3:
									{
										customer.viewTransaction();
										break;
									}

								case 4:
									{
										input = 0;
										checker_customer = 1;
										cout<<endl;
										break;
									}

								default: {}
							}
						}
					}
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
