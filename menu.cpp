
#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>

const int MAX_GENEROS = 6;
const char GENEROS_INICIALES[] = {'A', 'C', 'D', 'P', 'R', 'T'};
const std::string GENEROS[] = {"Aventura", "Ciencia ficcion", "Didactica", "Policiaca", "Romance", "Terror"};

const int NO_ENCONTRADO = -1;
const int MAX_PUNTAJE = 100;
const int MIN_PUNTAJE = 0;

const int MIN_ACCIONES = 1;
const int MAX_ACCIONES = 8;
const int LISTAR_LIBROS = 1;
const int MOSTRAR_LIBRO_FAVORITO = 2;
const int MOSTRAR_GENERO_MAS_LEIDO = 3;
const int MOSTRAR_GENERO_FAVORITO = 4;
const int MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE = 5;
const int AGREGAR_LIBRO = 6;
const int EDITAR_PUNTAJE = 7;
const int GUARDAR_Y_SALIR = 8;
const int CANTIDAD_LIBROS_MENOR_PUNTAJE = 3;

struct Genero {
    char genero{};
    int puntaje_total{};
    int cantidad_libros{};
};

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Devuelve la posicion de letra en el vector GENEROS_INICIALES.
 * Si letra no se encuentra en el vector, devuelve NO_ENCONTRADO.
 */
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

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Devuelve la palabra completa de la inicial del genero recibida como parametro.
 * Si la genero_letra no es una inicial dentro del rango, devuelve error.
 */
std::string genero_palabra(char genero_letra) {
    int indice = indice_genero_buscado(genero_letra);
    if (indice != NO_ENCONTRADO)
        return GENEROS[indice];
    return "Error, inicial no reconocida como genero posible";
}

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * La funcion le pregunta al usuario si quiere repetir la accion.
 * Devuelve true si siguiente_accion es "y" o "Y".
 */
bool se_debe_repetir_accion() {
    std::string siguiente_accion;
    std::cout << "Desea repetir accion? presione:" << std::endl << "Y -> Repetir accion" << std::endl
              << "'Cualquier otro character' -> Volver al menu" << std::endl;
    std::cin >> siguiente_accion;
    return siguiente_accion == "Y" || siguiente_accion == "y";
}

/*Precondiciones:
 * Cantidad_libros debe estar inicializado
 */
/*Postcondiciones:
 * Imprime por pantalla todos los libros del vector dinamico *libros.
 */
void listar_libros(Libro *libros, int cantidad_libros) {
    std::cout << "Listando los libros:" << std::endl;
    for (int i = 0; i < cantidad_libros; i++) {
        std::string genero_str = genero_palabra(libros[i].genero);
        std::cout << i + 1 << ") " << libros[i].nombre << ", " << libros[i].puntaje << " puntos";
        std::cout << ", de genero " << genero_str << std::endl;
    }
}

/*Precondiciones:
 * cantidad_libros y el vector dinamico *libros deben estar inicializados.
 */
/*Postcondiciones:
 * Calcula y carga los nombres de los libros favoritos en libros_favoritos[].
 * Es un libro favoritos si su puntaje es >= al puntaje del resto de los libros.
 */
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

/*Precondiciones:
 * libros_favoritos y tope deben estar inicializado.
 */
/*Postcondiciones:
 * Imprime por pantalla todos los nombres de los libros favoritos y el puntaje de estos.
 */
void mostrar_libros_favoritos(std::string libros_favoritos[], int tope, int puntaje_mayor) {

    std::cout << "Lista de libros favoritos:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << libros_favoritos[i] << std::endl;
    }
    std::cout << "El puntaje mayor es " << puntaje_mayor << std::endl;
}

/*Precondiciones:
 * cantidad_libros, el vector dinamico *libros y libros_favoritos deben estar inicializados.
 */
/*Postcondiciones:
 * Calcula y carga los nombres de los libros favoritos en libros_favoritos[].
 * Es un libro favoritos si su puntaje es >= al puntaje del resto de los libros.
 * Imprime por pantalla todos los nombres de los libros favoritos y el puntaje de estos.
 */
