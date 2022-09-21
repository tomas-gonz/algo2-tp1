
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

const int MAX_GENEROS = 6;
const char GENEROS_INICIALES[] = {'A', 'C', 'D', 'P', 'R', 'T'};
const std::string GENEROS[] = {"Aventura", "Ciencia ficcion", "Didactica", "Policiaca", "Romance", "Terror"};

const int NO_ENCONTRADO = -1;
const int MAX_PUNTAJE = 100;
const int MIN_PUNTAJE = 0;

const int MAX_ACCIONES = 8;
const char LISTAR_LIBROS = '1';
const char MOSTRAR_LIBRO_FAVORITO = '2';
const int MOSTRAR_GENERO_MAS_LEIDO = '3';
const int MOSTRAR_GENERO_FAVORITO = '4';
const int MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE = '5';
const int PEDIR_Y_AGREGAR_LIBRO = '6';
const int PEDIR_Y_EDITAR_PUNTAJE = '7';
const int GUARDAR_Y_SALIR = '8';


struct Genero {
    char genero{};
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
        case TERROR_INICIAL:
            genero_palabra = GENEROS[5];
        default:
            std::cout << "Error, genero no encontrado";
    }
    return genero_palabra;
}

void listar_libros(Libro *libros, int cantidad_libros) {
    std::cout << "Listando los libros:" << std::endl;
    for (int i = 0; i < cantidad_libros; i++) {

        std::string genero_str = genero_palabra(libros[i].genero);
        std::cout << i + 1 << ") " << libros[i].nombre << " ," << libros[i].puntaje << " puntos";
        std::cout << ", de genero " << genero_str << std::endl;
    }


}

void
obtener_libros_favoritos(Libro *libros, int cantidad_libros, std::string libros_favoritos[], int &tope,
                         int &mayor_puntaje) {
    libros_favoritos[0] = libros[0].nombre;
    mayor_puntaje = libros[0].puntaje;
    tope = 1;
    for (int i = 1; i < cantidad_libros; i++) {
        if (libros[i].puntaje > mayor_puntaje) {
            tope = 0;
            libros_favoritos[tope] = libros[i].nombre;
            mayor_puntaje = libros[i].puntaje;
            tope++;
        } else if (libros[i].puntaje == mayor_puntaje) {
            libros_favoritos[tope] = libros[i].nombre;
            tope++;
        }
    }
}

void mostrar_libros_favoritos(std::string libros_favoritos[], int tope, int puntaje_mayor) {

    std::cout << "Lista de libros favoritos:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << libros_favoritos[i] << std::endl;
    }
    std::cout << "El puntaje mayor es " << puntaje_mayor << std::endl;
}

void obtener_y_mostrar_libros_favoritos(Libro *libros, int cantidad_libros) {
    std::string libros_favoritos[cantidad_libros];
    int tope = 0;
    int puntaje_mayor = 0;
    obtener_libros_favoritos(libros, cantidad_libros, libros_favoritos, tope, puntaje_mayor);
    mostrar_libros_favoritos(libros_favoritos, tope, puntaje_mayor);
}

void aumentar_cantidad_y_puntaje_en_generos(Genero generos[], char genero_buscado, int puntaje_obtenido) {
    int i = 0;
    bool genero_encontrado = false;
    while (i < MAX_GENEROS && !genero_encontrado) {
        if (generos[i].genero == genero_buscado) {
            genero_encontrado = true;
            generos[i].cantidad_libros++;
            generos[i].puntaje_total += puntaje_obtenido;
        }
        i++;
    }
}

void inicializar_generos(Genero generos[], Libro *libros, int cantidad_libros) {
    for (int i = 0; i < MAX_GENEROS; i++) {
        generos[i].cantidad_libros = 0;
        generos[i].puntaje_total = 0;
        generos[i].genero = GENEROS_INICIALES[i];
    }
    for (int i = 0; i < cantidad_libros; i++) {
        aumentar_cantidad_y_puntaje_en_generos(generos, libros[i].genero, libros[i].puntaje);
    }
}

void obtener_generos_mas_leidos(std::string generos_mas_leidos[], Genero generos[], int &tope) {
    tope = 1;
    int mas_leido = generos[0].cantidad_libros;
    generos_mas_leidos[0] = genero_palabra(generos[0].genero);
    for (int i = 1; i < MAX_GENEROS; i++) {
        if (mas_leido < generos[i].cantidad_libros) {
            tope = 0;
            mas_leido = generos[i].cantidad_libros;
            generos_mas_leidos[tope] = genero_palabra(generos[i].genero);
            tope++;
        } else if (mas_leido == generos[i].cantidad_libros) {
            generos_mas_leidos[tope] = genero_palabra(generos[i].genero);
            tope++;
        }
    }
}

void mostrar_generos_mas_leidos(std::string generos_mas_leidos[], int tope) {
    std::cout << "Los generos mas leidos son:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << generos_mas_leidos[i] << std::endl;
    }
}

void obtener_y_mostrar_generos_mas_leidos(Libro *libros, int cantidad_libros) {
    Genero generos[MAX_GENEROS];
    std::string generos_mas_leidos[MAX_GENEROS];
    int tope = 0;
    inicializar_generos(generos, libros, cantidad_libros);
    obtener_generos_mas_leidos(generos_mas_leidos, generos, tope);
    mostrar_generos_mas_leidos(generos_mas_leidos, tope);
}

