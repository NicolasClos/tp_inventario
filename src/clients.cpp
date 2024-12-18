#include "clients.h"
#include "colors.h"
#include <iostream>
#include <cstring>

using namespace std;

int lastClientId = 0;

void addPurchase(NodeClient* clientList, int purchaseId) {
    NodeClientPurchases* newPurchase = new NodeClientPurchases;
    newPurchase->purchaseId = purchaseId;
    newPurchase->next = clientList->info.purchasesList;
    clientList->info.purchasesList = newPurchase;
    saveClients(clientList);
}

void addClient(NodeClient *&list)
{
    NodeClient *newClient = new NodeClient;
    
    lastClientId++;
    newClient->info.id = lastClientId;
    
    std::cout << endl << "Ingrese el nombre del cliente: ";
    std::cin.ignore();
    std::cin.getline(newClient->info.name, 50);
    std::cout << "Ingrese la dirección del cliente: ";
    std::cin.getline(newClient->info.address, 50);
    std::cout << "Ingrese el número de teléfono del cliente: ";
    std::cin >> newClient->info.phoneNumber;
    std::cout << endl;

    newClient->next = list;
    list = newClient;

    saveClients(list);
}

void updateClient(NodeClient* list, int id) {
    NodeClient* current = list;

    while (current != nullptr) {
        if (current->info.id == id) {
            std::cout << "Cliente encontrado. Ingrese nuevos valores:\n";
            std::cout << "ID del cliente: " << current->info.id << endl;
            std::cout << "Ingrese el nuevo nombre: ";
            std::cin.ignore();
            std::cin.getline(current->info.name, 50);
            std::cout << "Ingrese la nueva dirección: ";
            std::cin.getline(current->info.address, 50);
            std::cout << "Ingrese nuevo número de teléfono: ";
            std::cin >> current->info.phoneNumber;
            std::cout << "Cliente actualizado correctamente.\n";
            saveClients(list);
            return;
        }
        current = current->next;
    }
    std::cout << endl << RED << "Cliente con ID " << id << " no encontrado." << RESET;
}

void deleteClient(NodeClient*& list, int id) {
    NodeClient* current = list;
    NodeClient* previous = nullptr;

    while (current != nullptr && current->info.id != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << RED << endl << "Cliente con ID " << id << " no encontrado." << RESET;
        return;
    }

    if (previous == nullptr) {
        list = current->next;
    } else {
        previous->next = current->next;
    }

    NodeClientPurchases* currentPurchase = current->info.purchasesList;

    while (currentPurchase != nullptr) {
        NodeClientPurchases* tempPurchase = currentPurchase;
        currentPurchase = currentPurchase->next;
        delete tempPurchase;
    }

    delete current;
    
    saveClients(list);

    std::cout << GREEN << endl << "Cliente con ID " << id << " eliminado correctamente." << RESET;
}

void showClients(NodeClient* list) {
    NodeClient* current = list;

    if (current == nullptr) {
        std::cout << RED << endl << "No hay clientes registrados.\n" << RESET;
        return;
    }

    do {
        std::cout << "Cliente ID: " << YELLOW << current->info.id << RESET << "\n";
        std::cout << "Nombre: " << YELLOW << current->info.name << RESET << "\n";
        std::cout << "Dirección: " << YELLOW << current->info.address << RESET << "\n";
        std::cout << "Teléfono: " << YELLOW << current->info.phoneNumber << RESET << "\n\n";

        if (current->info.purchasesList == nullptr) {
            std::cout << endl << RED << current->info.name << " no ha realizado ninguna compra aún.\n" << RESET << endl;
        } else {
            std::cout << "Compras realizadas:\n";
            NodeClientPurchases* currentPurchase = current->info.purchasesList;
            while (currentPurchase != nullptr) {
                std::cout << "- ID de Compra: " << currentPurchase->purchaseId << endl;
                currentPurchase = currentPurchase->next;
            }
            cout << endl;
        }

        std::cout << "---------------------------\n" << endl;
        current = current->next;
    } while (current != nullptr);
}