void obtener_y_mostrar_libros_favoritos(Libro *libros, int cantidad_libros) {
    std::string libros_favoritos[cantidad_libros];
    int tope = 0;
    int puntaje_mayor = 0;
    obtener_libros_favoritos(libros, cantidad_libros, libros_favoritos, tope, puntaje_mayor);
    mostrar_libros_favoritos(libros_favoritos, tope, puntaje_mayor);
}

/*Precondiciones:
 * generos[], genero_buscado y puntaje_obtenido deben estar inicializados.
 */
/*Postcondiciones:
 * Suma 1 a la cantidad del genero del vector generos[] que coincide con genero_buscado.
 * Le suma puntaje_obtenido a puntaje_total del genero del vector generos[] que coincide con genero_buscado.
 */
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

/*Precondiciones:
 * cantidad_libros y el vector dinamico *libros deben estar inicializados.
 */
/*Postcondiciones:
 * Inicializa ceros en los campos cantidad_libros y puntaje_total de todos los generos de generos[]
 * Inicializa la inicial GENEROS_INICIALES[i] en generos[i].genero, tal que i pertenece a los numeros naturales con el cero menores que MAX_GENEROS.
 */
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

/*Precondiciones:
 * generos[] debe estar inicializado.
 */
/*Postcondiciones:
 * Cargara en generos_mas_leidos[] los generos mas repetidos del archivo de libros
 */
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

/*Precondiciones:
 * tope y generos_mas_leidos[] deben estar inicializados.
 */
/*Postcondiciones:
 * Imprime por pantalla los generos mas repetidos.
 */
void mostrar_generos_mas_leidos(std::string generos_mas_leidos[], int tope) {
    std::cout << "Los generos mas leidos son:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << generos_mas_leidos[i] << std::endl;
    }
}

/*Precondiciones:
 * cantidad_libros y *libros debem estar inicializados
 */
/*Postcondiciones:
 * Calcula los generos mas repetidos del archivo de libros
 * Imprime por pantalla los generos mas repetidos.
 */
void obtener_y_mostrar_generos_mas_leidos(Libro *libros, int cantidad_libros) {
    Genero generos[MAX_GENEROS];
    std::string generos_mas_leidos[MAX_GENEROS];
    int tope = 0;
    inicializar_generos(generos, libros, cantidad_libros);
    obtener_generos_mas_leidos(generos_mas_leidos, generos, tope);
    mostrar_generos_mas_leidos(generos_mas_leidos, tope);
}

/*Precondiciones:
 * generos[] debe estar inicializado.
 */
/*Postcondiciones:
 * Carga en generos_favoritos todos los generos de mayor promedio de puntaje.
 */
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

/*Precondiciones:
 * generos_favoritos[] y tope deben estar inicializados.
 */
/*Postcondiciones:
 * Imprime por pantalla todos los generos favoritos.
 */
void mostrar_generos_favoritos(std::string generos_favoritos[], int tope) {
    std::cout << "Los generos favoritos son:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << generos_favoritos[i] << std::endl;
    }
}

/*Precondiciones:
 * *libros y cantidad_libros deben estar inicializados.
 */
/*Postcondiciones:
 * Calcula todos los generos de mayor promedio de puntaje.
 * Imprime por pantalla todos los generos favoritos.
 */
void obtener_y_mostrar_generos_favoritos(Libro *libros, int cantidad_libros) {
    Genero generos[MAX_GENEROS];
    std::string generos_favoritos[MAX_GENEROS];
    int tope = 0;
    inicializar_generos(generos, libros, cantidad_libros);
    obtener_generos_favoritos(generos_favoritos, generos, tope);
    mostrar_generos_favoritos(generos_favoritos, tope);
}

/*Precondiciones:
 * libro_viejo y libro_nuevo deben estar inicializados.
 */
/*Postcondiciones:
 * Devuelve true si libro_nuevo es menor a libro_viejo, un libro es menor que otro si se cumple una de las siguientes condiciones:
 *      -Su puntaje es estrictamente menor que el otro.
 *      -Su puntaje es igual que el otro y su nombre es menor alfabeticamente.
 */
