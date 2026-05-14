#pragma once

#include <fstream>
#include <string>

class Client{
  public:
    void ClientMenu();
    void AddClient();
    void PrintClients();
    void PrintClient();
    void ChangeClientInfo();

  private:
    std::string firstName, lastName, shortAddress, emailAddress;
    int sales;
    std::fstream clientsFS;
};
