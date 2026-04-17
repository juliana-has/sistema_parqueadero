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