bool nuevo_libro_es_menor(const Libro &libro_viejo, const Libro &libro_nuevo) {
    return (libro_nuevo.puntaje < libro_viejo.puntaje) ||
           (libro_nuevo.nombre < libro_viejo.nombre && libro_nuevo.puntaje == libro_viejo.puntaje);
}

/*Precondiciones:
 * tope, indice y *libros_menor_puntaje deben estar inicializados.
 */
/*Postcondiciones:
 * desplaza todos los elementos desde el indice recibido por parametro, hacia la derecha del vector, hasta el tope del vector.
 */
void modificar_libros_menor_puntaje(Libro *libros_menor_puntaje, int tope, int indice) {
    for (int i = tope - 1; i > indice; i--) {
        libros_menor_puntaje[i] = libros_menor_puntaje[i - 1];
    }
}

/*Precondiciones:
 * libros_menor_puntaje[], tope, libro e indice deben estar inicializados.
 */
/*Postcondiciones:
 * Si libro es menor a uno de los libros de libros_menor_puntaje[], actualiza libros_menor_puntaje[] con el nuevo libro.
 */
void actualizar_libro_menos_favorito(Libro libros_menor_puntaje[], int tope, Libro &libro, int indice) {
    if (nuevo_libro_es_menor(libros_menor_puntaje[indice], libro)) {
        modificar_libros_menor_puntaje(libros_menor_puntaje, tope, indice);
        libros_menor_puntaje[indice] = libro;
    } else if (libros_menor_puntaje[indice].nombre != libro.nombre) {
        modificar_libros_menor_puntaje(libros_menor_puntaje, tope, indice);
        libros_menor_puntaje[indice + 1] = libro;
    }
}

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Intercambia los valores de libro_a con libro_b.
 */
void intercambiar_libros(Libro &libro_a, Libro &libro_b) {
    Libro libro_aux = libro_a;
    libro_a = libro_b;
    libro_b = libro_aux;
}

/*Precondiciones:
 * tope debe estar inicializado
 */
/*Postcondiciones:
 * Ordena libros_menor_puntaje[] de menor puntaje a mayor. Si el puntaje es el mismo, lo ordena alfabeticamente ascendente.
 */
void ordenar_libros_menor_puntaje(Libro libros_menor_puntaje[], int tope) {
    for (int i = 0; i < tope; i++) {
        for (int j = 0; j < tope - 1; j++) {
            if (nuevo_libro_es_menor(libros_menor_puntaje[j], libros_menor_puntaje[j + 1])) {
                intercambiar_libros(libros_menor_puntaje[j], libros_menor_puntaje[j + 1]);
            }
        }
    }
}

/*Precondiciones:
 * tope_libros_menor_puntaje y cantidad_libros debe estar inicializado
 */
/*Postcondiciones:
 * Calcula los n libros de menor puntaje y los carga en libros_menor_puntaje[], n es tope_libros_menor_puntaje.
 */
void obtener_n_libros_menor_puntaje(Libro *libros, int cantidad_libros, Libro libros_menor_puntaje[],
                                    int tope_libros_menor_puntaje) {
    for (int i = 0; i < tope_libros_menor_puntaje; i++) {
        libros_menor_puntaje[i] = libros[i];
    }
    ordenar_libros_menor_puntaje(libros_menor_puntaje, tope_libros_menor_puntaje);
    for (int i = tope_libros_menor_puntaje; i < cantidad_libros; i++) {
        for (int j = 0; j < tope_libros_menor_puntaje; j++) {
            if (libros[i].puntaje <= libros_menor_puntaje[j].puntaje) {
                actualizar_libro_menos_favorito(libros_menor_puntaje, tope_libros_menor_puntaje, libros[i], j);
                j = tope_libros_menor_puntaje;
            }
        }
    }
}

/*Precondiciones:
 * libros_menor_puntaje[] y tope deben estar inicializados.
 */
/*Postcondiciones:
 * Imprime por pantalla todos los libros de menor puntaje.
 */
