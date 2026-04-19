#include <iostream>

#define FILAS 16
#define COLS 16

struct Vehiculo {
    char placa[10];
    int horaEntrada;
    int ocupado;
    char tipo; // C = carro, M = moto
};

Vehiculo parqueadero[FILAS][COLS];
char mapa[FILAS][COLS];

// COPIAR ARREGLO
void copiarArreglo(char destino[], char origen[]) {
    int i = 0;
    while(origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// DETECTAR TIPO
char detectarTipo(char placa[]) {
    int i = 0;
    while (placa[i] != '\0') i++;

    char ultimo = placa[i - 1];

    if (ultimo >= '0' && ultimo <= '9')
        return 'C';
    else
        return 'M';
}

// Estructura
void inicio() {
    int i, j;

    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {

            parqueadero[i][j].ocupado = 0;
            parqueadero[i][j].placa[0] = '\0';

            if (i == 0 || i == FILAS - 1 || j == 0 || j == COLS - 1)
                mapa[i][j] = 'W';
            else if (i == 1 && j == 1)
                mapa[i][j] = 'E';
            else if (i == 1 && j == COLS - 2)
                mapa[i][j] = 'S';
            else if (j % 3 == 0 || i % 2 == 0)
                mapa[i][j] = 'V';
            else
                mapa[i][j] = 'L';
        }
    }
}

// MOSTRAR MAPA 
void mostrar_mapa(int horaActual) {
    int i, j;

    // VALIDAR HORA
    if (horaActual < 0 || horaActual > 23) {
        std::cout << "Hora invalida\n";
        return;
    }

    // MAPA
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {

            if (mapa[i][j] == 'V') std::cout << "..";

            else if (mapa[i][j] == 'L') {
                if (parqueadero[i][j].ocupado == 1) {

                    if (parqueadero[i][j].tipo == 'C')
                        std::cout << "C ";
                    else
                        std::cout << "M ";

                } else {
                    std::cout << "[]";
                }
            }

            else if (mapa[i][j] == 'E') std::cout << "EN";
            else if (mapa[i][j] == 'S') std::cout << "SA";
        }
        std::cout << std::endl;
    }

    std::cout << "\n[] Libre  C Carro  M Moto\n";

    // LISTA
   // LISTA
std::cout << "\n--- LISTA DE VEHICULOS ---\n";

int hayVehiculos = 0;

for (i = 0; i < FILAS; i++) {
    for (j = 0; j < COLS; j++) {

        if (parqueadero[i][j].ocupado == 1) {

            hayVehiculos = 1;

            int entrada = parqueadero[i][j].horaEntrada;

            if (horaActual < entrada) {
                std::cout << "[" << i << "," << j << "]: "
                          << parqueadero[i][j].placa
                          << " | Tiempo: invalido\n";
            } else {
                int tiempo = horaActual - entrada;

                std::cout << "[" << i << "," << j << "]: "
                          << parqueadero[i][j].placa
                          << " | Tiempo: " << tiempo << " horas\n";
            }
        }
    }
}

// SI NO HAY VEHICULOS
if (!hayVehiculos) {
  std::cout << "No hay vehiculos en el parqueadero\n";
}
   
}

// validacion de placa
int longitud(char placa[]) {
    int i = 0;
    while (placa[i] != '\0') i++;
    return i;
}

int esLetra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int esNumero(char c) {
    return (c >= '0' && c <= '9');
}

int placaValida(char placa[]) {
    int i = 0;
    int tieneLetra = 0;
    int tieneNumero = 0;

    if (longitud(placa) != 6) return 0;

    while (placa[i] != '\0') {
        if (esLetra(placa[i])) tieneLetra = 1;
        else if (esNumero(placa[i])) tieneNumero = 1;
        else return 0;
        i++;
    }

    return tieneLetra && tieneNumero;
}