void obtener_generos_favoritos(std::string generos_favoritos[], Genero generos[], int &tope) {
    tope = 1;
    int mayor_promedio = generos[0].puntaje_total / generos[0].cantidad_libros;
    for (int i = 1; i < MAX_GENEROS; i++) {
        if (mayor_promedio < generos[i].puntaje_total / generos[i].cantidad_libros) {
            tope = 0;
            mayor_promedio = generos[i].puntaje_total / generos[i].cantidad_libros;
            generos_favoritos[tope] = genero_palabra(generos[i].genero);
            tope++;
        } else if (mayor_promedio == generos[i].puntaje_total / generos[i].cantidad_libros) {
            generos_favoritos[tope] = genero_palabra(generos[i].genero);
            tope++;
        }
    }
}

void mostrar_generos_favoritos(std::string generos_favoritos[], int tope) {
    std::cout << "Los generos favoritos son:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << generos_favoritos[i] << std::endl;
    }
}

void obtener_y_mostrar_generos_favoritos(Libro *libros, int cantidad_libros) {
    Genero generos[MAX_GENEROS];
    std::string generos_favoritos[MAX_GENEROS];
    int tope = 0;
    inicializar_generos(generos, libros, cantidad_libros);
    obtener_generos_favoritos(generos_favoritos, generos, tope);
    mostrar_generos_favoritos(generos_favoritos, tope);
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

void mostrar_tres_libros_menor_puntaje(Libro libros_menor_puntaje[], int tope) {
    std::cout << "Los tres libros con menor puntaje son:" << std::endl;
    for (int i = 0; i < tope; i++){
        std::cout << libros_menor_puntaje[i].nombre << std::endl;
    }
}
void obtener_y_mostrar_tres_libros_menor_puntaje(Libro *libros, int cantidad_libros){
    Libro libros_menor_puntaje[3];
    obtener_tres_libros_menor_puntaje(libros, cantidad_libros, libros_menor_puntaje);
    mostrar_tres_libros_menor_puntaje(libros_menor_puntaje, 3);
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
    int i = 0;
    bool es_genero_valido = false;
    while(i < MAX_GENEROS && !es_genero_valido){
        if(letra == GENEROS_INICIALES[i])
            es_genero_valido = true;
        i++;
    }
    return es_genero_valido;
}

void pedir_libro(Libro &libro) {
    std::cout << "Ingrese el nombre del libro que quiere agregar a la lista" << std::endl;
    std::cin.ignore();
    getline(std::cin, libro.nombre);
    do {
        std::cout << "Ingrese la inicial del genero del libro, debe ser una de las siguientes inciales:" << std::endl;
        for(int i = 0; i < MAX_GENEROS; i++){
            std::cout << GENEROS_INICIALES[i] << " -> " << GENEROS[i] << std::endl;
        }
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
    std::cout << "_--------------------MENU--------------------_" << std::endl;
    std::cout << "1 -> Listar libros leidos." << std::endl;
    std::cout << "2 -> Mostrar libros favoritos." << std::endl;
    std::cout << "3 -> Mostrar generos mas leidos." << std::endl;
    std::cout << "4 -> Mostrar generos favoritos." << std::endl;
    std::cout << "5 -> Mostrar los 3 libros con menor puntaje." << std::endl;
    std::cout << "6 -> Agregar libro." << std::endl;
    std::cout << "7 -> Editar puntaje de un libro por titulo." << std::endl;
    std::cout << "8 -> Guardar y salir." << std::endl;
}

void pedir_accion(char &accion) {

    accion = 0;
    do {
        std::cout << "Ingrese un numero, del 1 al " << MAX_ACCIONES << " para utilizar el menu." << std::endl;
        std::cin >> accion;
    } while (accion < '1' || accion > '8');
}

void volver_al_menu() {
    char aux;
    std::cout << "Ingrese cualquier character para volver al menu" << std::endl;
    std::cin >> aux;
}

void
realizar_accion(char accion, Libro *&libros, int &cantidad_libros, int &tamanio_libros,
                const std::string &nombre_archivo,
                int &estado_menu, bool &hubo_cambios) {

    switch (accion) {
        case LISTAR_LIBROS:
            listar_libros(libros, cantidad_libros);
            volver_al_menu();
            break;
        case MOSTRAR_LIBRO_FAVORITO:
            obtener_y_mostrar_libros_favoritos(libros, cantidad_libros);
            volver_al_menu();
            break;
        case MOSTRAR_GENERO_MAS_LEIDO:
            obtener_y_mostrar_generos_mas_leidos(libros, cantidad_libros);
            volver_al_menu();
            break;
        case MOSTRAR_GENERO_FAVORITO:
            obtener_y_mostrar_generos_favoritos(libros, cantidad_libros);
            volver_al_menu();
            break;
        case MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE:
            obtener_y_mostrar_tres_libros_menor_puntaje(libros, cantidad_libros);
            volver_al_menu();
            break;
        case PEDIR_Y_AGREGAR_LIBRO:
            pedir_y_agregar_libro(libros, tamanio_libros, cantidad_libros, hubo_cambios);
            volver_al_menu();
            break;
        case PEDIR_Y_EDITAR_PUNTAJE:
            pedir_y_editar_puntaje(libros, cantidad_libros, hubo_cambios);
            volver_al_menu();
            break;
        case GUARDAR_Y_SALIR:
            guardar_y_salir(hubo_cambios, nombre_archivo, libros, cantidad_libros, estado_menu);
            break;
        default:
            std::cout << "Error, el character ingresado no se encuentra en el rango de numeros entre 1 y 8"
                      << std::endl;
            volver_al_menu();
    }
}
