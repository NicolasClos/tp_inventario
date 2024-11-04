#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <fstream>
#include <string>

struct order{
    int id;
    int productId;
    int quantity;
    int clientId;
};

struct NodeOrders{
    order info;
    NodeOrders *next;
};

struct NodeCola{
    int info;
    NodeCola *next;
};

struct NodePila{
    int info;
    NodePila *next;
};

order desenqueue(NodeOrders*& ordersListFront, NodeOrders*& ordersListEnd);
order pop(NodeOrders*& ordersList);

void push(NodeOrders*& ordersList, order order);
void enqueue(NodeOrders*& ordersListFront, NodeOrders*& ordersListEnd, order order);
void showCompletedOrders(NodeOrders*& ordersList);
void showPendingOrders(NodeOrders*& ordersListFront, NodeOrders*& ordersListEnd);
void loadOrders();
void addOrder();
void completeOrder();

#endif