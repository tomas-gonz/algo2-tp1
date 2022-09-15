
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
    int puntaje_total{};
    int cantidad_libros{};
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
    for (int i = 0; i < cantidad_libros; i++) {
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

void aumentar_cantidad(Genero contador_generos[6], char genero) {

    switch (genero) {
        case AVENTURA:
            contador_generos[0].cantidad_libros++;
            break;
        case CIENCIA_FICCION:
            contador_generos[1].cantidad_libros++;
            break;
        case DIDACTICA:
            contador_generos[2].cantidad_libros++;
            break;
        case POLICIACA:
            contador_generos[3].cantidad_libros++;
            break;
        case ROMANCE:
            contador_generos[4].cantidad_libros++;
            break;
        default:
            contador_generos[5].cantidad_libros++;
    }
}

void aumentar_puntaje(Genero contador_generos[6], char genero, int puntaje_obtenido) {

    switch (genero) {
        case AVENTURA:
            contador_generos[0].puntaje_total += puntaje_obtenido;
            break;
        case CIENCIA_FICCION:
            contador_generos[1].puntaje_total += puntaje_obtenido;
            break;
        case DIDACTICA:
            contador_generos[2].puntaje_total += puntaje_obtenido;
            break;
        case POLICIACA:
            contador_generos[3].puntaje_total += puntaje_obtenido;
            break;
        case ROMANCE:
            contador_generos[4].puntaje_total += puntaje_obtenido;
            break;
        default:
            contador_generos[5].puntaje_total += puntaje_obtenido;
    }
}

void calcular_generos_mas_leidos(std::string generos_mas_leidos[], Genero contador_generos[6], int &tope) {
    tope = 1;
    int mas_leido = contador_generos[0].cantidad_libros;
    for (int i = 0; i < 6; i++) {
        if (mas_leido < contador_generos[i].cantidad_libros) {
            tope = 0;
            mas_leido = contador_generos[i].cantidad_libros;
            generos_mas_leidos[tope] = contador_generos[i].genero;
            tope++;
        } else if (mas_leido == contador_generos[i].cantidad_libros) {
            generos_mas_leidos[tope] = contador_generos[i].genero;
            tope++;
        }
    }
}

void inicializar_generos(Genero generos[]) {
    for (int i = 0; i < 6; i++) {
        generos[i].cantidad_libros = 0;
        generos[i].puntaje_total = 0;
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
        aumentar_cantidad(generos, libros[i].genero);
    }
    std::string generos_mas_leidos[6];
    int tope = 0;
    calcular_generos_mas_leidos(generos_mas_leidos, generos, tope);
    for (int i = 0; i < tope; i++) {
        std::cout << generos_mas_leidos[i] << std::endl;
    }
}

void calcular_generos_favoritos(std::string generos_favoritos[], Genero generos[6], int &tope) {
    tope = 1;
    int mayor_puntaje = generos[0].puntaje_total / generos[0].cantidad_libros;
    for (int i = 0; i < 6; i++) {
        if (mayor_puntaje < generos[i].puntaje_total / generos[i].cantidad_libros) {
            tope = 0;
            mayor_puntaje = generos[i].puntaje_total / generos[i].cantidad_libros;
            generos_favoritos[tope] = generos[i].genero;
            tope++;
        } else if (mayor_puntaje == generos[i].puntaje_total / generos[i].cantidad_libros) {
            generos_favoritos[tope] = generos[i].genero;
            tope++;
        }
    }
}

void mostrar_genero_favorito(Libro *libros, int cantidad_libros) {
    Genero generos[6];
    inicializar_generos(generos);
    for (int i = 0; i < cantidad_libros; i++) {
        aumentar_cantidad(generos, libros[i].genero);
        aumentar_puntaje(generos, libros[i].genero, libros[i].puntaje);
    }
    std::string generos_favoritos[6];
    int tope = 0;
    calcular_generos_favoritos(generos_favoritos, generos, tope);
    for (int i = 0; i < tope; i++) {
        std::cout << generos_favoritos[i] << std::endl;
    }
}

bool nuevo_libro_es_menor(const Libro &libro_viejo, const Libro &libro_nuevo) {
    return libro_nuevo.puntaje < libro_viejo.puntaje || libro_nuevo.nombre < libro_viejo.nombre;
}

void modificar_libros_menos_favoritos(const Libro &libro, Libro libros_menor_puntaje[], int indice) {
    if (indice == 2) {
        if (nuevo_libro_es_menor(libros_menor_puntaje[2], libro))
            libros_menor_puntaje[2] = libro;
    } else if (indice == 1) {
        if (nuevo_libro_es_menor(libros_menor_puntaje[1], libro)) {
            libros_menor_puntaje[2] = libros_menor_puntaje[1];
            libros_menor_puntaje[1] = libro;
        } else if (libro.nombre < libros_menor_puntaje[1].nombre)
            libros_menor_puntaje[2] = libro;
    } else {
        libros_menor_puntaje[2] = libros_menor_puntaje[1];
        if (nuevo_libro_es_menor(libros_menor_puntaje[0], libro)) {
            libros_menor_puntaje[1] = libros_menor_puntaje[0];
            libros_menor_puntaje[0] = libro;
        } else if (libro.nombre > libros_menor_puntaje[0].nombre)
            libros_menor_puntaje[1] = libro;
    }
}


void obtener_tres_libros_menor_puntaje(Libro *libros, int cantidad_libros, Libro libros_menor_puntaje[]) {
    libros_menor_puntaje[0] = libros[0];
    libros_menor_puntaje[1] = libros[1];
    libros_menor_puntaje[2] = libros[2];
    for (int i = 0; i < cantidad_libros; i++) {
        if (libros[i].puntaje <= libros_menor_puntaje[0].puntaje)
            modificar_libros_menos_favoritos(libros[i], libros_menor_puntaje, 0);
        else if (libros[i].puntaje <= libros_menor_puntaje[1].puntaje)
            modificar_libros_menos_favoritos(libros[i], libros_menor_puntaje, 1);
        else if (libros[i].puntaje <= libros_menor_puntaje[2].puntaje)
            modificar_libros_menos_favoritos(libros[i], libros_menor_puntaje, 2);
    }
}

void mostrar_tres_libros_menor_puntaje(Libro *libros, int cantidad_libros) {
    Libro libros_menor_puntaje[3];
    obtener_tres_libros_menor_puntaje(libros, cantidad_libros, libros_menor_puntaje);
    for (auto &i: libros_menor_puntaje) {
        std::cout << i.nombre << " " << std::endl;
    }
}

int indice_libro_buscado(Libro *libros, int cantidad_libros, const std::string &titulo_buscado) {
    int indice = -1;
    int i = 0;
    while (indice == -1 && i < cantidad_libros) {
        if (libros[i].nombre == titulo_buscado)
            indice = i;
        i++;
    }
    return indice;
}

bool es_genero_valido(char letra) {
    return letra == AVENTURA || letra == CIENCIA_FICCION || letra == DIDACTICA || letra == POLICIACA ||
           letra == ROMANCE || letra == TERROR;
}

void pedir_libro(Libro &libro) {
    std::cout << "Ingrese el nombre del libro que quiere agregar a la lista" << std::endl;
    std::cin.ignore();
    getline(std::cin, libro.nombre);
    do {
        std::cout << "Ingrese el genero del libro, debe ser una de las siguientes inciales: FALTA" << std::endl;
        std::cin >> libro.genero;
    } while (!es_genero_valido(libro.genero));
    do {
        std::cout << "Ingrese el puntaje del libro entre 0 y 100" << std::endl;
        std::cin >> libro.puntaje;
    } while (libro.puntaje > 100 || libro.puntaje < 0);
}

void agregar_libro(Libro *&libros, int &tamanio_libros, int &cantidad_libros, const Libro &libro_nuevo) {
    if (tamanio_libros == cantidad_libros)
        aumentar_tamanio_libros(tamanio_libros, libros);
    libros[cantidad_libros] = libro_nuevo;
    cantidad_libros++;
}

void pedir_y_agregar_libro(Libro *&libros, int &tamanio_libros, int &cantidad_libros, bool &hubo_cambios) {
    hubo_cambios = false;
    Libro libro_nuevo;
    pedir_libro(libro_nuevo);
    if (indice_libro_buscado(libros, cantidad_libros, libro_nuevo.nombre) == -1) {
        agregar_libro(libros, tamanio_libros, cantidad_libros, libro_nuevo);
        hubo_cambios = true;
        std::cout << "Se agrego el libro correctamente" << std::endl;
    } else
        std::cout << "Ya existe este libro en la lista" << std::endl;
}

void pedir_nuevo_puntaje(Libro *libros, int cantidad_libros, int &puntaje_nuevo, int &indice) {
    std::string titulo = " ";
    indice = -1;
    std::cout << "Ingrese el nombre del libro cuyo puntaje quiere modificar" << std::endl;
    std::cin.ignore();
    getline(std::cin, titulo);
    indice = indice_libro_buscado(libros, cantidad_libros, titulo);
    if (indice != -1) {
        do {
            std::cout << "Ingrese el nuevo puntaje, entre 0 y 100" << std::endl;
            std::cin >> puntaje_nuevo;
        } while (puntaje_nuevo < 0 || puntaje_nuevo > 100);
    } else
        std::cout << titulo << " no se encuentra en la lista de libros." << std::endl;
}

void pedir_y_editar_puntaje(Libro *&libros, int cantidad_libros, bool &hubo_cambios) {
    hubo_cambios = false;
    int indice_libro = 0;
    int puntaje_nuevo = 0;
    pedir_nuevo_puntaje(libros, cantidad_libros, puntaje_nuevo, indice_libro);
    if (indice_libro != -1) {
        libros[indice_libro].puntaje = puntaje_nuevo;
        hubo_cambios = true;
    }
}

void guardar_y_salir(bool hubo_cambios, const std::string &nombre_archivo, Libro *libros, int cantidad_libros,
                     int &estado_menu) {
    if (hubo_cambios) {
        std::ofstream f_libros_escritura(nombre_archivo);
        if (!f_libros_escritura.is_open()) {
            perror("Se intenta abrir libros.csv");
            return;
        }
        escribir_libros(f_libros_escritura, libros, cantidad_libros);
        std::cout << "Se han guardado los cambios correctamente. Cerrando el menu.";
    } else
        std::cout << "No hubieron cambios realizados. Cerrando el menu.";
    estado_menu = 0;
}

void imprimir_menu() {
    std::cout << "Bienvenido/a !!" << std::endl;
    std::cout << "---------------MENU---------------" << std::endl;
    std::cout << "1 -> Listar libros leidos." << std::endl;
    std::cout << "2 -> Mostrar libro favorito." << std::endl;
    std::cout << "3 -> Mostrar genero mas leido." << std::endl;
    std::cout << "4 -> Mostrar genero favorito." << std::endl;
    std::cout << "5 -> Mostrar los 3 libros con menor puntaje." << std::endl;
    std::cout << "6 -> Agregar libro." << std::endl;
    std::cout << "7 -> Editar puntaje de un libro por titulo." << std::endl;
    std::cout << "8 -> Guardar y salir." << std::endl;
}

void pedir_accion(int &numero) {
    numero = 0;
    do {
        std::cout << "Ingrese un numero, del 1 al 8 para utilizar el menu." << std::endl;
    } while (numero > 1 && numero < 8);
    std::cin >> numero;
}

void
realizar_accion(int numero, Libro *&libros, int &cantidad_libros, int &tamanio_libros,
                const std::string &nombre_archivo,
                int &estado_menu) {

    bool hubo_cambios = false;
    switch (numero) {
        case 1:
            listar_libros(libros, cantidad_libros);
            break;
        case 2:
            mostrar_libro_favorito(libros, cantidad_libros);
            break;
        case 3:
            mostrar_genero_mas_leido(libros, cantidad_libros);
            break;
        case 4:
            mostrar_genero_favorito(libros, cantidad_libros);
            break;
        case 5:
            mostrar_tres_libros_menor_puntaje(libros, cantidad_libros);
            break;
        case 6:
            pedir_y_agregar_libro(libros, tamanio_libros, cantidad_libros, hubo_cambios);
            break;
        case 7:
            pedir_y_editar_puntaje(libros, cantidad_libros, hubo_cambios);
            break;
        case 8:
            guardar_y_salir(hubo_cambios, nombre_archivo, libros, cantidad_libros, estado_menu);
            break;
    }
}
