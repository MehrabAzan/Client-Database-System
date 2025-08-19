#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void MainMenu();

class Client{
  public:
    void ClientMenu(){
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

    void AddClient(){
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

    void PrintClients(){
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

    void PrintClient(){
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

    void ChangeClientInfo(){
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
  private:
    string firstName, lastName, shortAddress, emailAddress;
    int sales;
    fstream clientsFS;
};

class SalesRepresentative{
  public:
    void SalesRepresentativeMenu(){
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

    void AddSalesRepresentative(){
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

    void PrintSalesRepresentatives(){
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

    void PrintSalesRepresentative(){
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

    void ChangeSalesRepresentativeInfo(){
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

    void SalesBonus(){
      int ppw, commissionRate;

      cout << "What is the price per watt: $";
      cin >> ppw;
      cout << "What is the commission rate: $";
      cin >> commissionRate;
      cout << "Company generated lead: $" << ppw * commissionRate << endl;
      cout << "Self generated lead: $" << ppw * commissionRate + 50 << endl << endl;

      SalesRepresentativeMenu();
    }
  private:
    string firstName, lastName, shortAddress, emailAddress;
    int sales;
    fstream salesRepresentativesFS;
};

class Product{
  public:
    void ProductMenu(){
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

    void AddProduct(){
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

    void PrintProducts(){
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

    void PrintProduct(){
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

    void ChangeProductInfo(){
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

    void MonthlySalesReport(){
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
  private:
    string name, inverterType, battery;
    int price, sales, wattage;
    fstream productsFS;
};

class Sale{
  public:
    void SaleMenu(){
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

    void AddSale(){
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

    void SalesFromYear(){
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

    void SalesFromYearFromSpecificClient(){
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

    void ChangeSaleInfo(){
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
  private:
    string clientFirstName, clientLastName, productName, salesRepresentativeFirstName, salesRepresentativeLastName, month;
    int year, day;
    fstream salesFS;
};

void MainMenu(){
  int choice;

  cout << "SeerSolar" << endl;
  cout << endl;
  cout << "1: Clients" << endl;
  cout << "2: Sales Representatives" << endl;
  cout << "3: Products" << endl;
  cout << "4: Sales" << endl;
  cout << "5: Exit" << endl;
  cout << endl;
  cout << "Select Choice: ";

  cin >> choice;

  switch(choice){
    case 1:{
      system("cls");
      Client client;
      client.ClientMenu();
    }
    case 2:{
      system("cls");
      SalesRepresentative salesRepresentative;
      salesRepresentative.SalesRepresentativeMenu();
    }
    case 3:{
      system("cls");
      Product product;
      product.ProductMenu();
    }
    case 4:{
      system("cls");
      Sale sale;
      sale.SaleMenu();
    }
    case 5:{
      system("cls");
      exit(0);
      break;
    }
    default:
      system("cls");
      cout << "Invalid choice" << endl;
      MainMenu();
  }
}

int main(){
  MainMenu();

  return 0;
}