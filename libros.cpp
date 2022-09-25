#include <iostream>
#include <fstream>
#include <string>
#include "libros.h"
/*Precondiciones:
 *
 */
/*Postcondiciones:
 *
 */
void aumentar_tamanio_libros(int &tamanio, Libro *&libros) {
    auto *libros_aux = new Libro[tamanio * 2];
    for (int i = 0; i < tamanio; i++) {
        libros_aux[i] = libros[i];
    }
    delete[]libros;
    tamanio = tamanio * 2;
    libros = libros_aux;
}
/*Precondiciones:
 *
 */
/*Postcondiciones:
 *
 */
void leer_libros(std::ifstream &f_libros, Libro *&libros, int &cantidad, int &tamanio) {
    Libro libro_aux;
    cantidad = 0;
    std::string genero;
    std::string puntaje;
    do {
        std::getline(f_libros, libro_aux.nombre, ',');
        std::getline(f_libros, genero, ',');
        std::getline(f_libros, puntaje, '\n');
        libro_aux.genero = genero[0];
        libro_aux.puntaje = stoi(puntaje);
        if (cantidad == tamanio)
            aumentar_tamanio_libros(tamanio, libros);
        libros[cantidad] = libro_aux;
        cantidad++;
    } while (f_libros.good());
    cantidad--;
}
/*Precondiciones:
 *
 */
/*Postcondiciones:
 *
 */
void abrir_y_leer_archivo(const std::string& archivo, Libro *&libros, int &cantidad, int &tamanio) {
    std::ifstream f_libros(archivo);
    if (!f_libros.is_open()) {
        perror("Se intenta abrir libros.csv");
        return;
    }
    leer_libros(f_libros, libros, cantidad, tamanio);
    f_libros.close();
}
/*Precondiciones:
 *
 */
/*Postcondiciones:
 *
 */
void escribir_libros(std::ofstream &f_libros_escritura, Libro *libros, int cantidad_libros) {

    for (int i = 0; i < cantidad_libros; i++) {
        f_libros_escritura << libros[i].nombre << "," << libros[i].genero << "," << libros[i].puntaje << "\n";
    }
}
