#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <fstream>
#include <string>

struct ProductSupplier {
    int productId;
    int supplierId;
};

struct NodeProductSupplier {
    int productId;
    NodeProductSupplier* next;
};

struct Supplier {
    int id;
    char name[50];
    char address[50];
    int phoneNumber;
    NodeProductSupplier* productList;
};

struct NodeSupplier {
    Supplier info;
    NodeSupplier* next;
};

void addSupplier(NodeSupplier*& list);
void updateSupplier(NodeSupplier* list, int id);
void deleteSupplier(NodeSupplier*& list, int id);
void showSuppliers(NodeSupplier* list);
void saveSuppliers(NodeSupplier* list);
void loadSuppliers(NodeSupplier*& list);

#endif