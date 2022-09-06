#include <iostream>
#include <fstream>
#include <string>
#include "libros.h"


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
    delete[]libros;
    f_libros.close();
    return 0;
}
