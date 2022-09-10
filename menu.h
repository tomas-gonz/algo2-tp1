

#ifndef MAIN_CPP_MENU_H
#define MAIN_CPP_MENU_H

#include "libros.h"

void listar_libros(Libro *libros, int cantidad_libros);

void mostrar_libro_favorito(Libro *libros, int cantidad_libros);

void mostrar_genero_mas_leido(Libro *libros, int cantidad_libros);

void mostrar_genero_favorito(Libro *libros, int cantidad_libros);

void mostrar_tres_libros_menor_puntaje(Libro *libros, int cantidad_libros);

void pedir_y_agregar_libro(Libro *&libros, int &tamanio_libros, int &cantidad_libros);

void pedir_y_editar_puntaje(Libro *&libros, int cantidad_libros);

#endif //MAIN_CPP_MENU_H