void mostrar_n_libros_menor_puntaje(Libro libros_menor_puntaje[], int tope) {
    std::cout << "Los " << tope << " libros con menor puntaje son:" << std::endl;
    for (int i = 0; i < tope; i++) {
        std::cout << libros_menor_puntaje[i].nombre << std::endl;
    }
}

/*Precondiciones:
 * cantidad_libros y n deben estar inicializados.
 */
/*Postcondiciones:
 * Calcula los n libros de menor puntaje y los imprime por pantalla.
 */
void obtener_y_mostrar_n_libros_menor_puntaje(Libro *libros, int cantidad_libros, int n) {
    Libro libros_menor_puntaje[n];
    obtener_n_libros_menor_puntaje(libros, cantidad_libros, libros_menor_puntaje, n);
    mostrar_n_libros_menor_puntaje(libros_menor_puntaje, n);
}

/*Precondiciones:
 * cantidad_libros y titulo_buscado debe estar inicializado.
 */
/*Postcondiciones:
 * Busca y devuelve la posicion del titulo buscado en el vector de libros.
 * Si no se encuentra un libro con titulo_buscado, devuelve NO_ENCONTRADO.
 */
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

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Pide al usuario y carga el titulo.
 */
void pedir_titulo_libro(std::string &titulo) {
    std::cout << "Ingrese el nombre del libro" << std::endl;
    std::cin.ignore();
    getline(std::cin, titulo);
}

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Imprime por pantalla las iniciales de los generos y la palabra completa del genero al que pertenecen.
 */
void mostrar_generos() {
    for (int i = 0; i < MAX_GENEROS; i++) {
        std::cout << GENEROS_INICIALES[i] << " -> " << GENEROS[i] << std::endl;
    }
}

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Pide al usuario y carga el genero hasta que este se encuentre dentro del rango valido.
 * Es valido si pertenece a GENEROS_INICIALES[i], para i un numero natural y el cero que sea <= MAX_GENEROS.
 */
void pedir_genero_libro(char &genero) {
    std::cout << "Ingrese la inicial del genero del libro, debe ser una de las siguientes inciales:" << std::endl;
    mostrar_generos();
    std::cin >> genero;
    while (indice_genero_buscado(genero) == NO_ENCONTRADO) {
        std::cout << genero << " no se encuentra dentro de las opciones posibles." << std::endl
                  << "Ingrese nuevamente la inicial del genero, debe ser una de las siguientes iniciales:" << std::endl;
        mostrar_generos();
        std::cin >> genero;
    }
}

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Devuelve true si puntaje se encuentra dentro del rango valido, o false si no.
 * Es valido si puntaje es mayor o igual que MIN_PUNTAJE y puntaje es menor o igual que MAX_PUNTAJE.
 */
bool puntaje_esta_dentro_de_rango(int puntaje) {
    return puntaje >= MIN_PUNTAJE && puntaje <= MAX_PUNTAJE;
}

/*Precondiciones:
 * El usuario no debe ingresar una letra cuando se le pide ingresar un numero para puntaje.
 */
/*Postcondiciones:
 * Pide al usuario y carga el puntaje hasta que este se encuentre dentro del rango valido.
 * Es valido si es mayor o igual que MIN_PUNTAJE y menor o igual que MAX_PUNTAJE.
 */
void pedir_puntaje_libro(int &puntaje) {
    std::cout << "Ingrese el puntaje del libro entre " << MIN_PUNTAJE << " y " << MAX_PUNTAJE << std::endl;
    std::cin >> puntaje;
    while (!puntaje_esta_dentro_de_rango(puntaje)) {
        std::cout << puntaje << " no se encuentra dentro del rango valido. " << std::endl
                  << "Ingrese nuevamente el puntaje entre" << MIN_PUNTAJE << " y " << MAX_PUNTAJE << std::endl;
        std::cin >> puntaje;
    }
    puntaje = puntaje;
}

/*Precondiciones:
 * El usuario no debe ingresar una letra cuando se le pide ingresar un numero para puntaje.
 */
