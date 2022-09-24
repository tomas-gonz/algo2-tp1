
#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>

/*
* AVENTURA_INICIAL = 'A';
* CIENCIA_FICCION_INICIAL = 'C';
* DIDACTICA_INICIAL = 'D';
* POLICIACA_INICIAL = 'P';
* ROMANCE_INICIAL = 'R';
* TERROR_INICIAL = 'T';
*/
const int MAX_GENEROS = 6;
const char GENEROS_INICIALES[] = {'A', 'C', 'D', 'P', 'R', 'T'};
const std::string GENEROS[] = {"Aventura", "Ciencia ficcion", "Didactica", "Policiaca", "Romance", "Terror"};

const int NO_ENCONTRADO = -1;
const int MAX_PUNTAJE = 100;
const int MIN_PUNTAJE = 0;

const char MIN_ACCION = '1';
const char MAX_ACCION = '8';
const int MIN_ACCIONES = 1;
const int MAX_ACCIONES = 8;
const char LISTAR_LIBROS = '1';
const char MOSTRAR_LIBRO_FAVORITO = '2';
const int MOSTRAR_GENERO_MAS_LEIDO = '3';
const int MOSTRAR_GENERO_FAVORITO = '4';
const int MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE = '5';
const int PEDIR_Y_AGREGAR_LIBRO = '6';
const int PEDIR_Y_EDITAR_PUNTAJE = '7';
const int GUARDAR_Y_SALIR = '8';
const int CANTIDAD_LIBROS_MENOR_PUNTAJE = 3;

struct Genero {
    char genero{};
    int puntaje_total{};
    int cantidad_libros{};
};

int indice_genero_buscado(char letra) {
    int i = 0;
    int indice_genero_buscado = NO_ENCONTRADO;
    while (i < MAX_GENEROS && indice_genero_buscado == NO_ENCONTRADO) {
        if (letra == GENEROS_INICIALES[i])
            indice_genero_buscado = i;
        i++;
    }
    return indice_genero_buscado;
}

std::string genero_palabra(char genero_letra) {
    int indice = indice_genero_buscado(genero_letra);
    if (indice != NO_ENCONTRADO)
        return GENEROS[indice];
    return "Error, inicial no reconocida como genero posible";
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
    return libro_nuevo.puntaje < libro_viejo.puntaje ||
           libro_nuevo.nombre < libro_viejo.nombre && libro_nuevo.puntaje == libro_viejo.puntaje;
}

void modificar_libros_menor_puntaje(Libro *libros_menor_puntaje, int tope, int indice) {
    for (int i = tope - 1; i > indice; i--) {
        libros_menor_puntaje[i] = libros_menor_puntaje[i - 1];
    }
}

void insertar_libro_menos_favorito(Libro libros_menor_puntaje[], int tope, Libro &libro, int indice) {
    if (nuevo_libro_es_menor(libros_menor_puntaje[indice], libro)) {
        modificar_libros_menor_puntaje(libros_menor_puntaje, tope, indice);
        libros_menor_puntaje[indice] = libro;
    } else if (libros_menor_puntaje[indice].nombre != libro.nombre) {
        modificar_libros_menor_puntaje(libros_menor_puntaje, tope, indice);
        libros_menor_puntaje[indice + 1] = libro;
    }
}

void intercambiar_libros(Libro &libro_a, Libro &libro_b) {
    Libro libro_aux = libro_a;
    libro_a = libro_b;
    libro_b = libro_aux;
}

void ordenar_libros_menor_puntaje(Libro libros_menor_puntaje[], int tope) {
    for (int i = 0; i < tope; i++) {
        for (int j = 0; j < tope - 1; j++) {
            if (nuevo_libro_es_menor(libros_menor_puntaje[j], libros_menor_puntaje[j + 1])) {
                intercambiar_libros(libros_menor_puntaje[j], libros_menor_puntaje[j + 1]);
            }
        }
    }
}

