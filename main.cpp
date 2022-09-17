#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "libros.h"
#include "menu.h"


int main(int argc, char **argv) {
    std::ifstream f_libros(argv[1]);
    if (!f_libros.is_open()) {
        perror("Main intenta abrir libros.csv");
        return 1;
    }
    int tamanio = 5;
    auto *libros = new Libro[tamanio];
    int cantidad_libros = 0;
    leer_libros(f_libros, libros, cantidad_libros, tamanio);
    f_libros.close();
    int estado_menu = 1;
    char accion = ' ';
    bool hubo_cambios = false;
    do {

        imprimir_menu();
        pedir_accion(accion);
        realizar_accion(accion, libros, cantidad_libros, tamanio, argv[1], estado_menu, hubo_cambios);
    } while (estado_menu == 1);
    delete[]libros;
    return 0;
}
