#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <iostream>
#include <fstream>
#include <string>

struct Product {
    int id;
    char name[50];
    float price;
    int restockThreshold;
    int quantityAvailable;
};

struct NodeProduct {
    Product info;
    NodeProduct* next;
};

void addProduct(NodeProduct*& list);
void modifyProduct(NodeProduct* list, int id);
void deleteProduct(NodeProduct*& list, int id);
void showProducts(NodeProduct* list);
void saveProducts(NodeProduct* list);
void loadProducts(NodeProduct*& list);
void updateStock(NodeProduct *list, int id, int cantidadARestar);

bool checkProductExists(NodeProduct *& list, int id);
bool checkAvailability(NodeProduct *& list, int id, int quantity);

#endif