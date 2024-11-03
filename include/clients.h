#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream>
#include <fstream>
#include <string>

struct NodeClientPurchases {
    int purchaseId;
    NodeClientPurchases* next;
};

struct Client {
    int id;
    char name[50];
    char address[50];
    int phoneNumber;
    NodeClientPurchases* purchasesList;
};

struct NodeClient {
    Client info;
    NodeClient* next;
};

void addClient(NodeClient*& list);
void updateClient(NodeClient* list, int id);
void deleteClient(NodeClient*& list, int id);
void showClients(NodeClient* list);
void saveClients(NodeClient* list);
void loadClients(NodeClient*& list);

#endif