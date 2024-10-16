#include "products.h"
#include "colors.h"
#include <iostream>
#include <cstring>

using namespace std;

int lastProductId = 0;

void addProduct(NodeProduct *&list)
{
    NodeProduct *newProduct = new NodeProduct;
    
    lastProductId++;
    newProduct->info.id = lastProductId;
    
    cout << endl << "Ingrese nombre del producto: ";
    cin.ignore();
    cin.getline(newProduct->info.name, 50);
    cout << "Ingrese precio: ";
    cin >> newProduct->info.price;
    cout << "Ingrese umbral de reposición: ";
    cin >> newProduct->info.restockThreshold;
    cout << "Ingrese cantidad disponible: ";
    cin >> newProduct->info.quantityAvailable;

    cout << endl;

    newProduct->next = list;
    list = newProduct;

    saveProducts(list);
}

void modifyProduct(NodeProduct *list, int id)
{
    NodeProduct *current = list;
    while (current != nullptr)
    {
        if (current->info.id == id)
        {
            cout << "Producto encontrado. Ingrese nuevos valores:\n";
            
            cout << "ID del producto: " << current->info.id << endl;
            
            cout << "Ingrese nuevo nombre: ";
            cin.ignore();
            cin.getline(current->info.name, 50);
            cout << "Ingrese nuevo precio: ";
            cin >> current->info.price;
            cout << "Ingrese nuevo umbral de reposición: ";
            cin >> current->info.restockThreshold;
            cout << "Ingrese nueva cantidad disponible: ";
            cin >> current->info.quantityAvailable;

            saveProducts(list);
            return;
        }
        current = current->next;
    }
        cout << endl << RED "Producto con ID " << id << " no encontrado.\n" << RESET;
}

void deleteProduct(NodeProduct *&list, int id)
{
    NodeProduct *current = list;
    NodeProduct *previous = nullptr;

    while (current != nullptr && current->info.id != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << endl << RED "Producto con ID " << id << " no encontrado.\n" << RESET;
        return;
    }

    if (previous == nullptr)
    {
        list = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    delete current;
    cout << endl << RED "Producto con ID " << id << " eliminado.\n" << RESET;
    saveProducts(list);
}

void showProducts(NodeProduct *list)
{
    NodeProduct *current = list;

    if (current == nullptr)
    {
        cout << RED << "No hay productos en el inventario.\n" << RESET;
        return;
    }

    while (current != nullptr)
    {
        cout << YELLOW << "ID: " << current->info.id << ", Nombre: " << current->info.name
             << ", Precio: " << current->info.price << ", Umbral de reposición: "
             << current->info.restockThreshold << ", Cantidad disponible: "
             << current->info.quantityAvailable << endl << RESET;
        current = current->next;
    }
}

void saveProducts(NodeProduct *list)
{
    ofstream file("data/products.txt");

    if (!file)
    {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    NodeProduct *current = list;
    while (current != nullptr)
    {
        file << current->info.id << " " << current->info.name << " "
             << current->info.price << " " << current->info.restockThreshold << " "
             << current->info.quantityAvailable << endl;
        current = current->next;
    }
    file.close();
}

void loadProducts(NodeProduct*& list) {
    ifstream file("data/products.txt");
    
    if (!file) {
        cout << "Error al abrir el archivo.\n";
        return;
    }
    
    lastProductId = 0;
    
    while (!file.eof()) {
        NodeProduct* newProduct = new NodeProduct;
        file >> newProduct->info.id >> newProduct->info.name >> newProduct->info.price 
             >> newProduct->info.restockThreshold >> newProduct->info.quantityAvailable;
        
        if (file.eof()) break;
        
        if (newProduct->info.id > lastProductId) {
            lastProductId = newProduct->info.id;
        }

        newProduct->next = list;
        list = newProduct;
    }
    file.close();
}

void productsMenu(NodeProduct *&list)
{
    int option, id;

    do
    {
        cout << endl << "1. Mostrar productos" << endl
             << RESET;
        cout << "2. Agregar producto" << endl
             << RESET;
        cout << "3. Modificar producto por ID" << endl
             << RESET;
        cout << "4. Eliminar producto por ID" << endl
             << RESET;
        cout << RED << endl << "5. Volver al menú principal" << endl << endl
             << RESET;
        cout << CYAN << "Seleccione una opción: "  
             << RESET;

        cin >> option; cout << endl;

        switch (option)
        {
        case 1:
            showProducts(list);
            break;
        case 2:
            addProduct(list);
            break;
        case 3:
            cout << "Ingrese el ID del producto a modificar: ";
            cin >> id;
            modifyProduct(list, id);
            break;
        case 4:
            cout << "Ingrese el ID del producto a eliminar: ";
            cin >> id;
            deleteProduct(list, id);
            break;
        case 5:
            break;
        default:
            cout << RED << "Opción inválida\n"
                 << RESET;
        }
    } while (option != 5);
}