#include "SalesRepresentative.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

void MainMenu();

void SalesRepresentative::SalesRepresentativeMenu(){
  int choice;

  cout << "Sales Representatives" << endl;
  cout << endl;
  cout << "1: List current sales representatives" << endl;
  cout << "2: Get info for a specific sales representative" << endl;
  cout << "3: Add a new sales representative" << endl;
  cout << "4: Update info for a specific sales representative" << endl;
  cout << "5: Calculate sales bonus" << endl;
  cout << "6: Return to main menu" << endl;
  cout << endl;
  cout << "Select Choice: ";

  cin >> choice;

  switch(choice){
    case 1:{
      system("cls");
      PrintSalesRepresentatives();
    }
    case 2:{
      system("cls");
      PrintSalesRepresentative();
    }
    case 3:{
      system("cls");
      AddSalesRepresentative();
    }
    case 4:{
      system("cls");
      ChangeSalesRepresentativeInfo();
    }
    case 5:{
      system("cls");
      SalesBonus();
    }
    case 6:{
      system("cls");
      MainMenu();
    }
    default:{
      system("cls");
      cout << "Invalid option" << endl;
      SalesRepresentativeMenu();
    }
  }
}

void SalesRepresentative::AddSalesRepresentative(){
  salesRepresentativesFS.open("SalesRepresentatives.txt", ios::app);


  cout << "Enter the name (don't add middle name): ";
  cin >> firstName >> lastName;
  cout << "Enter the sales representative's address (no spaces): ";
  cin >> shortAddress;
  cout << "Enter the sales representative's email address: ";
  cin >> emailAddress;
  cout << "Enter the sales: $";
  cin >> sales;

  salesRepresentativesFS << emailAddress << " " << firstName << " " << lastName << " " << shortAddress  << " " << sales << endl;

  salesRepresentativesFS.close();

  SalesRepresentativeMenu();
}

void SalesRepresentative::PrintSalesRepresentatives(){
  int temp = 1;

  salesRepresentativesFS.open("SalesRepresentatives.txt", ios::in);

  if (!salesRepresentativesFS){
    cout << "No sales representatives in the database" << endl;
    salesRepresentativesFS.close();
  }


  if (salesRepresentativesFS.is_open()){
    while (salesRepresentativesFS >> emailAddress >> firstName >> lastName >> shortAddress >> sales){
      cout << "Name: " << firstName << " " << lastName << endl;
      cout << "Address: " << shortAddress << endl;
      cout << "Email address: " << emailAddress << endl;
      cout << "Sales: $" << sales << endl;
      cout << endl;
    }
    salesRepresentativesFS.close();
  }

  if (temp == 0){
    cout << "No sales representatives in the database" << endl;
  }

  SalesRepresentativeMenu();
}

void SalesRepresentative::PrintSalesRepresentative(){
    string inputEmailAddress;
    int counter = 0;

    salesRepresentativesFS.open("SalesRepresentatives.txt", ios::in);

    cout << "Enter the sales representative's email address: ";
    cin >> inputEmailAddress;

    while (!salesRepresentativesFS.eof()){
      salesRepresentativesFS >> emailAddress >> firstName >> lastName >> shortAddress >> sales;
      if (emailAddress == inputEmailAddress){
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Address: " << shortAddress << endl;
        cout << "Email address: " << emailAddress << endl;
        cout << "Sales: $" << sales << endl << endl;
        counter++;
        break;
      }
    }

    salesRepresentativesFS.close();

    if (counter == 0){
      cout << "Invalid sales representative" << endl << endl;
    }

    SalesRepresentativeMenu();
}

void SalesRepresentative::ChangeSalesRepresentativeInfo(){
  fstream tempFS;
  string oldEmailAddress, newFirstName, newLastName, newShortAddress, newEmailAddress;
  int newSales, counter = 0;

  cout << "Enter the sales representative's old email: ";
  cin >> oldEmailAddress;

  salesRepresentativesFS.open("SalesRepresentatives.txt", ios::in);
  tempFS.open("TempSalesRepresentatives.txt", ios::app | ios::out);

  while(salesRepresentativesFS >> emailAddress >> firstName >> lastName >> shortAddress >> sales){
    if (emailAddress != oldEmailAddress){
      tempFS << emailAddress << " " << firstName << " " << lastName << " " << shortAddress  << " " << sales << endl;
    }
    else{
      cout << "Enter new sales representatives's email: ";
      cin >> newEmailAddress;
      cout << "Enter new name (don't add middle name): ";
      cin >> newFirstName >> newLastName;
      cout << "Enter new address (no spaces): ";
      cin >> newShortAddress;
      cout << "Enter new sales amount: $";
      cin >> newSales;

      tempFS << newEmailAddress << " " << newFirstName << " " << newLastName << " " << newShortAddress << " " << newSales << endl;

      counter++;
    }
  }

  if (counter == 0){
    cout << "Invalid sales representative" << endl << endl;
  }

  salesRepresentativesFS.close();
  tempFS.close();
  
  remove("SalesRepresentatives.txt");
  rename("TempSalesRepresentatives.txt", "SalesRepresentatives.txt");

  SalesRepresentativeMenu();
}

void SalesRepresentative::SalesBonus(){
  int ppw, commissionRate;

  cout << "What is the price per watt: $";
  cin >> ppw;
  cout << "What is the commission rate: $";
  cin >> commissionRate;
  cout << "Company generated lead: $" << ppw * commissionRate << endl;
  cout << "Self generated lead: $" << ppw * commissionRate + 50 << endl << endl;

  SalesRepresentativeMenu();
}
