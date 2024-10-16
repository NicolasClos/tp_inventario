#include <iostream>
#include "products.h"
#include "suppliers.h"
#include "clients.h"
#include "orders.h"
#include "stock.h"
#include "colors.h"

using namespace std;

void productsMenu(NodeProduct*& list);

void showMenu() {
    cout << endl << endl << CYAN << "Sistema de Gestión de Inventario" << endl << endl << RESET;
    cout << GREEN << "1. Gestionar productos\n" << RESET;
    cout << GREEN << "2. Gestionar proveedores\n" << RESET;
    cout << GREEN << "3. Gestionar clientes\n" << RESET;
    cout << GREEN << "4. Registrar pedidos\n" << RESET;
    cout << GREEN << "5. Control de stock\n" << RESET;
    cout << RED << endl << "6. Salir\n" << RESET;
}

int main() { 
    
    NodeProduct* productList = nullptr;
    loadProducts(productList);

    //  NodoProveedores* listaProveedores = NULL;
    NodoClientes* listaClientes = NULL;

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
                cout << YELLOW << "Gestionando proveedores...\n" << RESET;
                // Implementación de proveedores
                break;
            case 3:
                cout << YELLOW << "Gestionando clientes...\n" << RESET;
                {
                    infoClientes nuevoCliente;
                    cout << "Ingrese ID del cliente: ";
                    cin >> nuevoCliente.id;
                    cout << "Ingrese nombre del cliente: ";
                    cin.ignore();
                    cin.getline(nuevoCliente.nombre, 50);
                    cout << "Ingrese dirección del cliente: ";
                    cin.getline(nuevoCliente.direccion, 50);
                    cout << "Ingrese teléfono del cliente: ";
                    cin >> nuevoCliente.telefono;

                    agregarNodoCliente(listaClientes, nuevoCliente);
                    mostrarNodoClientes(listaClientes);
                }
                break;
            case 4:
                cout << YELLOW << "Registrando pedidos...\n" << RESET;
                // Implementación de pedidos
                break;
            case 5:
                cout << YELLOW << "Controlando stock...\n" << RESET;
                // Implementación de control de stock
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
