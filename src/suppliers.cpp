#include "suppliers.h"
#include "colors.h"
#include <iostream>
#include <cstring>

using namespace std;

int lastSupplierId = 0;


void addProduct(NodeSupplier* supplier, int productId) {
    NodeProductSupplier* actual = supplier->info.productList;
    while (actual != nullptr) {
        if (actual->productId == productId) {
            std::cout << "El producto con ID " << productId << " ya está en la lista." << std::endl;
            return;
        }
        actual = actual->next;
    }
    NodeProductSupplier* newProduct = new NodeProductSupplier;
    newProduct->productId = productId;
    newProduct->next = supplier->info.productList;
    supplier->info.productList = newProduct;

    std::cout << "Producto con ID " << productId << " agregado correctamente." << std::endl;
    /*
    
    ProductSupplier newProductSupplier;

    newProductSupplier.productId = productId;

    newProductSupplier.supplierId = supplier->info.id;

    FILE *archivo = fopen("data/productsSuppliers.dat", "wb+");  

    if (!archivo)
    {
        cout << "Error al abrir el archivo.\n";
        return;
    }
    
    fwrite(&newProductSupplier, sizeof(ProductSupplier),1, archivo);*/
}

void addSupplier(NodeSupplier *&list)
{
    NodeSupplier *newSupplier = new NodeSupplier;
    
    lastSupplierId++;
    newSupplier->info.id = lastSupplierId;

    int suppliedProductID;
    
    std::cout << endl << "Ingrese nombre del proveedor: ";
    std::cin.ignore();
    std::cin.getline(newSupplier->info.name, 50);
    std::cout << "Ingrese la dirección del proveedor: ";
    std::cin.ignore();
    std::cin.getline(newSupplier->info.address, 50);
    std::cin.ignore();
    std::cout << "Ingrese el número de teléfono del proveedor: ";
    std::cin >> newSupplier->info.phoneNumber;
    std::cout << "Ingrese los ID de productos que provee (0 para terminar): ";
    do {
        std::cin >> suppliedProductID;
        if (suppliedProductID != 0) {
            addProduct(newSupplier, suppliedProductID);
        }
    } while (suppliedProductID != 0);

    std::cout << endl;

    newSupplier->next = list;
    list = newSupplier;

    saveSuppliers(list);
}

void updateSupplier(NodeSupplier* list, int id) {
    NodeSupplier* current = list;

    while (current != nullptr) {
        if (current->info.id == id) {
            std::cout << "Proveedor encontrado. Ingrese nuevos valores:\n";

            std::cout << "ID del proveedor: " << current->info.id << endl;

            std::cout << "Ingrese nuevo nombre: ";
            std::cin.ignore();
            std::cin.getline(current->info.name, 50);
            std::cout << "Ingrese la nueva dirección: ";
            std::cin.getline(current->info.address, 50);
            std::cout << "Ingrese nuevo número de teléfono: ";
            std::cin >> current->info.phoneNumber;

            int opcion;
            std::cout << "¿Desea agregar productos (1) o reemplazar todos los productos provistos (2)? ";
            std::cin >> opcion;

            if (opcion == 1) {
                int suppliedProductID;
                std::cout << "Ingrese los ID de productos que provee (0 para terminar): ";
                do {
                    std::cin >> suppliedProductID;

                    if (suppliedProductID != 0) {
                        addProduct(current, suppliedProductID);
                    }

                } while (suppliedProductID != 0);

            } else if (opcion == 2) {
                NodeProductSupplier* actualProducto = current->info.productList;
                while (actualProducto != nullptr) {
                    NodeProductSupplier* temp = actualProducto;
                    actualProducto = actualProducto->next;
                    delete temp;
                }
                current->info.productList = nullptr; 

                int suppliedProductID;
                std::cout << "Ingrese los nuevos ID de productos que provee (0 para terminar): ";
                do {
                    std::cin >> suppliedProductID;

                    if (suppliedProductID != 0) {
                        addProduct(current, suppliedProductID);
                    }

                } while (suppliedProductID != 0);
            }


            std::cout << "Proveedor actualizado correctamente.\n";
            saveSuppliers(list);
            return;
        }
        current = current->next;
        
    }
    std::cout << endl << "Proveedor con ID " << id << " no encontrado.\n";
}

void deleteSupplier(NodeSupplier*& list, int id) {
    NodeSupplier* current = list;
    NodeSupplier* previous = nullptr;

    while (current != nullptr && current->info.id != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Proveedor con ID " << id << " no encontrado.\n";
        return;
    }

    if (previous == nullptr) {
        list = current->next;
    } else {
        previous->next = current->next;
    }

    NodeProductSupplier* productCurrent = current->info.productList;
    while (productCurrent != nullptr) {
        NodeProductSupplier* tempProduct = productCurrent;
        productCurrent = productCurrent->next;
        delete tempProduct;
    }

    delete current;

    std::cout << YELLOW << endl << "Proveedor con ID " << id << " eliminado correctamente.\n";
}

