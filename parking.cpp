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
