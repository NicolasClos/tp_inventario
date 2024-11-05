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
    
    cout << "Ingrese nombre del producto: ";
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
        cout << endl << RED "Producto con ID " << id << " no encontrado." << RESET;
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
        cout << endl << RED "Producto con ID " << id << " no encontrado." << RESET;
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
    cout << endl << RED "Producto con ID " << id << " eliminado." << RESET;
    saveProducts(list);
}

void showProducts(NodeProduct *list)
{
    NodeProduct *current = list;

    if (current == nullptr)
    {
        cout << RED << endl << "No hay productos en el inventario.\n" << RESET;
        return;
    }

    while (current != nullptr)
    {
        cout << "ID: " << YELLOW << current->info.id << RESET << endl;
        cout << "Nombre: " << YELLOW << current->info.name << RESET << endl;
        cout << "Precio: " YELLOW << current->info.price << RESET << endl;
        cout << "Umbral de reposición: " << YELLOW << current->info.restockThreshold << RESET << endl;
        cout << "Cantidad disponible: " << YELLOW << current->info.quantityAvailable << RESET << endl;
        std::cout << endl <<"---------------------------\n" << endl;
        current = current->next;
    }
}

void saveProducts(NodeProduct *list)
{
    FILE *archivo = fopen("data/products.dat", "wb+");  
    if (!archivo)
    {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    NodeProduct *current = list;
    while (current != nullptr)
    {
        fwrite(&current->info.id, sizeof(current->info.id), 1, archivo);
        fwrite(&current->info.name, sizeof(current->info.name), 1, archivo);
        fwrite(&current->info.price, sizeof(current->info.price), 1, archivo);
        fwrite(&current->info.restockThreshold, sizeof(current->info.restockThreshold), 1, archivo);
        fwrite(&current->info.quantityAvailable, sizeof(current->info.quantityAvailable), 1, archivo);

        current = current->next;
    }

    fclose(archivo);
}

void loadProducts(NodeProduct*& list) {
    FILE *archivo = fopen("data/products.dat", "rb");

    if (!archivo) {
        cout << "Archivo de productos no encontrado.\n";
        return;
    }

    lastProductId = 0;

    while (true) {
        NodeProduct* newProduct = new NodeProduct;
        if (fread(&newProduct->info.id, sizeof(newProduct->info.id), 1, archivo) != 1) {
            delete newProduct;
            break;
        }
        if (fread(&newProduct->info.name, sizeof(newProduct->info.name), 1, archivo) != 1) {
            delete newProduct;
            break;
        }
        if (fread(&newProduct->info.price, sizeof(newProduct->info.price), 1, archivo) != 1) {
            delete newProduct;
            break;
        }
        if (fread(&newProduct->info.restockThreshold, sizeof(newProduct->info.restockThreshold), 1, archivo) != 1) {
            delete newProduct;
            break;
        }
        if (fread(&newProduct->info.quantityAvailable, sizeof(newProduct->info.quantityAvailable), 1, archivo) != 1) {
            delete newProduct;
            break;
        }
        if (newProduct->info.id > lastProductId) {
            lastProductId = newProduct->info.id;
        }
        newProduct->next = list;
        list = newProduct;
    }

    fclose(archivo); 
}


void productsMenu(NodeProduct *&list)
{
    int option, id;

    do
    {
        std::cout << endl << endl <<"---------------------------\n" << endl;
        cout << YELLOW << "\nGESTIÓN DE PRODUCTOS \n" << RESET << endl;
        cout << CYAN << "Seleccione una opción:" << endl << RESET;
        cout << endl << "1. Mostrar productos" << endl
             << RESET;
        cout << "2. Agregar producto" << endl
             << RESET;
        cout << "3. Modificar producto por ID" << endl
             << RESET;
        cout << "4. Eliminar producto por ID" << endl
             << RESET;
        cout << RED << endl << "0. Volver al menú principal" << endl << endl
             << RESET;
        cout << CYAN << "Opción: "  
             << RESET;

        cin >> option; 
        
         std::cout << endl <<"---------------------------\n" << endl;

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
    } while (option != 0);
}

void updateStock(NodeProduct *list, int id, int cantidadARestar){
    NodeProduct *current = list;
    while (current != nullptr)
    {
        if (current->info.id == id){
            list->info.quantityAvailable -= cantidadARestar;
            if(list->info.quantityAvailable < list->info.restockThreshold){
                int diff = list->info.restockThreshold-list->info.quantityAvailable;
                cout << endl << RED << "NECESITA REPONER AL MENOS " << diff << " CANTIDAD DE "<< list->info.name << "." << endl << RESET;
            }
            saveProducts(list);
            return;
        }
        current = current->next;
    }
    cout << endl << RED "Producto con ID " << id << " no encontrado." << RESET;
}

bool checkProductExists(NodeProduct *& list, int id){
    NodeProduct *current = list;
    while (current != nullptr){
        if (current->info.id == id) return true;
        current = current->next;
    } return false;
}

bool checkAvailability(NodeProduct *& list, int id, int quantity){
    NodeProduct *current = list;
    while (current != nullptr){
        if (current->info.id == id){
            if(current->info.quantityAvailable >= quantity) return true;
            return false;
        };
        current = current->next;
    } return false;
};