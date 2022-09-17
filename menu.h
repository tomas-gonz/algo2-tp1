

#ifndef MAIN_CPP_MENU_H
#define MAIN_CPP_MENU_H

#include "libros.h"

void imprimir_menu();

void pedir_accion(char &accion);

void
realizar_accion(int numero, Libro *&libros, int &cantidad_libros, int &tamanio_libros,
                const std::string &nombre_archivo,
                int &estado_menu, bool &hubo_cambios);

#endif //MAIN_CPP_MENU_H
