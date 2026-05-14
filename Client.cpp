#include "Client.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

void MainMenu();

void Client::ClientMenu(){
  int choice;

  cout << "Clients" << endl;
  cout << endl;
  cout << "1: List current clients" << endl;
  cout << "2: Get info for a specific client" << endl;
  cout << "3: Add a new client" << endl;
  cout << "4: Update info for a specific client" << endl;
  cout << "5: Return to main menu" << endl;
  cout << endl;
  cout << "Select Choice: ";

  cin >> choice;

  switch(choice){
    case 1:{
      system("cls");
      PrintClients();
    }
    case 2:{
      system("cls");
      PrintClient();
    }
    case 3:{
      system("cls");
      AddClient();
    }
    case 4:{
      system("cls");
      ChangeClientInfo();
    }
    case 5:{
      system("cls");
      MainMenu();
    }
    default:{
      system("cls");
      cout << "Invalid option" << endl;
      ClientMenu();
    }
  }
}

void Client::AddClient(){
  clientsFS.open("Clients.txt", ios::app);

  cout << "Enter the name (don't add middle name): ";
  cin >> firstName >> lastName;
  cout << "Enter the client's address (no spaces): ";
  cin >> shortAddress;
  cout << "Enter the client's email address: ";
  cin >> emailAddress;
  cout << "Enter the sales: $";
  cin >> sales;

  clientsFS << emailAddress << " " << firstName << " " << lastName << " " << shortAddress  << " " << sales << endl;

  clientsFS.close();

  ClientMenu();
}

void Client::PrintClients(){
  int temp = 1;

  clientsFS.open("Clients.txt", ios::in);

  if (!clientsFS){
    cout << "No clients in the database";
    clientsFS.close();
  }

  if (clientsFS.is_open()){
    while (clientsFS >> emailAddress >> firstName >> lastName >> shortAddress >> sales){
      cout << "Name: " << firstName << " " << lastName << endl;
      cout << "Address: " << shortAddress << endl;
      cout << "Email address: " << emailAddress << endl;
      cout << "Sales: $" << sales << endl;
      cout << endl;
    }
      clientsFS.close();
  }

  if (temp == 0){
    cout << "No clients in the database" << endl;
  }

  ClientMenu();
}

void Client::PrintClient(){
  string inputEmailAddress;
  int counter = 0;

  clientsFS.open("Clients.txt", ios::in);

  cout << "Enter the client's email address: ";
  cin >> inputEmailAddress;

  while (!clientsFS.eof()){
    clientsFS >> emailAddress >> firstName >> lastName >> shortAddress >> sales;
    if (emailAddress == inputEmailAddress){
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Address: " << shortAddress << endl;
    cout << "Email address: " << emailAddress << endl;
    cout << "Sales: $" << sales << endl << endl;
    counter++;
    break;
    }
  }

  clientsFS.close();

  if (counter == 0){
    cout << "Invalid client" << endl << endl;
  }

  ClientMenu();
}

void Client::ChangeClientInfo(){
  fstream tempFS;
  string oldEmailAddress, newFirstName, newLastName, newShortAddress, newEmailAddress;
  int newSales, counter = 0;

  cout << "Enter the client's old email: ";
  cin >> oldEmailAddress;

  clientsFS.open("Clients.txt", ios::in);
  tempFS.open("TempClients.txt", ios::app | ios::out);

  while(clientsFS >> emailAddress >> firstName >> lastName >> shortAddress >> sales){
    if (emailAddress != oldEmailAddress){
      tempFS << emailAddress << " " << firstName << " " << lastName << " " << shortAddress  << " " << sales << endl;
    }
    else{
      cout << "Enter new client's email: ";
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
    cout << "Invalid client" << endl << endl;
  }

  clientsFS.close();
  tempFS.close();

  remove("Clients.txt");
  rename("TempClients.txt", "Clients.txt");

  ClientMenu();
}
