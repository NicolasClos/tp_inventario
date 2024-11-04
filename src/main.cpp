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

void showMenu() {
    cout << endl << endl <<"---------------------------\n" << endl;
    cout << YELLOW << "\nGESTIÓN DE INVENTARIO \n" << RESET << endl;
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
    // NodeOrders* ordersList = nullptr;
    loadProducts(productList);
    loadSuppliers(supplierList);
    loadClients(clientsList);
    // loadOrders();

    int opcion;
    do {
        showMenu();
        cout << endl << CYAN << "Seleccione una opción: " << RESET;
        cin >> opcion;

        std::cout << endl << endl <<"---------------------------\n" << endl;

        switch(opcion) {
            case 1:
                productsMenu(productList);
                break;
            case 2:
                suppliersMenu(supplierList);
                break;
            case 3:
                clientsMenu(clientsList);
                break;
            case 4:
                ordersMenu(productList);
                break;
            case 5:
                cout << YELLOW << "\nCONTROL DE STOCK \n" << RESET;
                // Implementación de control de stock
                break;
            case 0:
                break;
            default:
                cout << RED << "\nOPCIÓN INVÁLIDA\n" << RESET;
        }
    } while (opcion != 0);

    return 0;
}
