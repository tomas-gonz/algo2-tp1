#include <iostream>
#include <fstream>
#include <string>

struct Libro {
    std::string nombre;
    char genero{};
    int puntaje{};
};

void leer_libros(std::ifstream &f_libros, Libro *libros) {
    Libro libro_aux;
    std::string genero;
    std::string puntaje;
    std::getline(f_libros,libro_aux.nombre,',');
    std::getline(f_libros,genero,',');
    std::getline(f_libros,puntaje,'\n');
    libro_aux.genero = genero[0];
    libro_aux.genero = stoi(puntaje);

}

int main(int argc, char **argv) {
    std::ifstream f_libros(argv[1]);
    if (!f_libros.is_open()) {
        perror("in main trying to open file");
        return 1;
    }
    auto *libros = new Libro[10];
    leer_libros(f_libros, libros);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}