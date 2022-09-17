
#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>

const char AVENTURA_INICIAL = 'A';
const char CIENCIA_FICCION_INICIAL = 'C';
const char DIDACTICA_INICIAL = 'D';
const char POLICIACA_INICIAL = 'P';
const char ROMANCE_INICIAL = 'R';
const char TERROR_INICIAL = 'T';
const std::string GENEROS[] = {"Aventura", "Ciencia ficcion", "Didactica", "Policiaca", "Romance", "Terror"};

const int NO_ENCONTRADO = -1;
const int MAX_PUNTAJE = 100;
const int MIN_PUNTAJE = 0;

const int LISTAR_LIBROS = 1;
const int MOSTRAR_LIBRO_FAVORITO = 2;
const int MOSTRAR_GENERO_MAS_LEIDO = 3;
const int MOSTRAR_GENERO_FAVORITO = 4;
const int MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE = 5;
const int PEDIR_Y_AGREGAR_LIBRO = 6;
const int PEDIR_Y_EDITAR_PUNTAJE = 7;
const int GUARDAR_Y_SALIR = 8;


struct Genero {
    std::string genero;
    int puntaje_total{};
    int cantidad_libros{};
};

std::string genero_palabra(char genero_letra) {
    std::string genero_palabra;
    switch (genero_letra) {
        case AVENTURA_INICIAL:
            genero_palabra = GENEROS[0];
            break;
        case CIENCIA_FICCION_INICIAL:
            genero_palabra = GENEROS[1];
            break;
        case DIDACTICA_INICIAL:
            genero_palabra = GENEROS[2];
            break;
        case POLICIACA_INICIAL:
            genero_palabra = GENEROS[3];
            break;
        case ROMANCE_INICIAL:
            genero_palabra = GENEROS[4];
            break;
        default:
            genero_palabra = GENEROS[5];
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

void aumentar_cantidad_y_puntaje(Genero contador_generos[6], char genero, int cantidad, int puntaje_obtenido) {

    switch (genero) {
        case AVENTURA_INICIAL:
            contador_generos[0].cantidad_libros += cantidad;
            contador_generos[0].puntaje_total += puntaje_obtenido;
            break;
        case CIENCIA_FICCION_INICIAL:
            contador_generos[1].cantidad_libros += cantidad;
            contador_generos[1].puntaje_total += puntaje_obtenido;
            break;
        case DIDACTICA_INICIAL:
            contador_generos[2].cantidad_libros += cantidad;
            contador_generos[2].puntaje_total += puntaje_obtenido;
            break;
        case POLICIACA_INICIAL:
            contador_generos[3].cantidad_libros += cantidad;
            contador_generos[3].puntaje_total += puntaje_obtenido;
            break;
        case ROMANCE_INICIAL:
            contador_generos[4].cantidad_libros += cantidad;
            contador_generos[4].puntaje_total += puntaje_obtenido;
            break;
        default:
            contador_generos[5].cantidad_libros += cantidad;
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
        generos[i].genero = GENEROS[i];
    }
}

void mostrar_genero_mas_leido(Libro *libros, int cantidad_libros) {
    Genero generos[6];
    inicializar_generos(generos);
    for (int i = 0; i < cantidad_libros; i++) {
        aumentar_cantidad_y_puntaje(generos, libros[i].genero, 1, 0);
    }
    std::string generos_mas_leidos[6];
    int tope = 0;
    calcular_generos_mas_leidos(generos_mas_leidos, generos, tope);
    for (int i = 0; i < tope; i++) {
        std::cout << generos_mas_leidos[i] << std::endl;
    }
}

void calcular_generos_favoritos(std::string generos_favoritos[], Genero generos[], int &tope) {
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
        aumentar_cantidad_y_puntaje(generos, libros[i].genero, 1, libros[i].puntaje);
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
    int indice = NO_ENCONTRADO;
    int i = 0;
    while (indice == NO_ENCONTRADO && i < cantidad_libros) {
        if (libros[i].nombre == titulo_buscado)
            indice = i;
        i++;
    }
    return indice;
}

bool es_genero_valido(char letra) {
    return letra == AVENTURA_INICIAL || letra == CIENCIA_FICCION_INICIAL || letra == DIDACTICA_INICIAL ||
           letra == POLICIACA_INICIAL ||
           letra == ROMANCE_INICIAL || letra == TERROR_INICIAL;
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
        std::cout << "Ingrese el puntaje del libro entre " << MIN_PUNTAJE << " y " << MAX_PUNTAJE << std::endl;
        std::cin >> libro.puntaje;
    } while (libro.puntaje > MAX_PUNTAJE || libro.puntaje < MIN_PUNTAJE);
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
                int &estado_menu, bool &hubo_cambios) {

    switch (numero) {
        case LISTAR_LIBROS:
            listar_libros(libros, cantidad_libros);
            break;
        case MOSTRAR_LIBRO_FAVORITO:
            mostrar_libro_favorito(libros, cantidad_libros);
            break;
        case MOSTRAR_GENERO_MAS_LEIDO:
            mostrar_genero_mas_leido(libros, cantidad_libros);
            break;
        case MOSTRAR_GENERO_FAVORITO:
            mostrar_genero_favorito(libros, cantidad_libros);
            break;
        case MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE:
            mostrar_tres_libros_menor_puntaje(libros, cantidad_libros);
            break;
        case PEDIR_Y_AGREGAR_LIBRO:
            pedir_y_agregar_libro(libros, tamanio_libros, cantidad_libros, hubo_cambios);
            break;
        case PEDIR_Y_EDITAR_PUNTAJE:
            pedir_y_editar_puntaje(libros, cantidad_libros, hubo_cambios);
            break;
        case GUARDAR_Y_SALIR:
            guardar_y_salir(hubo_cambios, nombre_archivo, libros, cantidad_libros, estado_menu);
            break;
    }
}
