
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

struct Genero {
    std::string genero;
    int puntaje{};
    int cantidad_libros;
};

std::string genero_palabra(char genero_letra) {
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
        std::string genero_str = genero_palabra(libros[i].genero);
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

void aumentar_contador(Genero contador_generos[6], char genero) {

    switch (genero) {
        case AVENTURA:
            contador_generos[0].puntaje++;
            break;
        case CIENCIA_FICCION:
            contador_generos[1].puntaje++;
            break;
        case DIDACTICA:
            contador_generos[2].puntaje++;
            break;
        case POLICIACA:
            contador_generos[3].puntaje++;
            break;
        case ROMANCE:
            contador_generos[4].puntaje++;
            break;
        default:
            contador_generos[5].puntaje++;
    }
}

void calcular_generos_mas_leidos(std::string generos_mas_leidos[], Genero contador_generos[6], int &tope) {
    tope = 1;
    int mas_leido = contador_generos[0].puntaje;
    for (int i = 0; i < 6; i++) {
        if (mas_leido < contador_generos[i].puntaje) {
            tope = 0;
            mas_leido = contador_generos[i].puntaje;
            generos_mas_leidos[tope] = contador_generos[i].genero;
            tope++;
        } else if (mas_leido == contador_generos[i].puntaje) {
            generos_mas_leidos[tope] = contador_generos[i].genero;
            tope++;
        }
    }
}

void inicializar_generos(Genero generos[]) {
    for (int i = 0; i < 6; i++) {
        generos[i].puntaje = 0;
    }
    generos[0].genero = AVENTURA_STR;
    generos[1].genero = CIENCIA_FICCION_STR;
    generos[2].genero = DIDACTICA_STR;
    generos[3].genero = POLICIACA_STR;
    generos[4].genero = ROMANCE_STR;
    generos[5].genero = TERROR_STR;
}

void mostrar_genero_mas_leido(Libro *libros, int cantidad_libros) {
    Genero generos[6];
    inicializar_generos(generos);
    for (int i = 0; i < cantidad_libros; i++) {
        aumentar_contador(generos, libros[i].genero);
    }
    std::string generos_mas_leidos[6];
    int tope = 0;
    calcular_generos_mas_leidos(generos_mas_leidos, generos, tope);
    for (int i = 0; i < tope; i++) {
        std::cout << generos_mas_leidos[i] << std::endl;
    }
}

void mostrar_genero_favorito(Libro *libros, int cantidad_libros) {
    Genero generos[6];
}