#include <iostream>
#include <fstream>
#include <string>
#include "libros.h"
#include "menu.h"


int main(int argc, char **argv) {
    std::ifstream f_libros(argv[1]);
    if (!f_libros.is_open()) {
        perror("Main intenta abrir libros.csv");
        return 1;
    }
    int tamanio = 10;
    auto *libros = new Libro[tamanio];
    int cantidad_libros = 0;
    leer_libros(f_libros, libros, cantidad_libros, tamanio);
    listar_libros(libros, cantidad_libros);
    mostrar_libro_favorito(libros, cantidad_libros);
    mostrar_genero_mas_leido(libros, cantidad_libros);
    mostrar_genero_favorito(libros, cantidad_libros);
    mostrar_tres_libros_menor_puntaje(libros, cantidad_libros);
    bool se_debe_modificar_archivo = false;
    pedir_y_agregar_libro(libros, tamanio, cantidad_libros, se_debe_modificar_archivo);
    pedir_y_editar_puntaje(libros, cantidad_libros, se_debe_modificar_archivo);
    listar_libros(libros, cantidad_libros);
    int estado = 0;
    f_libros.close();
    guardar_y_salir(se_debe_modificar_archivo, argv[1], libros, cantidad_libros, estado);
    delete[]libros;
    return 0;
}
