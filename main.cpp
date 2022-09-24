
#include <iostream>
#include "libros.h"
#include "menu.h"
const int ESTADO_MENU_ACTIVO = 1;

int main(int argc, char **argv) {
    if(argc != 2){
        std::cout << "No se ejecuto el programa con los parametros necesarios, deteniendo el programa." << std::endl;
        return -1;
    }
    int tamanio = 5;
    int cantidad_libros = 0;
    auto *libros = new Libro[tamanio];
    abrir_y_leer_archivo(argv[1], libros, cantidad_libros, tamanio);
    int estado_menu = ESTADO_MENU_ACTIVO;
    char accion = ' ';
    bool hubo_cambios = false;
    do {
        imprimir_menu();
        pedir_accion(accion);
        realizar_accion(accion, libros, cantidad_libros, tamanio, argv[1], estado_menu, hubo_cambios);
    } while (estado_menu == ESTADO_MENU_ACTIVO);
    delete[]libros;
    return 0;
}
