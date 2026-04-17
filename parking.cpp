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

// DETECTAR TIPO

char detectarTipo(char placa[]) {
    int i = 0;

    while (placa[i] != '\0') {
        i++;
    }

    char ultimo = placa[i - 1];

    if (ultimo >= '0' && ultimo <= '9')
        return 'C';
    else
        return 'M';
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
// SALIDA


void SALEVehiculo(Vehiculo *v) {
    v->ocupado = 0;
    v->placa[0] = '\0';
}


// PAGO

int calcularPago(int entrada, int salida, char tipo) {
    int tiempo = salida - entrada; // en horas

    if (tipo == 'C')
        return tiempo * 60 * 80; // carro: 80 por minuto
    else
        return tiempo * 60 * 75; // moto: 75 por minuto
}




int main() {
    int opcion, i, j, salida, pago;

    inicio();

    do {
        std::cout << "\n1. Ingresar\n2. Mostrar\n3. Retirar\n4. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            mostrar_mapa();
        }

        else if (opcion == 2) {
            std::cout << "Fila Columna: ";
            std::cin >> i >> j;

            if (mapa[i][j] == 'L' && parqueadero[i][j].ocupado == 0) {
                ingresarVehiculo(&parqueadero[i][j]);
            } else {
                std::cout << "No disponible\n";
            }
        }

        else if (opcion == 3) {
            std::cout << "Fila Columna: ";
            std::cin >> i >> j;

            if (parqueadero[i][j].ocupado == 1) {
                std::cout << "Hora salida: ";
                std::cin >> salida;
               
       pago = calcularPago(
            parqueadero[i][j].horaEntrada,
            salida,
           parqueadero[i][j].tipo
       );

                SALEVehiculo(&parqueadero[i][j]);
            } else {
                std::cout << "No hay vehiculo\n";
            }
        }

    } while (opcion != 4);

    return 0;
}
