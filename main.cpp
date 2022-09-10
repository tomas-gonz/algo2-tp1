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
    std::cout<<cantidad_libros<<std::endl;
    listar_libros(libros, cantidad_libros);
    mostrar_libro_favorito(libros, cantidad_libros);
    mostrar_genero_mas_leido(libros, cantidad_libros);
    mostrar_genero_favorito(libros, cantidad_libros);
    mostrar_tres_libros_menor_puntaje(libros, cantidad_libros);
    pedir_agregar_libro(libros, tamanio, cantidad_libros);
    listar_libros(libros, cantidad_libros);
    std::cout<<cantidad_libros<<std::endl;
    delete[]libros;
    f_libros.close();
    return 0;
}
