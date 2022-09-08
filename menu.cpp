
#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>

const char AVENTURA = 'A';
const char CIENCIA_FICCION = 'C';
const char DIDACTICA = 'D';
const char POLICIACA = 'P';
const char ROMANCE = 'R';
const char TERROR = 'T';
const std::string AVENTURA_STR = "Aventura";
const std::string CIENCIA_FICCION_STR = "Ciencia ficcion";
const std::string DIDACTICA_STR = "Didactica";
const std::string POLICIACA_STR = "Policiaca";
const std::string ROMANCE_STR = "Romance";
const std::string TERROR_STR = "Terror";

std::string genero(char genero_letra) {
    std::string genero_palabra;
    switch (genero_letra) {
        case AVENTURA:
            genero_palabra = AVENTURA_STR;
            break;
        case CIENCIA_FICCION:
            genero_palabra = CIENCIA_FICCION_STR;
            break;
        case DIDACTICA:
            genero_palabra = DIDACTICA_STR;
            break;
        case POLICIACA:
            genero_palabra = POLICIACA_STR;
            break;
        case ROMANCE:
            genero_palabra = ROMANCE_STR;
            break;
        default:
            genero_palabra = TERROR_STR;
    }
    return genero_palabra;
}

void listar_libros(Libro *libros, int cantidad_libros) {
    for (int i = 0; i < cantidad_libros - 1; i++) {
        std::string genero_str = genero(libros[i].genero);
        std::cout << libros[i].nombre << "," << libros[i].puntaje << "," << genero_str << std::endl;
    }
}

int lista_libros_favoritos(Libro *libros, int cantidad_libros, std::string libros_favoritos[], int &tope) {
    libros_favoritos[0] = libros[0].nombre;
    int puntaje_mayor = libros[0].puntaje;
    tope = 0;
    for (int i = 1; i < cantidad_libros; i++) {
        if (libros[i].puntaje > puntaje_mayor) {
            tope = 0;
            libros_favoritos[tope] = libros[i].nombre;
            puntaje_mayor = libros[i].puntaje;
        } else if (libros[i].puntaje == puntaje_mayor) {
            tope++;
            libros_favoritos[tope] = libros[i].nombre;
        }
    }
    return puntaje_mayor;
}

void mostrar_libro_favorito(Libro *libros, int cantidad_libros) {
    std::string libros_favoritos[cantidad_libros];
    int tope = 0;
    int puntaje_mayor = lista_libros_favoritos(libros, cantidad_libros, libros_favoritos, tope);
    int i = 0;
    do {
        std::cout << libros_favoritos[i] << std::endl;
        i++;
    } while (i < tope);
    std::cout << puntaje_mayor << std::endl;
}