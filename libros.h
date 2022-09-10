
#ifndef MAIN_CPP_LIBROS_H
#define MAIN_CPP_LIBROS_H

#include <string>

struct Libro {
    std::string nombre;
    char genero;
    int puntaje;
};

void aumentar_tamanio_libros(int &tamanio, Libro *&libros);

void leer_libros(std::ifstream &f_libros, Libro *&libros, int &cantidad, int &tamanio);


#endif //MAIN_CPP_LIBROS_H
