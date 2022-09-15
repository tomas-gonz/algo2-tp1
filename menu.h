

#ifndef MAIN_CPP_MENU_H
#define MAIN_CPP_MENU_H

#include "libros.h"

void imprimir_menu();

void pedir_accion(int &numero);

void
realizar_accion(int numero, Libro *&libros, int &cantidad_libros, int &tamanio_libros,
                const std::string &nombre_archivo,
                int &estado_menu);

#endif //MAIN_CPP_MENU_H
