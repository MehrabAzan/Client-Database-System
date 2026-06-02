#include "Sale.h"
#include "Database.h"
#include <cstdlib>
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
      break;
    }
    case 2:{
      system("cls");
      AddSale();
      break;
    }
    case 3:{
      system("cls");
      SalesFromYearFromSpecificClient();
      break;
    }
    case 4:{
      system("cls");
      ChangeSaleInfo();
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
      SaleMenu();
      break;
    }
  }
}

void Sale::AddSale(){
  sqlite3_stmt* statement = nullptr;

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

  const char* sql =
    "INSERT INTO sales (product_name, client_first_name, client_last_name, "
    "sales_rep_first_name, sales_rep_last_name, month, day, year) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

  if (Database::Prepare(sql, &statement, "adding sale")) {
    sqlite3_bind_text(statement, 1, productName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, clientFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, clientLastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, salesRepresentativeFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, salesRepresentativeLastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 6, month.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 7, day);
    sqlite3_bind_int(statement, 8, year);

    Database::StepDone(statement, "adding sale");
    sqlite3_finalize(statement);
  }

  SaleMenu();
}

void Sale::SalesFromYear(){
  int inputYear, counter = 0;
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the year: ";
  cin >> inputYear;

  const char* sql =
    "SELECT product_name, client_first_name, client_last_name, "
    "sales_rep_first_name, sales_rep_last_name, month, day, year "
    "FROM sales "
    "WHERE year = ? "
    "ORDER BY month, day;";

  if (Database::Prepare(sql, &statement, "listing sales from year")) {
    sqlite3_bind_int(statement, 1, inputYear);

    while (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Product: " << Database::ColumnText(statement, 0) << endl;
      cout << "Client name: " << Database::ColumnText(statement, 1) << " " << Database::ColumnText(statement, 2) << endl;
      cout << "Sales representative name: " << Database::ColumnText(statement, 3) << " " << Database::ColumnText(statement, 4) << endl;
      cout << "Date: " << Database::ColumnText(statement, 5) << " " << sqlite3_column_int(statement, 6) << ", " << sqlite3_column_int(statement, 7) << endl;
      cout << endl;
      counter++;
    }

    sqlite3_finalize(statement);
  }

  if (counter == 0){
    cout << "No sales from " << inputYear << endl << endl;
  }

  SaleMenu();
}

void Sale::SalesFromYearFromSpecificClient(){
  int inputYear, counter = 0;
  string inputClientFirstName, inputClientLastName;
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the year: ";
  cin >> inputYear;
  cout << "Enter the client's first name: ";
  cin >> inputClientFirstName;
  cout << "Enter the client's last name: ";
  cin >> inputClientLastName;

  const char* sql =
    "SELECT product_name, client_first_name, client_last_name, "
    "sales_rep_first_name, sales_rep_last_name, month, day, year "
    "FROM sales "
    "WHERE year = ? AND client_first_name = ? AND client_last_name = ? "
    "ORDER BY month, day;";

  if (Database::Prepare(sql, &statement, "listing sales from year and client")) {
    sqlite3_bind_int(statement, 1, inputYear);
    sqlite3_bind_text(statement, 2, inputClientFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, inputClientLastName.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Product: " << Database::ColumnText(statement, 0) << endl;
      cout << "Client name: " << Database::ColumnText(statement, 1) << " " << Database::ColumnText(statement, 2) << endl;
      cout << "Sales representative name: " << Database::ColumnText(statement, 3) << " " << Database::ColumnText(statement, 4) << endl;
      cout << "Date: " << Database::ColumnText(statement, 5) << " " << sqlite3_column_int(statement, 6) << ", " << sqlite3_column_int(statement, 7) << endl;
      cout << endl;
      counter++;
    }

    sqlite3_finalize(statement);
  }

  if (counter == 0){
    cout << "No sales from " << inputYear << " from " << inputClientFirstName << " " << inputClientLastName << endl << endl;
  }

  SaleMenu();
}

void Sale::ChangeSaleInfo(){
  sqlite3_stmt* statement = nullptr;
  string oldProductName, newProductName, newClientFirstName, newClientLastName, newSalesRepresentativeFirstName, newSalesRepresentativeLastName, newMonth;
  int newYear, newDay;

  cout << "Enter product: ";
  cin >> oldProductName;
  cout << "Enter the product: ";
  cin >> newProductName;
  cout << "Enter the client name (don't add middle name): ";
  cin >> newClientFirstName >> newClientLastName;
  cout << "Enter the new sales representative name (don't add middle name): ";
  cin >> newSalesRepresentativeFirstName >> newSalesRepresentativeLastName;
  cout << "Enter the month: ";
  cin >> newMonth;
  cout << "Enter the day of the month: ";
  cin >> newDay;
  cout << "Enter the year: ";
  cin >> newYear;

  const char* sql =
    "UPDATE sales "
    "SET product_name = ?, client_first_name = ?, client_last_name = ?, "
    "sales_rep_first_name = ?, sales_rep_last_name = ?, month = ?, day = ?, year = ? "
    "WHERE product_name = ?;";

  if (Database::Prepare(sql, &statement, "updating sale")) {
    sqlite3_bind_text(statement, 1, newProductName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, newClientFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, newClientLastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, newSalesRepresentativeFirstName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, newSalesRepresentativeLastName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 6, newMonth.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 7, newDay);
    sqlite3_bind_int(statement, 8, newYear);
    sqlite3_bind_text(statement, 9, oldProductName.c_str(), -1, SQLITE_TRANSIENT);

    Database::StepDone(statement, "updating sale");
    sqlite3_finalize(statement);

    if (sqlite3_changes(Database::Connection()) == 0){
      cout << "Invalid sale" << endl << endl;
    }
  }

  SaleMenu();
}
