#include <iostream>
#include <fstream>
#include <string>

struct Libro {
    std::string nombre;
    char genero{};
    int puntaje{};
};

void leer_libros(std::ifstream &f_libros, Libro *libros, int &cantidad) {
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
        libros[cantidad] = libro_aux;
        cantidad++;
    } while (f_libros.good());

}

int main(int argc, char **argv) {
    std::ifstream f_libros(argv[1]);
    if (!f_libros.is_open()) {
        perror("Main intenta abrir libros.csv");
        return 1;
    }
    auto *libros = new Libro[10];
    int cantidad_libros = 0;
    leer_libros(f_libros, libros, cantidad_libros);
    for (int i = 0; i < cantidad_libros - 1; i++) {
        std::cout << libros[i].nombre << "," << libros[i].puntaje << "," << libros[i].genero << std::endl;
    }
    delete[]libros;
    std::cout << "Hello, World!" << std::endl;
    f_libros.close();
    return 0;
}
