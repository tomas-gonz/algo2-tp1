#include <iostream>
#include <fstream>
#include <string>
#include "libros.h"
/*Precondiciones:
 * tamanio debe estar inicializado
 */
/*Postcondiciones:
 * Crea un nuevo vector dinamico de tamanio = 2*tamanio y borra el vector anterior.
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
 * f_libros no debe respetar el formato de lectura:
 * TITULO,G,PUNTAJE'/n'.
 */
/*Postcondiciones:
 * Lee y copia la informacion del archivo f_libros en *&libros.
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
 * -
 */
/*Postcondiciones:
 * Abre, lee y copia la informacion del archivo f_libros en *&libros.
 */
void abrir_y_leer_archivo(const std::string &archivo, Libro *&libros, int &cantidad, int &tamanio) {
    std::ifstream f_libros(archivo);
    if (!f_libros.is_open()) {
        perror("Se intenta abrir libros.csv");
        return;
    }
    leer_libros(f_libros, libros, cantidad, tamanio);
    f_libros.close();
}
/*Precondiciones:
 * cantidad_libros debe estar inicializado.
 */
/*Postcondiciones:
 * Escribe la informacion de *libros en el archivo f_libros_escritura.
 * El formato del archivo resultante es:
 * "TITULO",'G',"PUNTAJE"'/n'.
 */
void escribir_libros(std::ofstream &f_libros_escritura, Libro *libros, int cantidad_libros) {

    for (int i = 0; i < cantidad_libros; i++) {
        f_libros_escritura << libros[i].nombre << "," << libros[i].genero << "," << libros[i].puntaje << "\n";
    }
}
