#include "Sale.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

void MainMenu();

void Sale::SaleMenu(){
  int choice;

  cout << "Sales" << endl;
  cout << endl;
  cout << "1: List current sales from a specific year" << endl;
  cout << "2: Add a sale" << endl;
  cout << "3: List current sales from a specific year from a specific client" << endl;
  cout << "4: Update info for a specific sale" << endl;
  cout << "5: Return to main menu" << endl;
  cout << endl;
  cout << "Select Choice: ";

  cin >> choice;

  switch(choice){
    case 1:{
      system("cls");
      SalesFromYear();
    }
    case 2:{
      system("cls");
      AddSale();
    }
    case 3:{
      system("cls");
      SalesFromYearFromSpecificClient();
    }
    case 4:{
      system("cls");
      ChangeSaleInfo();
    }
    case 5:{
      system("cls");
      MainMenu();
    }
    default:{
      system("cls");
      cout << "Invalid option" << endl;
      SaleMenu();
    }
  }
}

void Sale::AddSale(){
  salesFS.open("Sales.txt", ios::app);

  cout << "Enter the client (don't add middle name): ";
  cin >> clientFirstName >> clientLastName;
  cout << "Enter the product: ";
  cin >> productName;
  cout << "Enter the sales representative (don't add middle name): ";
  cin >> salesRepresentativeFirstName >> salesRepresentativeLastName;
  cout << "Enter the month this sale occured (Enter the full month name): ";
  cin >> month;
  cout << "Enter the year this sale occured: ";
  cin >> year;
  cout << "Enter the day in the month this sale occured: ";
  cin >> day;

  salesFS << productName << " " << clientFirstName << " " << clientLastName << " " << salesRepresentativeFirstName << " " << salesRepresentativeLastName  << " " << month << " " << day << " " << year << endl;

  salesFS.close();

  SaleMenu();
}

void Sale::SalesFromYear(){
  int inputYear, counter = 0;

  salesFS.open("Sales.txt", ios::in);

  cout << "Enter the year: ";
  cin >> inputYear;

  while (!salesFS.eof()){
    salesFS >> productName >> clientFirstName >>  clientLastName >> salesRepresentativeFirstName >> salesRepresentativeLastName >> month >> day >> year;
    if(inputYear == year){
      cout << "Product: " << productName << endl;
      cout << "Client name: " << clientFirstName << " " << clientLastName << endl;
      cout << "Sales representative name: " << salesRepresentativeFirstName << " " << salesRepresentativeLastName << endl;
      cout << "Date: " << month << " " << day << ", " << year << endl;
      cout << endl;
      counter++;
    }
  }

  salesFS.close();

  if (counter == 0){
    cout << "No sales from " << inputYear << endl << endl;
  }

  SaleMenu();
}

void Sale::SalesFromYearFromSpecificClient(){
  int inputYear, counter = 0;
  string inputClientFirstName, inputClientLastName;

  salesFS.open("Sales.txt", ios::in);

  cout << "Enter the year: ";
  cin >> inputYear;
  cout << "Enter the client's first name: ";
  cin >> inputClientFirstName;
  cout << "Enter the client's last name: ";
  cin >> inputClientLastName;

  while (!salesFS.eof()){
    salesFS >> productName >> clientFirstName >>  clientLastName >> salesRepresentativeFirstName >> salesRepresentativeLastName >> month >> day >> year;
    if(inputYear == year && inputClientFirstName == clientFirstName && inputClientLastName == clientLastName){
      cout << "Product: " << productName << endl;
      cout << "Client name: " << clientFirstName << " " << clientLastName << endl;
      cout << "Sales representative name: " << salesRepresentativeFirstName << " " << salesRepresentativeLastName << endl;
      cout << "Date: " << month << " " << day << ", " << year << endl;
      cout << endl;
      counter++;
    }
  }

  salesFS.close();

  if (counter == 0){
    cout << "No sales from " << inputYear << " from " << inputClientFirstName << " " << inputClientLastName << endl << endl;
  }

  SaleMenu();
}

void Sale::ChangeSaleInfo(){
  fstream tempFS;
  string oldProductName, newProductName, newClientFirstName, newClientLastName, newSalesRepresentativeFirstName, newSalesRepresentativeLastName, newMonth;
  int newYear, newDay, counter = 0;

  cout << "Enter product: ";
  cin >> oldProductName;

  salesFS.open("Sales.txt", ios::in);
  tempFS.open("TempSales.txt", ios::app | ios::out);

  while(salesFS >> productName >> clientFirstName >>  clientLastName >> salesRepresentativeFirstName >> salesRepresentativeLastName >> month >> day >> year){
    if (productName != oldProductName){
      tempFS << productName << " " << clientFirstName << " " << clientLastName << " " << salesRepresentativeFirstName << " " << salesRepresentativeLastName  << " " << month << " " << day << " " << year << endl;
    }
    else{
      cout << "Enter the product: ";
      cin >> newProductName;
      cout << "Enter the client name (don't add middle name): ";
      cin >> newClientFirstName >> newClientLastName;
      cout << "Enter the new sales representative name (don't add middle name): ";
      cin >> newSalesRepresentativeFirstName >> newSalesRepresentativeLastName;
      cout << "Enter the month: ";
      cin >> newMonth;
      cout << "Enter the day of the month: ";
      cin >> day;
      cout << "Enter the year: ";
      cin >> newYear;

      tempFS << newProductName << " " << newClientFirstName << " " << newClientLastName << " " << newSalesRepresentativeFirstName << " " << newSalesRepresentativeLastName  << " " << newMonth << " " << newDay << " " << newYear << endl;

      counter++;
    }
  }

  if (counter == 0){
    cout << "Invalid sale" << endl << endl;
  }

  salesFS.close();
  tempFS.close();
  
  remove("Sales.txt");
  rename("TempSales.txt", "Sales.txt");

  SaleMenu();
}
