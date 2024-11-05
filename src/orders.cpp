#include <iostream>
#include "orders.h"
#include "colors.h"
#include "products.h"
#include "clients.h"

using namespace std;

int lastOrderId = 0;

void addOrder(NodeProduct*& productList, NodeClient*& clientList, NodeOrders*& colaVfte, NodeOrders*& colaVfin){
    order newOrder;
    lastOrderId++;
    newOrder.id = lastOrderId;
    cout << "Ingrese el ID del producto: ";
    cin >> newOrder.productId;
    if(!checkProductExists(productList, newOrder.productId)){
        std::cout << endl <<"---------------------------\n" << endl;
        cout << endl << RED << "No existe el producto con ID: " << newOrder.productId << ". Revise bien el ID del producto y crearlo de ser necesario." << endl << RESET;
        return;
    }
    cout << "Ingrese la cantidad: ";
    cin >> newOrder.quantity;
    if(!checkAvailability(productList, newOrder.productId, newOrder.quantity)){
        std::cout << endl <<"---------------------------\n" << endl;
        cout << endl << RED << "No hay cantidad disponible de este producto. Revise la cantidad disponible." << endl << RESET;
        return;
    }
    cout << "Ingrese el ID del cliente: ";
    cin >> newOrder.clientId;
    if(!checkClientExists(clientList, newOrder.clientId)){
        std::cout << endl <<"---------------------------\n" << endl;
        cout << endl << RED << "No existe el cliente con ID: " << newOrder.clientId << ". Revise bien el ID del cliente y delo de alta de ser necesario." << endl << RESET;
        return;
    }
    
    cout << GREEN << endl << "PEDIDO INGRESADO CON ÉXITO" << RESET;

    enqueue(colaVfte, colaVfin, newOrder);
    
    saveOrders(colaVfte, "data/orders_queue.dat");
}

void completeOrder(NodeProduct*& productList, NodeClient*& clientList, NodeOrders*& pila, NodeOrders*& colaVfte, NodeOrders*& colaVfin){
    if (colaVfte == nullptr) {
        cout << RED << "No hay órdenes pendientes para completar." << RESET;
        return;
    }
    order order = desenqueue(colaVfte, colaVfin);
    push(pila, order);
    updateStock(productList, order.productId, order.quantity);
    addPurchase(clientList, order.id);
    cout << GREEN << "La orden con ID " << order.id << " se ha marcado como completada." << RESET;
    saveOrders(pila, "data/orders_stack.dat");
    saveOrders(colaVfte, "data/orders_queue.dat");
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

void showCompletedOrders(NodeOrders *& orderslist) {
    if (orderslist == NULL) {
        cout << RED << endl << "No hay pedidos completados registrados.\n" << RESET;
        return;
    }

    std::cout << YELLOW << endl << "Elementos de la pila: " << RESET << endl << endl;

    NodeOrders *current = orderslist;
    while (current != NULL) {
        cout << "ID del pedido: " << YELLOW << current->info.id << RESET << endl;
        cout << "ID del producto: " << YELLOW << current->info.productId << RESET << endl;
        cout << "Cantidad: " << YELLOW << current->info.quantity << RESET << endl;
        cout << "ID del cliente: " << YELLOW << current->info.clientId << RESET;
        cout << endl << endl <<"---------------------------\n" << endl;
        current = current->next;
    }
}

void showPendingOrders(NodeOrders *&colafte, NodeOrders *&colafin){
    NodeOrders *auxfte = NULL;
    NodeOrders *auxfin = NULL;
    if(colafte == NULL){
        cout << RED << endl << "No hay pedidos pendientes registrados.\n" << RESET;
        return;
    };
    std::cout << YELLOW << endl << "Elementos de la cola: " << RESET << endl << endl;
    while (colafte != NULL){
        order order = desenqueue(colafte, colafin);
        cout << "ID del pedido: " << YELLOW << order.id << RESET<< endl;
        cout << "ID del producto: " << YELLOW << order.productId << RESET << endl;
        cout << "Cantidad: " << YELLOW << order.quantity << RESET << endl;
        cout << "ID del cliente: " << YELLOW << order.clientId << RESET;
        cout << endl << endl << "---------------------------\n" << endl;

        enqueue(auxfte, auxfin, order);

    }
    std::cout << std::endl;
    while (auxfte != NULL){
        enqueue(colafte, colafin, desenqueue(auxfte, auxfin));
    }
}

void loadOrders(NodeOrders*& list, const char* filename) {
    FILE *archivo = fopen(filename, "rb");
    if (!archivo) {
        cout << "Archivo " << filename << " no encontrado.\n";
        return;
    }


    while (true) {
        NodeOrders* newOrder = new NodeOrders;
        if (fread(&newOrder->info.id, sizeof(newOrder->info.id), 1, archivo) != 1) {
            delete newOrder;
            break;
        }
        if (fread(&newOrder->info.productId, sizeof(newOrder->info.productId), 1, archivo) != 1) {
            delete newOrder;
            break;
        }
        if (fread(&newOrder->info.quantity, sizeof(newOrder->info.quantity), 1, archivo) != 1) {
            delete newOrder;
            break;
        }
        if (fread(&newOrder->info.clientId, sizeof(newOrder->info.clientId), 1, archivo) != 1) {
            delete newOrder;
            break;
        }
        if (newOrder->info.id > lastOrderId) {
            lastOrderId = newOrder->info.id;
        }
        newOrder->next = list;
        list = newOrder;
    }

    fclose(archivo);
}


void ordersMenu(NodeProduct*& productList, NodeClient*& clientList, NodeOrders*& colaVfte, NodeOrders*& colaVfin, NodeOrders*& pila){
    int option;
    do{
    std::cout << endl << endl <<"---------------------------\n" << endl;
    cout << YELLOW << "\nGESTIÓN DE ÓRDENES \n" << RESET << endl;
    cout << CYAN << "Seleccione una opción:" << endl << endl << RESET;
    cout << "1. Registrar un nuevo pedido\n" << RESET;
    cout << "2. Completar un pedido\n" << RESET;
    cout << "3. Mostrar los pedidos pendientes\n" << RESET;
    cout << "4. Mostrar los pedidos completados\n" << RESET;
    cout << RED << endl << "0. Volver al menú principal\n" << RESET;
    
    cout << endl << "Opción: ";

    cin >> option;

    std::cout << endl <<"---------------------------\n" << endl;

        switch(option){
            case 1:
                addOrder(productList, clientList, colaVfte, colaVfin);
                break;
            case 2:
                completeOrder(productList, clientList, pila, colaVfte, colaVfin);
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
                cout << RED << "Opción inválida" << RESET;
    }} while(option != 0);
}

void saveOrders(NodeOrders*& list, const char* filename)
{
    FILE *archivo = fopen(filename, "wb+");  
    if (!archivo)
    {
        cout << "Archivo " << filename << " no encontrado.\n";
        return;
    }

    NodeOrders *current = list;
    while (current != nullptr)
    {
        fwrite(&current->info.id, sizeof(current->info.id), 1, archivo);
        fwrite(&current->info.clientId, sizeof(current->info.clientId), 1, archivo);
        fwrite(&current->info.productId, sizeof(current->info.productId), 1, archivo);
        fwrite(&current->info.quantity, sizeof(current->info.quantity), 1, archivo);

        current = current->next;
    }

    fclose(archivo);
}