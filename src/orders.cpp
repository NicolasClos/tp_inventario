#include <iostream>
#include "orders.h"
#include "colors.h"
#include "products.h"

using namespace std;

NodeOrders* colaVfte = NULL;
NodeOrders* colaVfin = NULL;
NodeOrders* pila = NULL;

int lastOrderId = 0;

void addOrder(){
    order newOrder;

    lastOrderId++;
    newOrder.id = lastOrderId;

    cout << endl << "Ingrese el ID de la orden: ";
    cin >> newOrder.id;
    cout << "Ingrese el ID del producto: ";
    cin >> newOrder.productId;
    cout << "Ingrese la cantidad: ";
    cin >> newOrder.quantity;
    cout << "Ingrese el ID del cliente: ";
    cin >> newOrder.clientId;
    cout << endl;

    enqueue(colaVfte, colaVfin, newOrder);
}

void completeOrder(NodeProduct*& productList){
    order order = desenqueue(colaVfte, colaVfin);
    push(pila, order);
    updateStock(productList, order.productId, order.quantity);
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

    NodeOrders *ordersListAux = NULL;

    if(orderslist == NULL){
        cout << RED << endl << "No hay pedidos completos registrados.\n";
        return;
    };

    std::cout << YELLOW << endl << "Elementos de la pila: " << RESET << endl << endl;

    while (orderslist != NULL) {
        order order = pop(orderslist);
        cout << "ID del pedido: " << order.id << endl;
        cout << "ID del producto: " << order.productId << endl;
        cout << "Cantidad: " << order.quantity << endl;
        cout << "ID del cliente: " << order.clientId << endl;
        push(ordersListAux, order);
    }

    cout << endl;
}

void showPendingOrders(NodeOrders *&colafte, NodeOrders *&colafin){
    NodeOrders *auxfte = NULL;
    NodeOrders *auxfin = NULL;
    if(colafte == NULL){
        cout << RED << endl << "No hay pedidos pendientes registrados.\n";
        return;
    };
    std::cout << YELLOW << endl << "Elementos de la cola: " << RESET << endl << endl;
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

void loadOrders(){ 

    // FILE *archivo = fopen("data/orders.dat", "rb");

    // if (!archivo) {
    //     cout << "Error al abrir el archivo.\n";
    //     return;
    // }

    // lastOrderId = 0;

    // while (true) {
    //     NodeOrders* newOrder = new NodeOrders;
    //     if (fread(&newOrder->info.id, sizeof(newOrder->info.id), 1, archivo) != 1) break;
    //     fread(&newOrder->info.productId, sizeof(newOrder->info.productId), 1, archivo);
    //     fread(&newOrder->info.quantity, sizeof(newOrder->info.quantity), 1, archivo);
    //     fread(&newOrder->info.clientId, sizeof(newOrder->info.clientId), 1, archivo);
    //     if (feof(archivo)) break;
    //     if (newOrder->info.id > lastOrderId) {
    //         lastOrderId = newOrder->info.id;
    //     }
    //     newOrder->next = list;
    //     list = newOrder;
    // }
    // fclose(archivo); 
}

void ordersMenu(NodeProduct*& productList){
    int option;

    do{
    cout << YELLOW << "\nGESTIÓN DE ÓRDENES \n" << RESET << endl;
    cout << CYAN << "Seleccione una opción:" << endl << endl << RESET;
    cout << GREEN << "1. Registrar un nuevo pedido\n" << RESET;
    cout << GREEN << "2. Completar un pedido\n" << RESET;
    cout << GREEN << "3. Mostrar los pedidos pendientes\n" << RESET;
    cout << GREEN << "4. Mostrar los pedidos completados\n" << RESET;
    cout << RED << endl << "0. Salir\n" << RESET;
    
    cout << endl << "Opción: ";

    cin >> option;

        switch(option){
            case 1:
                addOrder();
                break;
            case 2:
                completeOrder(productList);
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