/*Postcondiciones:
 * Pide al usuario y carga el titulo.
 * Pide al usuario y carga el genero hasta que este se encuentre dentro del rango valido.
 * Es valido si pertenece a GENEROS_INICIALES[i], para i un numero natural y el cero que sea <= MAX_GENEROS.
 * Pide al usuario y carga el puntaje hasta que este se encuentre dentro del rango valido.
 * Es valido si es mayor o igual que MIN_PUNTAJE y menor o igual que MAX_PUNTAJE.
 *
 */
void pedir_libro_a_agregar(Libro &libro) {
    pedir_titulo_libro(libro.nombre);
    pedir_genero_libro(libro.genero);
    pedir_puntaje_libro(libro.puntaje);
}

/*Precondiciones:
 * tamanio_libros y cantidad_libros deben estar inicializados.
 */
/*Postcondiciones:
 * Agrega un nuevo libro al vector *libros.
 */
void agregar_libro(Libro *&libros, int &tamanio_libros, int &cantidad_libros, const Libro &libro_nuevo) {
    if (tamanio_libros == cantidad_libros)
        aumentar_tamanio_libros(tamanio_libros, libros);
    libros[cantidad_libros] = libro_nuevo;
    cantidad_libros++;
}

/*Precondiciones:
 * tamanio_libros y cantidad_libros deben estar inicializados.
 */
/*Postcondiciones:
 * Pide al usuario los datos de un libro y lo agrega al vector.
 * Si el libro ya se encuentra en el vector, no lo agrega.
 */
void pedir_y_agregar_libro(Libro *&libros, int &tamanio_libros, int &cantidad_libros, bool &hubo_cambios) {
    hubo_cambios = false;
    Libro libro_nuevo;
    pedir_libro_a_agregar(libro_nuevo);
    if (indice_libro_buscado(libros, cantidad_libros, libro_nuevo.nombre) == NO_ENCONTRADO) {
        agregar_libro(libros, tamanio_libros, cantidad_libros, libro_nuevo);
        hubo_cambios = true;
        std::cout << "Se agrego el libro correctamente." << std::endl;
    } else
        std::cout << "Ya existe este libro en la lista." << std::endl;
}

/*Precondiciones:
 * tamanio_libros y cantidad_libros deben estar inicializados.
 */
/*Postcondiciones:
 * Pide al usuario los datos de un libro y lo agrega al vector mientras que el usuario quiera seguir agregando libros.
 * Si el libro ya se encuentra en el vector, no lo agrega.
 */
void accion_agregar_libro(Libro *&libros, int &tamanio_libros, int &cantidad_libros, bool &hubo_cambios) {
    do {
        pedir_y_agregar_libro(libros, tamanio_libros, cantidad_libros, hubo_cambios);
    } while (se_debe_repetir_accion());
}

/*Precondiciones:
 * cantidad_libros debe estar inicializado.
 */
/*Postcondiciones:
 * Pide al usuario el nombre del libro cuyo puntaje desea modificar.
 * Si el libro se encuentra el vector de libros, pide al usuario el puntaje nuevo.
 */
void pedir_libro_a_modificar_puntaje(Libro *libros, int cantidad_libros, int &puntaje_nuevo, int &indice) {
    std::string titulo = " ";
    indice = NO_ENCONTRADO;
    pedir_titulo_libro(titulo);
    indice = indice_libro_buscado(libros, cantidad_libros, titulo);
    if (indice != NO_ENCONTRADO) {
        pedir_puntaje_libro(puntaje_nuevo);
    } else
        std::cout << titulo << " no se encuentra en la lista de libros." << std::endl;
}

/*Precondiciones:
 * cantidad_libros debe estar inicializado.
 */
/*Postcondiciones:
 * Pide al usuario el nombre del libro cuyo puntaje desea modificar.
 * Si el libro se encuentra el vector de libros, pide al usuario el puntaje nuevo y edita el puntaje del libro.
 */
void pedir_y_editar_puntaje(Libro *&libros, int cantidad_libros, bool &hubo_cambios) {
    hubo_cambios = false;
    int indice_libro = NO_ENCONTRADO;
    int puntaje_nuevo = 0;
    pedir_libro_a_modificar_puntaje(libros, cantidad_libros, puntaje_nuevo, indice_libro);
    if (indice_libro != NO_ENCONTRADO) {
        libros[indice_libro].puntaje = puntaje_nuevo;
        hubo_cambios = true;
    }
}