void obtener_n_libros_menor_puntaje(Libro *libros, int cantidad_libros, Libro libros_menor_puntaje[],
                                    int tope_libros_menor_puntaje) {
    for (int i = 0; i < tope_libros_menor_puntaje; i++) {
        libros_menor_puntaje[i] = libros[i];
    }
    ordenar_libros_menor_puntaje(libros_menor_puntaje, tope_libros_menor_puntaje);
    for (int i = tope_libros_menor_puntaje; i < cantidad_libros; i++) {
        for (int j = 0; j < tope_libros_menor_puntaje; j++) {
            if (libros[i].puntaje <= libros_menor_puntaje[j].puntaje) {
                insertar_libro_menos_favorito(libros_menor_puntaje, tope_libros_menor_puntaje, libros[i], j);
                j = tope_libros_menor_puntaje;
            }
        }
    }
}

void mostrar_n_libros_menor_puntaje(Libro libros_menor_puntaje[], int tope) {
    std::cout << "Los " << tope << " libros con menor puntaje son:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << libros_menor_puntaje[i].nombre << std::endl;
    }
}

void obtener_y_mostrar_n_libros_menor_puntaje(Libro *libros, int cantidad_libros, int n) {
    Libro libros_menor_puntaje[n];
    obtener_n_libros_menor_puntaje(libros, cantidad_libros, libros_menor_puntaje, n);
    mostrar_n_libros_menor_puntaje(libros_menor_puntaje, n);
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

void pedir_libro(Libro &libro) {
    std::cout << "Ingrese el nombre del libro que quiere agregar a la lista" << std::endl;
    std::cin.ignore();
    getline(std::cin, libro.nombre);
    do {
        std::cout << "Ingrese la inicial del genero del libro, debe ser una de las siguientes inciales:" << std::endl;
        for (int i = 0; i < MAX_GENEROS; i++) {
            std::cout << GENEROS_INICIALES[i] << " -> " << GENEROS[i] << std::endl;
        }
        std::cin >> libro.genero;
    } while (indice_genero_buscado(libro.genero) != NO_ENCONTRADO);
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
    indice = NO_ENCONTRADO;
    std::cout << "Ingrese el nombre del libro cuyo puntaje quiere modificar" << std::endl;
    std::cin.ignore();
    getline(std::cin, titulo);
    indice = indice_libro_buscado(libros, cantidad_libros, titulo);
    if (indice != NO_ENCONTRADO) {
        do {
            std::cout << "Ingrese el nuevo puntaje, entre " << MIN_PUNTAJE << "y " << MAX_PUNTAJE << std::endl;
            std::cin >> puntaje_nuevo;
        } while (puntaje_nuevo < MIN_PUNTAJE || puntaje_nuevo > MAX_PUNTAJE);
    } else
        std::cout << titulo << " no se encuentra en la lista de libros." << std::endl;
}

void pedir_y_editar_puntaje(Libro *&libros, int cantidad_libros, bool &hubo_cambios) {
    hubo_cambios = false;
    int indice_libro = 0;
    int puntaje_nuevo = 0;
    pedir_nuevo_puntaje(libros, cantidad_libros, puntaje_nuevo, indice_libro);
    if (indice_libro != NO_ENCONTRADO) {
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
        f_libros_escritura.close();
    } else {
        std::cout << "No hubieron cambios realizados. Cerrando el menu.";
    }
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
        std::cout << "Ingrese un numero, del " << MIN_ACCIONES << " al " << MAX_ACCIONES << " para utilizar el menu."
                  << std::endl;
        std::cin >> accion;
    } while (accion < MIN_ACCION || accion > MAX_ACCION);
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
            obtener_y_mostrar_n_libros_menor_puntaje(libros, cantidad_libros, CANTIDAD_LIBROS_MENOR_PUNTAJE);
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
            std::cout << "Error, el character ingresado no se encuentra en el rango de numeros entre" << MIN_ACCION
                      << " y " << MAX_ACCION << std::endl;
            volver_al_menu();
    }
}
