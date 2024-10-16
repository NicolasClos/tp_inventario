#ifndef CLIENTES_H
#define CLIENTES_H

struct NodoCompras {
    
};

struct infoClientes {
    int id;
    char nombre[50];
    char direccion[50];
    int telefono;
    NodoCompras* comprasAnteriores;
};

struct NodoClientes {
    infoClientes info;
    NodoClientes* sig;
};

void agregarNodoCliente(NodoClientes*& lista, infoClientes x);
void mostrarNodoClientes(NodoClientes* lista);

#endif