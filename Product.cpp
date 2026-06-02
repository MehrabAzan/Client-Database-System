#include "Product.h"
#include "Database.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void MainMenu();

void Product::ProductMenu(){
  int choice;

  cout << "Products" << endl;
  cout << endl;
  cout << "1: List current product" << endl;
  cout << "2: Get info for a specific product" << endl;
  cout << "3: Add a new product" << endl;
  cout << "4: Update info for a specific product" << endl;
  cout << "5: Monthly sales report" << endl;
  cout << "6: Return to main menu" << endl;
  cout << endl;
  cout << "Select Choice: ";

  cin >> choice;

  switch(choice){
    case 1:{
      system("cls");
      PrintProducts();
      break;
    }
    case 2:{
      system("cls");
      PrintProduct();
      break;
    }
    case 3:{
      system("cls");
      AddProduct();
      break;
    }
    case 4:{
      system("cls");
      ChangeProductInfo();
      break;
    }
    case 5:{
      system("cls");
      MonthlySalesReport();
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
      ProductMenu();
      break;
    }
  }
}

void Product::AddProduct(){
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the name: ";
  cin >> name;
  cout << "Enter the inverter type: ";
  cin >> inverterType;
  cout << "Enter the price: $";
  cin >> price;
  cout << "Enter the wattage: ";
  cin >> wattage;
  cout << "Enter the amount of sales: $";
  cin >> sales;
  cout << "Does this have a battery (only enter true or false): ";
  cin >> battery;

  const char* sql =
    "INSERT INTO products (name, price, wattage, inverter_type, battery, sales) "
    "VALUES (?, ?, ?, ?, ?, ?);";

  if (Database::Prepare(sql, &statement, "adding product")) {
    sqlite3_bind_text(statement, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 2, price);
    sqlite3_bind_int(statement, 3, wattage);
    sqlite3_bind_text(statement, 4, inverterType.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, battery.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 6, sales);

    Database::StepDone(statement, "adding product");
    sqlite3_finalize(statement);
  }

  ProductMenu();
}

void Product::PrintProducts(){
  sqlite3_stmt* statement = nullptr;
  int counter = 0;

  const char* sql =
    "SELECT name, price, wattage, inverter_type, battery, sales "
    "FROM products "
    "ORDER BY name;";

  if (Database::Prepare(sql, &statement, "listing products")) {
    while (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Name: " << Database::ColumnText(statement, 0) << endl;
      cout << "Price: $" << sqlite3_column_int(statement, 1) << endl;
      cout << "Wattage: " << sqlite3_column_int(statement, 2) << endl;
      cout << "Inverter Type: " << Database::ColumnText(statement, 3) << endl;
      cout << "Battery: " << Database::ColumnText(statement, 4) << endl;
      cout << "Sales: $" << sqlite3_column_int(statement, 5) << endl;
      cout << endl;
      counter++;
    }

    sqlite3_finalize(statement);
  }

  if (counter == 0){
    cout << "No products in the database" << endl;
  }

  ProductMenu();
}

void Product::PrintProduct(){
  string inputName;
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the product: ";
  cin >> inputName;

  const char* sql =
    "SELECT name, price, wattage, inverter_type, battery, sales "
    "FROM products "
    "WHERE name = ?;";

  if (Database::Prepare(sql, &statement, "finding product")) {
    sqlite3_bind_text(statement, 1, inputName.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(statement) == SQLITE_ROW) {
      cout << "Name: " << Database::ColumnText(statement, 0) << endl;
      cout << "Price: $" << sqlite3_column_int(statement, 1) << endl;
      cout << "Wattage: " << sqlite3_column_int(statement, 2) << endl;
      cout << "Inverter Type: " << Database::ColumnText(statement, 3) << endl;
      cout << "Battery: " << Database::ColumnText(statement, 4) << endl;
      cout << "Sales: $" << sqlite3_column_int(statement, 5) << endl << endl;
    }
    else {
      cout << "Invalid product" << endl << endl;
    }

    sqlite3_finalize(statement);
  }

  ProductMenu();
}

void Product::ChangeProductInfo(){
  sqlite3_stmt* statement = nullptr;
  string oldName, newName, newInverterType, newBattery;
  int newSales, newPrice, newWattage;

  cout << "Enter the old name: ";
  cin >> oldName;
  cout << "Enter the new name: ";
  cin >> newName;
  cout << "Enter the new price: ";
  cin >> newPrice;
  cout << "Enter the new wattage: ";
  cin >> newWattage;
  cout << "Enter the new inverter type: ";
  cin >> newInverterType;
  cout << "Enter if it has a battery or not: ";
  cin >> newBattery;
  cout << "Enter new sales amount: $";
  cin >> newSales;

  const char* sql =
    "UPDATE products "
    "SET name = ?, price = ?, wattage = ?, inverter_type = ?, battery = ?, sales = ? "
    "WHERE name = ?;";

  if (Database::Prepare(sql, &statement, "updating product")) {
    sqlite3_bind_text(statement, 1, newName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 2, newPrice);
    sqlite3_bind_int(statement, 3, newWattage);
    sqlite3_bind_text(statement, 4, newInverterType.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, newBattery.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 6, newSales);
    sqlite3_bind_text(statement, 7, oldName.c_str(), -1, SQLITE_TRANSIENT);

    Database::StepDone(statement, "updating product");
    sqlite3_finalize(statement);

    if (sqlite3_changes(Database::Connection()) == 0){
      cout << "Invalid product" << endl << endl;
    }
  }

  ProductMenu();
}

void Product::MonthlySalesReport(){
  string inputMonth;
  int inputYear, counter = 0;
  sqlite3_stmt* statement = nullptr;

  cout << "Enter the month: ";
  cin >> inputMonth;
  cout << "Enter the year: ";
  cin >> inputYear;

  const char* sql =
    "SELECT product_name, client_first_name, client_last_name, "
    "sales_rep_first_name, sales_rep_last_name, month, day, year "
    "FROM sales "
    "WHERE month = ? AND year = ? "
    "ORDER BY day;";

  if (Database::Prepare(sql, &statement, "building monthly sales report")) {
    sqlite3_bind_text(statement, 1, inputMonth.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 2, inputYear);

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
    cout << "No sales made this month" << endl << endl;
  }

  ProductMenu();
}
