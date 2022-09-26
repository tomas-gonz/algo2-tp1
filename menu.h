#ifndef MAIN_CPP_MENU_H
#define MAIN_CPP_MENU_H

#include "libros.h"

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Imprime por pantalla el interfaz del menu.
 */
void imprimir_menu();

/*Precondiciones:
 * El usuario debe ingresar un numero cuando se le pide ingresar una accion para utilizar el menu.
 */
/*Postcondiciones:
 * Pide al usuario la accion hasta que esta se encuentre dentro del rango valido.
 * Es valido si accion es mayor o igual que MIN_ACCION y menor o igual que MAX_ACCION.
 */
void pedir_accion(int &accion);

/*Precondiciones:
 * accion, cantidad_libros y tamanio_libros deben estar inicializados.
 */
/*Postcondiciones:
 * El procedimiento se encarga de realizar la accion del menu.
 */
void
realizar_accion(int &accion, Libro *&libros, int &cantidad_libros, int &tamanio_libros,
                const std::string &nombre_archivo,
                int &estado_menu, bool &hubo_cambios);

#endif //MAIN_CPP_MENU_H
