## TP 2 CUATRIMESTRE - SISTEMA DE GESTIÓN DE INVENTARIO PARA TIENDA MINORISTA

### DESCRIPCIÓN

Este proyecto consiste en un sistema para gestionar el inventario de una tienda minorista.

### COMPILACIÓN CON MAKEFILE

1. Clona el repositorio.
2. Compilá usando el Makefile con el comando: **make** en consola.

### EJECUCIÓN

- Ejecutá lo compilado previamente con el comando **make run** en consola.

### PARA BORRAR LO COMPILADO

- Para resetear lo compilado ejecutar **make clean** en consola y luego recompilar con **make** nuevamente.

#### RESUMEN

- Este proyecto está pensado para ser ejecutado con el Makefile el cual se ocupará de crear una carpeta build y correr la compilación realizada previamente. 

- La estructura del proyecto está dividida en 4 directorios principales.

    1. 'data': aquí persiste la información en archivos con formato .dat actuando como una base de datos simple donde se mantiene la información de clientes, productos y proveedores.
    2. 'include': aquí se definen las estructuras y funciones claves que se utilizan a lo largo del programa.
    3. 'src': aquí en source está el archivo principal 'main' junto a los archivos secundarios de clientes, pedidos, productos y proveedores, aquí se encuentra la lógica, el desarrollo de las funciones previamente definidas y el hilo principal del programa.