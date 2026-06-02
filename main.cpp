#include <cstdlib>
#include <iostream>
#include "Database.h"
#include "Client.h"
#include "Product.h"
#include "Sale.h"
#include "SalesRepresentative.h"

using namespace std;

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
      break;
    }
    case 2:{
      system("cls");
      SalesRepresentative salesRepresentative;
      salesRepresentative.SalesRepresentativeMenu();
      break;
    }
    case 3:{
      system("cls");
      Product product;
      product.ProductMenu();
      break;
    }
    case 4:{
      system("cls");
      Sale sale;
      sale.SaleMenu();
      break;
    }
    case 5:{
      system("cls");
      Database::Close();
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
  if (!Database::Initialize()) {
    return 1;
  }

  MainMenu();
  Database::Close();

  return 0;
}
