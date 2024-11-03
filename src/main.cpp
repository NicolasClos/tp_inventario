#include <iostream>
#include "products.h"
#include "suppliers.h"
#include "clients.h"
#include "orders.h"
#include "stock.h"
#include "colors.h"

using namespace std;

void productsMenu(NodeProduct*& list);
void suppliersMenu(NodeSupplier*& list);
void clientsMenu(NodeClient*& list);
// void ordersMenu(NodeOrders*& list);

void showMenu() {
    cout << endl << endl << CYAN << "Sistema de Gestión de Inventario" << endl << endl << RESET;
    cout << GREEN << "1. Gestionar productos\n" << RESET;
    cout << GREEN << "2. Gestionar proveedores\n" << RESET;
    cout << GREEN << "3. Gestionar clientes\n" << RESET;
    cout << GREEN << "4. Registrar pedidos\n" << RESET;
    cout << GREEN << "5. Control de stock\n" << RESET;
    cout << RED << endl << "0. Salir\n" << RESET;
}

int main() { 
    
    NodeProduct* productList = nullptr;
    NodeSupplier* supplierList = nullptr;
    NodeClient* clientsList = nullptr;
    NodeOrders* ordersList = nullptr;
    loadProducts(productList);
    loadSuppliers(supplierList);
    loadClients(clientsList);
    // loadOrders(orderslist);

    int opcion;
    do {
        showMenu();
        cout << endl << CYAN << "Seleccione una opción: " << RESET;
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << YELLOW << "\nGESTIÓN DE PRODUCTOS \n" << RESET;
                productsMenu(productList);
                break;
            case 2:
                cout << YELLOW << "\nGESTIÓN DE PROVEEDORES \n" << RESET;
                suppliersMenu(supplierList);
                break;
            case 3:
                cout << YELLOW << "Gestionando clientes...\n" << RESET;
                clientsMenu(clientsList);
                break;
            case 4:
                cout << YELLOW << "Registrando pedidos...\n" << RESET;
                ordersMenu();
                break;
            case 5:
                cout << YELLOW << "Controlando stock...\n" << RESET;
                // Implementación de control de stock
                break;
            case 0:
                cout << RED << endl << endl << "Saliendo...\n" << endl << endl << RESET;
                break;
            default:
                cout << RED << "Opción inválida\n" << RESET;
        }
    } while (opcion != 0);

    return 0;
}
