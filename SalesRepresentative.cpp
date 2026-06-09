#include "SalesRepresentative.h"
#include "Database.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void MainMenu();

void SalesRepresentative::SalesRepresentativeMenu() {
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

  switch(choice) {
    case 1:{
      system("cls");
      PrintSalesRepresentatives();
      break;
    }
    case 2:{
      system("cls");
      PrintSalesRepresentative();
      break;
    }
    case 3:{
      system("cls");
      AddSalesRepresentative();
      break;
    }
    case 4:{
      system("cls");
      ChangeSalesRepresentativeInfo();
      break;
    }
    case 5:{
      system("cls");
      SalesBonus();
      break;
    }
    case 6:{
      system("cls");
      MainMenu();
      break;
    }
    default:{
      system("cls");
      cout << "Invalid option" << endl;
      SalesRepresentativeMenu();
      break;
    }
  }
}

void SalesRepresentative::AddSalesRepresentative() {
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the name (don't add middle name): ";
  cin >> firstName >> lastName;
  cout << "Enter the sales representative's address (no spaces): ";
  cin >> shortAddress;
  cout << "Enter the sales representative's email address: ";
  cin >> emailAddress;
  cout << "Enter the sales: $";
  cin >> sales;

  const char* sql =
    "INSERT INTO sales_representatives (email, first_name, last_name, address, sales) "
    "VALUES (?, ?, ?, ?, ?);";

  if (Database::Prepare(sql, &statement, "adding sales representative")) {
    sqlite3_bind_text(statement, 1, emailAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, firstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, lastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, shortAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 5, sales);

    Database::StepDone(statement, "adding sales representative");
    sqlite3_finalize(statement);
  }

  SalesRepresentativeMenu();
}

void SalesRepresentative::PrintSalesRepresentatives() {
  sqlite3_stmt* statement = nullptr;
  int counter = 0;

  const char* sql =
    "SELECT first_name, last_name, address, email, sales "
    "FROM sales_representatives "
    "ORDER BY last_name, first_name;";

  if (Database::Prepare(sql, &statement, "listing sales representatives")) {
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

  if (counter == 0) {
    cout << "No sales representatives in the database" << endl;
  }

  SalesRepresentativeMenu();
}

void SalesRepresentative::PrintSalesRepresentative() {
  string inputEmailAddress;
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the sales representative's email address: ";
  cin >> inputEmailAddress;

  const char* sql =
    "SELECT first_name, last_name, address, email, sales "
    "FROM sales_representatives "
    "WHERE email = ?;";

  if (Database::Prepare(sql, &statement, "finding sales representative")) {
    sqlite3_bind_text(statement, 1, inputEmailAddress.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Name: " << Database::ColumnText(statement, 0) << " " << Database::ColumnText(statement, 1) << endl;
      cout << "Address: " << Database::ColumnText(statement, 2) << endl;
      cout << "Email address: " << Database::ColumnText(statement, 3) << endl;
      cout << "Sales: $" << sqlite3_column_int(statement, 4) << endl << endl;
    }
    else {
      cout << "Invalid sales representative" << endl << endl;
    }

    sqlite3_finalize(statement);
  }

  SalesRepresentativeMenu();
}

void SalesRepresentative::ChangeSalesRepresentativeInfo() {
  sqlite3_stmt* statement = nullptr;
  string oldEmailAddress, newFirstName, newLastName, newShortAddress, newEmailAddress;
  int newSales;

  cout << "Enter the sales representative's old email: ";
  cin >> oldEmailAddress;
  cout << "Enter new sales representatives's email: ";
  cin >> newEmailAddress;
  cout << "Enter new name (don't add middle name): ";
  cin >> newFirstName >> newLastName;
  cout << "Enter new address (no spaces): ";
  cin >> newShortAddress;
  cout << "Enter new sales amount: $";
  cin >> newSales;

  const char* sql =
    "UPDATE sales_representatives "
    "SET email = ?, first_name = ?, last_name = ?, address = ?, sales = ? "
    "WHERE email = ?;";

  if (Database::Prepare(sql, &statement, "updating sales representative")) {
    sqlite3_bind_text(statement, 1, newEmailAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, newFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, newLastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, newShortAddress.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 5, newSales);
    sqlite3_bind_text(statement, 6, oldEmailAddress.c_str(), -1, SQLITE_TRANSIENT);

    Database::StepDone(statement, "updating sales representative");
    sqlite3_finalize(statement);

    if (sqlite3_changes(Database::Connection()) == 0) {
      cout << "Invalid sales representative" << endl << endl;
    }
  }

  SalesRepresentativeMenu();
}

void SalesRepresentative::SalesBonus() {
  int ppw, commissionRate;

  cout << "What is the price per watt: $";
  cin >> ppw;
  cout << "What is the commission rate: $";
  cin >> commissionRate;
  cout << "Company generated lead: $" << ppw * commissionRate << endl;
  cout << "Self generated lead: $" << ppw * commissionRate + 50 << endl << endl;

  SalesRepresentativeMenu();
}
