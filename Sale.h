#pragma once

#include <string>

class Sale{
  public:
    void SaleMenu();
    void AddSale();
    void SalesFromYear();
    void SalesFromYearFromSpecificClient();
    void ChangeSaleInfo();

  private:
    std::string clientFirstName, clientLastName, productName, salesRepresentativeFirstName, salesRepresentativeLastName, month;
    int year, day;
};
