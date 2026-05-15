#include <cstdlib>
#include <iostream>
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