void showSuppliers(NodeSupplier* list) {
    NodeSupplier* current = list;

    if (current == nullptr) {
        std::cout << RED << "No hay proveedores registrados.\n" << RESET;
        return;
    }

    while (current != nullptr) {
        std::cout << "Proveedor ID: " << current->info.id << "\n";
        std::cout << "Nombre: " << current->info.name << "\n";
        std::cout << "Dirección: " << current->info.address << "\n";
        std::cout << "Teléfono: " << current->info.phoneNumber << "\n";

        if (current->info.productList == nullptr) {
            std::cout << "Este proveedor no tiene productos asignados.\n";
        } else {
            std::cout << "Productos provistos:\n";
            NodeProductSupplier* productCurrent = current->info.productList;
            while (productCurrent != nullptr) {
                std::cout << "- Producto ID: " << productCurrent->productId << "\n";
                productCurrent = productCurrent->next;
            }
        }

        std::cout << "---------------------------\n";
        current = current->next;
    }
}

void saveSuppliers(NodeSupplier *list)
{
    FILE *archivo = fopen("data/suppliers.dat", "wb+");  
    if (!archivo)
    {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    NodeSupplier *current = list;
    while (current != nullptr)
    {
        fwrite(&current->info.id, sizeof(current->info.id), 1, archivo);
        fwrite(&current->info.name, sizeof(current->info.name), 1, archivo);
        fwrite(&current->info.address, sizeof(current->info.address), 1, archivo);
        fwrite(&current->info.phoneNumber, sizeof(current->info.phoneNumber), 1, archivo);
        NodeProductSupplier* productCurrent = current->info.productList;
        size_t productCount = 0;
        NodeProductSupplier* temp = productCurrent;
        while (temp != nullptr) {
            productCount++;
            temp = temp->next;
        }
        fwrite(&productCount, sizeof(productCount), 1, archivo);
        while (productCurrent != nullptr) {
            fwrite(&productCurrent->productId, sizeof(productCurrent->productId), 1, archivo);
            productCurrent = productCurrent->next;
        }

        current = current->next;
    }

    fclose(archivo);
}

void loadSuppliers(NodeSupplier*& list) {
    FILE *archivo = fopen("data/suppliers.dat", "rb");

    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    lastSupplierId = 0;

    while (true) {
        NodeSupplier* newSupplier = new NodeSupplier;
        if (fread(&newSupplier->info.id, sizeof(newSupplier->info.id), 1, archivo) != 1) break;
        fread(&newSupplier->info.name, sizeof(newSupplier->info.name), 1, archivo);
        fread(&newSupplier->info.address, sizeof(newSupplier->info.address), 1, archivo);
        fread(&newSupplier->info.phoneNumber, sizeof(newSupplier->info.phoneNumber), 1, archivo);

        size_t productCount;
        fread(&productCount, sizeof(productCount), 1, archivo);

        NodeProductSupplier* productList = nullptr;
        NodeProductSupplier* lastProduct = nullptr;

        for (size_t i = 0; i < productCount; i++) {
            NodeProductSupplier* newProduct = new NodeProductSupplier;
            fread(&newProduct->productId, sizeof(newProduct->productId), 1, archivo);
            newProduct->next = nullptr;
            if (productList == nullptr) {
                productList = newProduct;
            } else {
                lastProduct->next = newProduct;
            }
            lastProduct = newProduct;
        }

        newSupplier->info.productList = productList;

        if (feof(archivo)) break;

        if (newSupplier->info.id > lastSupplierId) {
            lastSupplierId = newSupplier->info.id;
        }

        newSupplier->next = list;
        list = newSupplier;
    }

    fclose(archivo); 
}

void suppliersMenu(NodeSupplier *&list) {
    int option, id;

    do {
        cout << endl
             << "1. Mostrar proveedores" << endl
             << "2. Agregar proveedor" << endl
             << "3. Modificar proveedor por ID" << endl
             << "4. Eliminar proveedor por ID" << endl
             << RED << endl
             << "5. Volver al menú principal" << endl
             << RESET;
        cout << CYAN << "Seleccione una opción: " << RESET;

        cin >> option;
        cout << endl;

        switch (option) {
        case 1:
            showSuppliers(list);
            break;
        case 2:
            addSupplier(list);
            break;
        case 3:
            cout << "Ingrese el ID del proveedor a modificar: ";
            cin >> id;
            updateSupplier(list, id);
            break;
        case 4:
            cout << "Ingrese el ID del proveedor a eliminar: ";
            cin >> id;
            deleteSupplier(list, id);
            break;
        case 5:
            break;
        default:
            cout << RED << "Opción inválida\n" << RESET;
        }
    } while (option != 5);
}