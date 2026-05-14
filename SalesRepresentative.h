#pragma once

#include <fstream>
#include <string>

class SalesRepresentative{
  public:
    void SalesRepresentativeMenu();
    void AddSalesRepresentative();
    void PrintSalesRepresentatives();
    void PrintSalesRepresentative();
    void ChangeSalesRepresentativeInfo();
    void SalesBonus();

  private:
    std::string firstName, lastName, shortAddress, emailAddress;
    int sales;
    std::fstream salesRepresentativesFS;
};
