#pragma once

#include <string>

class Client {
  public:
    void ClientMenu();
    void AddClient();
    void PrintClients();
    void PrintClient();
    void ChangeClientInfo();

  private:
    std::string firstName, lastName, shortAddress, emailAddress;
    int sales;
};