void saveClients(NodeClient *list)
{
    FILE *archivo = fopen("data/clients.dat", "wb+");  
    if (!archivo){
        cout << "Archivo de clientes no encontrado.\n";
        return;
    }

    NodeClient *current = list;
    while (current != nullptr)
    {
        fwrite(&current->info.id, sizeof(current->info.id), 1, archivo);
        fwrite(&current->info.name, sizeof(current->info.name), 1, archivo);
        fwrite(&current->info.address, sizeof(current->info.address), 1, archivo);
        fwrite(&current->info.phoneNumber, sizeof(current->info.phoneNumber), 1, archivo);
        NodeClientPurchases* currentPurchase = current->info.purchasesList;
        size_t purchaseCount = 0;
        NodeClientPurchases* temp = currentPurchase;
        while (temp != nullptr) {
            purchaseCount++;
            temp = temp->next;
        }
        fwrite(&purchaseCount, sizeof(purchaseCount), 1, archivo);
        while (currentPurchase != nullptr) {
            fwrite(&currentPurchase->purchaseId, sizeof(currentPurchase->purchaseId), 1, archivo);
            currentPurchase = currentPurchase->next;
        }

        current = current->next;
    }

    fclose(archivo);
}

void loadClients(NodeClient*& list) {
    FILE *archivo = fopen("data/clients.dat", "rb");

    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    lastClientId = 0;

    while (true) {
        NodeClient* newClient = new NodeClient;
        if (fread(&newClient->info.id, sizeof(newClient->info.id), 1, archivo) != 1) {
            delete newClient;
            break;
        }
        if (fread(&newClient->info.name, sizeof(newClient->info.name), 1, archivo) != 1) {
            delete newClient;
            break;
        }
        if (fread(&newClient->info.address, sizeof(newClient->info.address), 1, archivo) != 1) {
            delete newClient;
            break;
        }
        if (fread(&newClient->info.phoneNumber, sizeof(newClient->info.phoneNumber), 1, archivo) != 1) {
            delete newClient;
            break;
        }
        size_t purchaseCount;
        if (fread(&purchaseCount, sizeof(purchaseCount), 1, archivo) != 1) {
            delete newClient;
            break;
        }

        NodeClientPurchases* purchasesList = nullptr;
        NodeClientPurchases* lastPurchase = nullptr;

        for (size_t i = 0; i < purchaseCount; i++) {
            NodeClientPurchases* newPurchase = new NodeClientPurchases;
            if (fread(&newPurchase->purchaseId, sizeof(newPurchase->purchaseId), 1, archivo) != 1) {
                delete newPurchase;
                break;
            }
            newPurchase->next = nullptr;
            if (purchasesList == nullptr) {
                purchasesList = newPurchase;
            } else {
                lastPurchase->next = newPurchase;
            }
            lastPurchase = newPurchase;
        }

        newClient->info.purchasesList = purchasesList;

        if (newClient->info.id > lastClientId) {
            lastClientId = newClient->info.id;
        }

        newClient->next = list;
        list = newClient;
    }

    fclose(archivo); 
}

void clientsMenu(NodeClient *&list) {
    int option, id;
    do {
        std::cout << endl << endl <<"---------------------------\n" << endl;
        cout << YELLOW << "\nGESTIÓN DE CLIENTES \n" << RESET << endl;
        cout << CYAN << "Seleccione una opción:" << endl << endl << RESET
        << "1. Mostrar clientes" << endl
        << "2. Agregar cliente" << endl
        << "3. Modificar cliente por ID" << endl
        << "4. Eliminar cliente por ID" << endl
        << RED << endl
        << "0. Volver al menú principal" << endl
        << RESET;
        cout << CYAN << endl << "Opción: " << RESET;

        cin >> option;
        
        std::cout << endl <<"---------------------------\n" << endl;

        switch (option) {
        case 1:
            showClients(list);
            break;
        case 2:
            addClient(list);
            break;
        case 3:
            cout << "Ingrese el ID del cliente a modificar: ";
            cin >> id;
            updateClient(list, id);
            break;
        case 4:
            cout << "Ingrese el ID del cliente a eliminar: ";
            cin >> id;
            deleteClient(list, id);
            break;
        case 0:
            break;
        default:
            cout << RED << "Opción inválida\n" << RESET;
        }
    } while (option != 0);
}

bool checkClientExists(NodeClient *& list, int id){
    NodeClient *current = list;
    while (current != nullptr){
        if (current->info.id == id) return true;
        current = current->next;
    } return false;
}