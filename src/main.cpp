#include <iostream>
#include "products.h"
#include "suppliers.h"
#include "clients.h"
#include "orders.h"
#include "colors.h"

using namespace std;

void productsMenu(NodeProduct*& list);
void suppliersMenu(NodeSupplier*& list);
void clientsMenu(NodeClient*& list);
//void ordersMenu(NodeOrders*& list, NodeClient*& clientList, NodeProduct*& productList);

void showMenu() {
    cout << endl << endl <<"---------------------------\n" << endl;
    cout << YELLOW << "\nGESTIÓN DE INVENTARIO - MENU PRINCIPAL \n" << RESET << endl;
    cout << CYAN << "Seleccione una opción: " << endl << endl << RESET;
    cout << GREEN << "1. Gestionar productos\n" << RESET;
    cout << GREEN << "2. Gestionar proveedores\n" << RESET;
    cout << GREEN << "3. Gestionar clientes\n" << RESET;
    cout << GREEN << "4. Registrar pedidos\n" << RESET;
    cout << RED << endl << "0. Salir\n" << RESET;
}

int main() { 
    NodeProduct* productsList = nullptr;
    NodeSupplier* suppliersList = nullptr;
    NodeClient* clientsList = nullptr;

    NodeOrders* colaVfte = nullptr;
    NodeOrders* colaVfin = nullptr;
    NodeOrders* pila = nullptr;
    
    loadProducts(productsList);
    loadSuppliers(suppliersList);
    loadClients(clientsList);
    loadOrders(colaVfte, "data/orders_queue.dat");
    loadOrders(pila, "data/orders_stack.dat");

    int opcion;
    do {
        showMenu();
        cout << endl << CYAN << "Opción: " << RESET;
        cin >> opcion;

        switch(opcion) {
            case 1:
                productsMenu(productsList);
                break;
            case 2:
                suppliersMenu(suppliersList);
                break;
            case 3:
                clientsMenu(clientsList);
                break;
            case 4:
                ordersMenu(productsList, clientsList, colaVfte, colaVfin, pila);
                break;
            case 0:
                break;
            default:
                cout << endl << "---------------------------\n" << endl;
                cout << RED << "\nOPCIÓN INVÁLIDA\n" << RESET;
        }
    } while (opcion != 0);

    return 0;
}
