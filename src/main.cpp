#include <iostream>
#include "products.h"
#include "suppliers.h"
#include "clients.h"
#include "orders.h"
#include "stock.h"
#include "colors.h"

using namespace std;

void showMenu() {
    cout << endl << endl << CYAN << "Sistema de Gestión de Inventario" << endl << endl << RESET;
    cout << GREEN << "1. Gestionar productos\n" << RESET;
    cout << GREEN << "2. Gestionar proveedores\n" << RESET;
    cout << GREEN << "3. Gestionar clientes\n" << RESET;
    cout << GREEN << "4. Registrar pedidos\n" << RESET;
    cout << GREEN << "5. Control de stock\n" << RESET;
    cout << RED << "6. Salir\n" << RESET;
}

int main() {
    int opcion;
    do {
        showMenu();
        cout << endl << CYAN << "Seleccione una opción: " << RESET;
        cin >> opcion;

        switch(opcion) {
            case 1:
                // Llamar a funciones de productos
                cout << YELLOW << "Gestionando productos...\n" << RESET;
                break;
            case 2:
                // Llamar a funciones de proveedores
                cout << YELLOW << "Gestionando proveedores...\n" << RESET;
                break;
            case 3:
                // Llamar a funciones de clientes
                cout << YELLOW << "Gestionando clientes...\n" << RESET;
                break;
            case 4:
                // Llamar a funciones de pedidos
                cout << YELLOW << "Registrando pedidos...\n" << RESET;
                break;
            case 5:
                // Llamar a funciones de control de stock
                cout << YELLOW << "Controlando stock...\n" << RESET;
                break;
            case 6:
                cout << RED << endl << endl << "Saliendo...\n" << endl << endl << RESET;
                break;
            default:
                cout << RED << "Opción inválida\n" << RESET;
        }
    } while (opcion != 6);

    return 0;
}
