#include "Client.h"
#include "Database.h"
#include <cstdlib>
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
      break;
    }
    case 2:{
      system("cls");
      PrintClient();
      break;
    }
    case 3:{
      system("cls");
      AddClient();
      break;
    }
    case 4:{
      system("cls");
      ChangeClientInfo();
      break;
    }
    case 5:{
      system("cls");
      MainMenu();
      break;
    }
    default:{
      system("cls");
      cout << "Invalid option" << endl;
      ClientMenu();
      break;
    }
  }
}

void Client::AddClient(){
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the name (don't add middle name): ";
  cin >> firstName >> lastName;
  cout << "Enter the client's address (no spaces): ";
  cin >> shortAddress;
  cout << "Enter the client's email address: ";
  cin >> emailAddress;
  cout << "Enter the sales: $";
  cin >> sales;

  const char* sql =
    "INSERT INTO clients (email, first_name, last_name, address, sales) "
    "VALUES (?, ?, ?, ?, ?);";

  if (Database::Prepare(sql, &statement, "adding client")) {
    sqlite3_bind_text(statement, 1, emailAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, firstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, lastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, shortAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 5, sales);

    Database::StepDone(statement, "adding client");
    sqlite3_finalize(statement);
  }

  ClientMenu();
}

void Client::PrintClients(){
  sqlite3_stmt* statement = nullptr;
  int counter = 0;

  const char* sql =
    "SELECT first_name, last_name, address, email, sales "
    "FROM clients "
    "ORDER BY last_name, first_name;";

  if (Database::Prepare(sql, &statement, "listing clients")) {
    while (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Name: " << Database::ColumnText(statement, 0) << " " << Database::ColumnText(statement, 1) << endl;
      cout << "Address: " << Database::ColumnText(statement, 2) << endl;
      cout << "Email address: " << Database::ColumnText(statement, 3) << endl;
      cout << "Sales: $" << sqlite3_column_int(statement, 4) << endl;
      cout << endl;
      counter++;
    }

    sqlite3_finalize(statement);
  }

  if (counter == 0){
    cout << "No clients in the database" << endl;
  }

  ClientMenu();
}

void Client::PrintClient(){
  string inputEmailAddress;
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the client's email address: ";
  cin >> inputEmailAddress;

  const char* sql =
    "SELECT first_name, last_name, address, email, sales "
    "FROM clients "
    "WHERE email = ?;";

  if (Database::Prepare(sql, &statement, "finding client")) {
    sqlite3_bind_text(statement, 1, inputEmailAddress.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Name: " << Database::ColumnText(statement, 0) << " " << Database::ColumnText(statement, 1) << endl;
      cout << "Address: " << Database::ColumnText(statement, 2) << endl;
      cout << "Email address: " << Database::ColumnText(statement, 3) << endl;
      cout << "Sales: $" << sqlite3_column_int(statement, 4) << endl << endl;
    }
    else {
      cout << "Invalid client" << endl << endl;
    }

    sqlite3_finalize(statement);
  }

  ClientMenu();
}

void Client::ChangeClientInfo(){
  sqlite3_stmt* statement = nullptr;
  string oldEmailAddress, newFirstName, newLastName, newShortAddress, newEmailAddress;
  int newSales;

  cout << "Enter the client's old email: ";
  cin >> oldEmailAddress;
  cout << "Enter new client's email: ";
  cin >> newEmailAddress;
  cout << "Enter new name (don't add middle name): ";
  cin >> newFirstName >> newLastName;
  cout << "Enter new address (no spaces): ";
  cin >> newShortAddress;
  cout << "Enter new sales amount: $";
  cin >> newSales;

  const char* sql =
    "UPDATE clients "
    "SET email = ?, first_name = ?, last_name = ?, address = ?, sales = ? "
    "WHERE email = ?;";

  if (Database::Prepare(sql, &statement, "updating client")) {
    sqlite3_bind_text(statement, 1, newEmailAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, newFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, newLastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, newShortAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 5, newSales);
    sqlite3_bind_text(statement, 6, oldEmailAddress.c_str(), -1, SQLITE_TRANSIENT);

    Database::StepDone(statement, "updating client");
    sqlite3_finalize(statement);

    if (sqlite3_changes(Database::Connection()) == 0){
      cout << "Invalid client" << endl << endl;
    }
  }

  ClientMenu();
}
