#include <iostream>
#include "orders.h"
#include "colors.h"

using namespace std;

NodeOrders* colaVfte = NULL;
NodeOrders* colaVfin = NULL;
NodeOrders* pila = NULL;

void addOrder(){
    order newOrder;

    cout << endl << "Ingrese el ID de la orden: ";
    cin >> newOrder.id;
    cout << endl << "Ingrese el ID del producto: ";
    cin >> newOrder.productId;
    cout << "Ingrese la cantidad: ";
    cin >> newOrder.quantity;
    cout << "Ingrese el ID del cliente";
    cin >> newOrder.clientId;
    cout << endl;

    enqueue(colaVfte, colaVfin, newOrder);
}

void completeOrder(){
    order order = desenqueue(colaVfte, colaVfin);
    push(pila, order);
}

void push(NodeOrders *& ordersList, order order){
    NodeOrders*newOrder = new NodeOrders;
    newOrder->info = order;
    newOrder->next = ordersList;
    ordersList = newOrder;
}

order pop(NodeOrders *& ordersList){
    order order = ordersList->info;
    NodeOrders*aux = ordersList;
    ordersList = ordersList->next;
    delete aux;
    return order;
}

void enqueue(NodeOrders *&colafte, NodeOrders *&colafin, order currentOrder){
    NodeOrders *ordersList = new NodeOrders;
    ordersList->info = currentOrder;
    ordersList->next = NULL;
    if (colafte == NULL){
        colafte = ordersList;
    } else{
        colafin->next = ordersList;
    }
    colafin = ordersList;
}

order desenqueue(NodeOrders *&colafte, NodeOrders *&colafin){
    order order = colafte->info;
    NodeOrders*aux = colafte;
    colafte = colafte->next;
    if (colafte == NULL){
        colafin = NULL;
    }
    delete aux;
    return order;
}

void showCompletedOrders(NodeOrders *&orderslist) {
    NodeOrders *auxPila = NULL;
    cout << "Elementos de la pila: " << endl;

    while (orderslist != NULL) {
        order order = pop(orderslist);  // pop debe devolver el nodo eliminado
        cout << "ID del pedido: " << order.id << endl;
        cout << "ID del producto: " << order.productId << endl;
        cout << "Cantidad: " << order.quantity << endl;
        cout << "ID del cliente: " << order.clientId << endl;
        
        // Guarda el nodo en auxPila para restaurar la pila más adelante
        push(auxPila, order);
    }

    cout << endl;

    // Restaura el contenido original de orderslist
    while (auxPila != NULL) {
        push(orderslist, pop(auxPila));
    }
}

void showPendingOrders(NodeOrders *&colafte, NodeOrders *&colafin){
    NodeOrders *auxfte = NULL;
    NodeOrders *auxfin = NULL;
    std::cout << "Elementos de la cola: " << endl;
    while (colafte != NULL){
        order order = desenqueue(colafte, colafin);
        cout << "ID del pedido: " << order.id << endl;
        cout << "ID del producto: " << order.productId <<endl;
        cout << "Cantidad: " << order.quantity << endl;
        cout << "ID del cliente: " << order.clientId << endl;
        enqueue(auxfte, auxfin, order);
    }
    std::cout << std::endl;
    while (auxfte != NULL){
        enqueue(colafte, colafin, desenqueue(auxfte, auxfin));
    }
}

void ordersMenu(){
    NodeOrders *pila = NULL;
    NodeOrders *colafte = NULL;
    NodeOrders *colafin = NULL;
    int option;
    order order;

    do{
    cout << endl << endl << CYAN << "Seleccione una opción:" << endl << endl << RESET;
    cout << GREEN << "1. Registrar un nuevo pedido\n" << RESET;
    cout << GREEN << "2. Completar un pedido\n" << RESET;
    cout << GREEN << "3. Mostrar los pedidos pendientes\n" << RESET;
    cout << GREEN << "4. Mostrar los pedidos completados\n" << RESET;
    cout << RED << endl << "0. Salir\n" << RESET;
    
    cout << endl << "Seleccione una opción: " << endl;

    cin >> option;

        switch(option){
            case 1:
                addOrder();
                break;
            case 2:
                completeOrder();
                break;
            case 3:
                showPendingOrders(colaVfte, colaVfin);
                break;
            case 4:
                showCompletedOrders(pila);
                break;
            case 0: 
                break;
            default:
                cout << RED << "Opción inválida\n" << RESET;
    }} while(option != 0);
}