#pragma once

#include <fstream>
#include <string>

class Product{
  public:
    void ProductMenu();
    void AddProduct();
    void PrintProducts();
    void PrintProduct();
    void ChangeProductInfo();
    void MonthlySalesReport();

  private:
    std::string name, inverterType, battery;
    int price, sales, wattage;
    std::fstream productsFS;
};
