#include <iostream>

#define FILAS 16
#define COLS 16

struct Vehiculo {
    char placa[10];
    int horaEntrada;
    int ocupado;
Vehiculo parqueadero[FILAS][COLS];
char mapa[FILAS][COLS];

// Arreglo

void copiarArreglo(char destino[], char origen[]) {
    int i = 0;

    while(origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }

    destino[i] = '\0';
}

// inicio

void inicio() {
    int i, j;

    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {
            parqueadero[i][j].ocupado = 0;
            parqueadero[i][j].placa[0] = '\0';

            if (i == 0 && j == 0)
                mapa[i][j] = 'E';
            else if (i == FILAS - 1 && j == COLS - 1)
                mapa[i][j] = 'S';
            else if (i % 2 == 0)
                mapa[i][j] = 'V';
            else
                mapa[i][j] = 'L';
        }
    }
}

// MOSTRAR MAPA

void mostrar_mapa() {
    int i, j;

    std::cout << "\nPARQUEADERO\n\n";

    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {

            if (mapa[i][j] == 'V') std::cout << "..";
            else if (mapa[i][j] == 'L') {
                if (parqueadero[i][j].ocupado == 1)
                    std::cout << "XX";
                else
                    std::cout << "[]";
            }
            else if (mapa[i][j] == 'E') std::cout << "EN";
            else if (mapa[i][j] == 'S') std::cout << "SA";
        }
        std::cout << std::endl;
    }

    std::cout << "\n[] Libre  XX Ocupado\n\n";
}

// entra vehiculo

void ingresarVehiculo(Vehiculo *v) {
    char placa[10];
    int hora;

    std::cout << "Placa: ";
    std::cin >> placa;

    std::cout << "Hora entrada: ";
    std::cin >> hora;

    copiarCadena(v->placa, placa);
    v->horaEntrada = hora;
    v->ocupado = 1;
}
