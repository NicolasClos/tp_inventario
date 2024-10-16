#include <iostream>
#include "clients.h"

using namespace std;

void agregarNodoCliente(NodoClientes*& lista, infoClientes x) {
    NodoClientes* nuevo = new NodoClientes();
    nuevo->info = x;
    nuevo->sig = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        NodoClientes* aux = lista;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

void mostrarNodoClientes(NodoClientes* lista) {
    NodoClientes* aux = lista;

    while (aux != NULL) {
        cout << aux->info.id << " - ";
        cout << aux->info.nombre << " - ";
        cout << aux->info.direccion << " - ";
        cout << aux->info.telefono << endl;
        aux = aux->sig;
    }
}