/*Precondiciones:
 * cantidad_libros debe estar inicializado.
 */
/*Postcondiciones:
 * Pide al usuario el nombre del libro cuyo puntaje desea modificar.
 * Si el libro se encuentra el vector de libros, pide al usuario el puntaje nuevo y edita el puntaje del libro.
 * Repite la accion mientras que el usuario quiera modificar el puntaje de un libro.
 */
void accion_editar_puntaje(Libro *&libros, int cantidad_libros, bool &hubo_cambios) {
    do {
        pedir_y_editar_puntaje(libros, cantidad_libros, hubo_cambios);
    } while (se_debe_repetir_accion());
}

/*Precondiciones:
 * cantidad_libros debe estar inicializado.
 */
/*Postcondiciones:
 * Si hubo_cambios es igual a true, escribe en un el archivo de nombre &nombre_archivo todos los libros del vector libros.
 * Iguala estado_menu a cero.
 */
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

/*Precondiciones:
 * -
 */
/*Postcondiciones:
 * Imprime por pantalla el interfaz del menu.
 */
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

/*Precondiciones:
 * El usuario debe ingresar un numero cuando se le pide ingresar una accion para utilizar el menu.
 */
/*Postcondiciones:
 * Pide al usuario la accion hasta que esta se encuentre dentro del rango valido.
 * Es valido si accion es mayor o igual que MIN_ACCION y menor o igual que MAX_ACCION.
 */
void pedir_accion(int &accion) {
    std::cout << "Ingrese un numero, del " << MIN_ACCIONES << " al " << MAX_ACCIONES << " para utilizar el menu."
              << std::endl;
    std::cin >> accion;
    while (accion < MIN_ACCIONES || accion > MAX_ACCIONES) {
        std::cout << accion << " no se encuentra dentro del rango valido" << std::endl;
        std::cout << "Ingrese un numero, del " << MIN_ACCIONES << " al " << MAX_ACCIONES << " para utilizar el menu."
                  << std::endl;
        std::cin >> accion;
    }
}

/*Precondiciones:
 * accion, cantidad_libros y tamanio_libros deben estar inicializados.
 */
/*Postcondiciones:
 * El procedimiento se encarga de realizar la accion del menu.
 */
void
realizar_accion(int &accion, Libro *&libros, int &cantidad_libros, int &tamanio_libros,
                const std::string &nombre_archivo,
                int &estado_menu, bool &hubo_cambios) {
    switch (accion) {
        case LISTAR_LIBROS:
            listar_libros(libros, cantidad_libros);
            break;
        case MOSTRAR_LIBRO_FAVORITO:
            obtener_y_mostrar_libros_favoritos(libros, cantidad_libros);
            break;
        case MOSTRAR_GENERO_MAS_LEIDO:
            obtener_y_mostrar_generos_mas_leidos(libros, cantidad_libros);
            break;
        case MOSTRAR_GENERO_FAVORITO:
            obtener_y_mostrar_generos_favoritos(libros, cantidad_libros);
            break;
        case MOSTRAR_TRES_LIBROS_MENOR_PUNTAJE:
            obtener_y_mostrar_n_libros_menor_puntaje(libros, cantidad_libros, CANTIDAD_LIBROS_MENOR_PUNTAJE);
            break;
        case AGREGAR_LIBRO:
            accion_agregar_libro(libros, tamanio_libros, cantidad_libros, hubo_cambios);
            break;
        case EDITAR_PUNTAJE:
            accion_editar_puntaje(libros, cantidad_libros, hubo_cambios);
            break;
        case GUARDAR_Y_SALIR:
            guardar_y_salir(hubo_cambios, nombre_archivo, libros, cantidad_libros, estado_menu);
            break;
        default:
            std::cout << "Error, el character ingresado no se encuentra en el rango de numeros entre" << MIN_ACCIONES
                      << " y " << MAX_ACCIONES << std::endl << "Ingrese un character para volver al menu" << std::endl;
            std::string aux;
            std::cin >> aux;
    }
}
