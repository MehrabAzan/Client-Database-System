#include "Product.h"
#include <cstdlib>
#include <cstdio>
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
    }
    case 2:{
      system("cls");
      PrintProduct();
    }
    case 3:{
      system("cls");
      AddProduct();
    }
    case 4:{
      system("cls");
      ChangeProductInfo();
    }
    case 5:{
      system("cls");
      MonthlySalesReport();
    }
    case 6:{
      system("cls");
      MainMenu();
    }
    default:{
      system("cls");
      cout << "Invalid option" << endl;
      ProductMenu();
    }
  }
}

void Product::AddProduct(){
  productsFS.open("Products.txt", ios::app);

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

  productsFS << name << " " << price << " " << wattage << " " << inverterType << " " << battery << " " << sales << endl;

  productsFS.close();

  ProductMenu();
}

void Product::PrintProducts(){
  int temp = 1;

  productsFS.open("Products.txt", ios::in);

  if (!productsFS){
    cout << "No products in the database";
    productsFS.close();
  }

  if (productsFS.is_open()){
    while (productsFS >> name >> price >> wattage >> inverterType >> battery >> sales){
      cout << "Name: " << name << endl;
      cout << "Price: $" << price << endl;
      cout << "Wattage: " << wattage << endl;
      cout << "Inverter Type: " << inverterType << endl;
      cout << "Battery: " << battery << endl;
      cout << "Sales: $" << sales << endl;
      cout << endl;
    }
    productsFS.close();
  }

  if (temp == 0){
    cout << "No products in the database" << endl;
  }

  ProductMenu();
}

void Product::PrintProduct(){
  string inputName;
  int counter = 0;

  productsFS.open("Products.txt", ios::in);

  cout << "Enter the product: ";
  cin >> inputName;

  while (!productsFS.eof()){
    productsFS >> name >> price >> wattage >> inverterType >> battery >> sales;
    if (name == inputName){
      cout << "Name: " << name << endl;
      cout << "Price: $" << price << endl;
      cout << "Wattage: " << wattage << endl;
      cout << "Inverter Type: " << inverterType << endl;
      cout << "Battery: " << battery << endl;
      cout << "Sales: $" << sales << endl << endl;
      counter++;
      break;
    }
  }

  productsFS.close();

  if (counter == 0){
    cout << "Invalid product" << endl << endl;
  }

  ProductMenu();
}

void Product::ChangeProductInfo(){
  fstream tempFS;
  string oldName, newName, newInverterType, newBattery;
  int newSales, newPrice, newWattage, counter = 0;

  cout << "Enter the old name: ";
  cin >> oldName;

  productsFS.open("Products.txt", ios::in);
  tempFS.open("TempProducts.txt", ios::app | ios::out);

  while(productsFS >> name >> price >> wattage >> inverterType >> battery >> sales){
    if (name != oldName){
      tempFS << name << " " << price << " " << wattage << " " << inverterType << " " << battery << " " << sales << endl;
    }
    else{
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

      tempFS << newName << " " << newPrice << " " << newWattage << " " << newInverterType << " " << newBattery << " " << newSales << endl;

      counter++;
    }
  }

  if (counter == 0){
    cout << "Invalid product" << endl << endl;
  }

  productsFS.close();
  tempFS.close();
  
  remove("Products.txt");
  rename("TempProducts.txt", "Products.txt");

  ProductMenu();
}

void Product::MonthlySalesReport(){
  string inputMonth, clientFirstName, clientLastName, productName, salesRepresentativeFirstName, salesRepresentativeLastName, month;
  int inputYear, year, day, counter = 0;
  fstream salesFS;

  salesFS.open("Sales.txt", ios::in);

  cout << "Enter the month: ";
  cin >> inputMonth;
  cout << "Enter the year: ";
  cin >> inputYear;

  while (!salesFS.eof()){
    salesFS >> productName >> clientFirstName >>  clientLastName >> salesRepresentativeFirstName >> salesRepresentativeLastName >> month >> day >> year;

    if (month == inputMonth && inputYear == year){
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
    cout << "No sales made this month" << endl << endl;
  }

  ProductMenu();
}