// placa duplicada
int buscarVehiculo(char placa[], int *fila, int *col) {
    int i, j, k, igual;

    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {

            if (parqueadero[i][j].ocupado == 1) {

                k = 0;
                igual = 1;

                while (placa[k] != '\0' && parqueadero[i][j].placa[k] != '\0') {
                    if (placa[k] != parqueadero[i][j].placa[k]) {
                        igual = 0;
                        break;
                    }
                    k++;
                }

                if (placa[k] != '\0' || parqueadero[i][j].placa[k] != '\0')
                    igual = 0;

                if (igual) {
                    *fila = i;
                    *col = j;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// INGRESAR
void ingresarVehiculo(Vehiculo *v) {
    char placa[10];
    int hora;
    int valida;

    do {
        std::cout << "Placa: ";
        std::cin >> placa;

        int fi, co;
        if (buscarVehiculo(placa, &fi, &co)) {
            std::cout << "Esa placa ya esta en el parqueadero\n";
            valida = 0;
            continue;
        }

        valida = placaValida(placa);

        if (!valida)
            std::cout << "Placa invalida\n";

    } while (!valida);

    do {
        std::cout << "Hora entrada (0-23): ";
        std::cin >> hora;

    } while (hora < 0 || hora > 23);

    copiarArreglo(v->placa, placa);
    v->horaEntrada = hora;
    v->ocupado = 1;
    v->tipo = detectarTipo(placa);
}

// ASIGNAR
int asignarEspacio(int *fila, int *col) {
    int i, j;

    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {

            if (mapa[i][j] == 'L' && parqueadero[i][j].ocupado == 0) {
                *fila = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

// CONTAR espacios
int contarDisponibles() {
    int i, j, libres = 0;

    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {
            if (mapa[i][j] == 'L' && parqueadero[i][j].ocupado == 0) {
                libres++;
            }
        }
    }
    return libres;
}

// SALIda de  VEHICULO
void salidaVehiculo(Vehiculo *v) {
    v->ocupado = 0;
    v->placa[0] = '\0';
}

// PAGO
int calcularPago(int entrada, int salida, char tipo) {
    int tiempo = salida - entrada;

    if (tipo == 'C')
        return tiempo * 60 * 80;
    else
        return tiempo * 60 * 75;
}

// MAIN
int main() {
    int opcion, i, j, salida, pago;

    inicio();

    do {
        std::cout << "\n1. Ingresar\n2. Mostrar\n3. Retirar\n4. Salir\n";
        std::cout << "Espacios libres: " << contarDisponibles() << std::endl;

        std::cin >> opcion;

        if (opcion == 1) {
            if (asignarEspacio(&i, &j)) {
                std::cout << "Espacio asignado en [" << i << "][" << j << "]\n";
                ingresarVehiculo(&parqueadero[i][j]);
            } else {
                std::cout << "Parqueadero lleno\n";
            }
        }

        else if (opcion == 2) {
            int horaActual;
            std::cout << "Hora actual: ";
            std::cin >> horaActual;

            mostrar_mapa(horaActual);
        }

        else if (opcion == 3) {
            char placaBuscar[10];

            std::cout << "Placa: ";
            std::cin >> placaBuscar;

            if (buscarVehiculo(placaBuscar, &i, &j)) {

                std::cout << "Vehiculo en [" << i << "][" << j << "]\n";
                std::cout << "Hora entrada: " << parqueadero[i][j].horaEntrada << std::endl;

                std::cout << "Hora salida: ";
                std::cin >> salida;

        if (salida < 0 || salida > 23 || salida < parqueadero[i][j].horaEntrada) {
            std::cout << "Hora invalida\n";
             continue;
}
                pago = calcularPago(
                    parqueadero[i][j].horaEntrada,
                    salida,
                    parqueadero[i][j].tipo
                );

                std::cout << "Pago: " << pago << std::endl;

                salidaVehiculo(&parqueadero[i][j]);

            } else {
                std::cout << "Vehiculo no encontrado\n";
            }
        }

    } while (opcion != 4);

    return 0;
}
