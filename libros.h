
#ifndef MAIN_CPP_LIBROS_H
#define MAIN_CPP_LIBROS_H

#include <string>

struct Libro {
    std::string nombre;
    char genero;
    int puntaje;
};

void aumentar_tamanio_libros(int &tamanio, Libro *&libros);

void leer_libros(std::ifstream &f_libros_lectura, Libro *&libros, int &cantidad, int &tamanio);

void escribir_libros(std::ofstream &f_libros_escritura, Libro *libros, int cantidad_libros);


#endif //MAIN_CPP_LIBROS_H
