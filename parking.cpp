#include <iostream>

#define FILAS 16
#define COLS 16

struct Vehiculo {
    char placa[10];
    int horaEntrada;
    int ocupado;
    char tipo;
};

Vehiculo parqueadero[FILAS][COLS];
char mapa[FILAS][COLS];

// COPIAR
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
    return (ultimo >= '0' && ultimo <= '9') ? 'C' : 'M';
}

// INICIALIZAR
void inicio() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

            parqueadero[i][j].ocupado = 0;
            parqueadero[i][j].placa[0] = '\0';

            if (i == 0 || i == FILAS-1 || j == 0 || j == COLS-1)
                mapa[i][j] = 'W';
            else if (i == 1 && j == 1)
                mapa[i][j] = 'E';
            else if (i == 1 && j == COLS-2)
                mapa[i][j] = 'S';
            else if (j % 3 == 0 || i % 2 == 0)
                mapa[i][j] = 'V';
            else
                mapa[i][j] = ((i + j) % 2 == 0) ? 'C' : 'M';
        }
    }
}

// MOSTRAR MAPA
void mostrar_mapa(int horaActual) {

    if (horaActual < 0 || horaActual > 23) {
        std::cout << "Hora invalida\n";
        return;
    }

    // MAPA
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (mapa[i][j] == 'V') std::cout << "..";

            else if (mapa[i][j] == 'C' || mapa[i][j] == 'M') {
                if (parqueadero[i][j].ocupado) {
                    std::cout << parqueadero[i][j].tipo << " ";
                } else {
                    std::cout << (mapa[i][j] == 'C' ? "c " : "m ");
                }
            }

            else if (mapa[i][j] == 'E') std::cout << "EN";
            else if (mapa[i][j] == 'S') std::cout << "SA";
        }
        std::cout << std::endl;
    }

    std::cout << "\n--- LISTA ---\n";

    int total = 0, carros = 0, motos = 0, totalEspacios = 0;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (mapa[i][j] == 'C' || mapa[i][j] == 'M')
                totalEspacios++;

            if (parqueadero[i][j].ocupado) {

                total++;

                int entrada = parqueadero[i][j].horaEntrada;
                int tiempo;

                if (horaActual >= entrada)
                    tiempo = horaActual - entrada;
                else
                    tiempo = (24 - entrada) + horaActual;

                std::cout << "[" << i << "," << j << "] "
                          << parqueadero[i][j].placa
                          << " | " << (parqueadero[i][j].tipo == 'C' ? "Carro" : "Moto")
                          << " | " << tiempo << "h\n";

                if (parqueadero[i][j].tipo == 'C') carros++;
                else motos++;
            }
        }
    }

    if (total == 0)
        std::cout << "No hay vehiculos\n";
    else {
        std::cout << "\nTotal: " << total << std::endl;
        std::cout << "Carros: " << carros << " | Motos: " << motos << std::endl;

        if (totalEspacios > 0)
            std::cout << "Ocupacion: " << (total * 100) / totalEspacios << "%\n";
    }
}

// VALIDACIONES
int longitud(char placa[]) {
    int i = 0;
    while (placa[i] != '\0') i++;
    return i;
}

int esLetra(char c) {
    return (c >= 'A' && c <= 'Z');
}

int esNumero(char c) {
    return (c >= '0' && c <= '9');
}

int placaValida(char placa[]) {
    if (longitud(placa) != 6) return 0;

    if (!(esLetra(placa[0]) && esLetra(placa[1]) && esLetra(placa[2])))
        return 0;

    if (!(esNumero(placa[3]) && esNumero(placa[4]) && esNumero(placa[5])))
        return 0;

    return 1;
}

// BUSCAR
int buscarVehiculo(char placa[], int *fila, int *col) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (parqueadero[i][j].ocupado) {

                int k = 0, igual = 1;

                while (placa[k] && parqueadero[i][j].placa[k]) {
                    if (placa[k] != parqueadero[i][j].placa[k]) {
                        igual = 0;
                        break;
                    }
                    k++;
                }

                if (placa[k] != parqueadero[i][j].placa[k])
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

    do {
        std::cout << "Placa: ";
        std::cin >> placa;
    } while (!placaValida(placa));

    do {
        std::cout << "Hora: ";
        std::cin >> hora;
    } while (hora < 0 || hora > 23);

    copiarArreglo(v->placa, placa);
    v->horaEntrada = hora;
    v->ocupado = 1;
    v->tipo = detectarTipo(placa);
}

// ASIGNAR
int asignarEspacio(int *fila, int *col, char tipoVehiculo) {

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (!parqueadero[i][j].ocupado) {
                if ((tipoVehiculo == 'C' && mapa[i][j] == 'C') ||
                    (tipoVehiculo == 'M' && mapa[i][j] == 'M')) {

                    *fila = i;
                    *col = j;
                    return 1;
                }
            }
        }
    }

    // moto usa carro
    if (tipoVehiculo == 'M') {
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLS; j++) {

                if (!parqueadero[i][j].ocupado && mapa[i][j] == 'C') {
                    *fila = i;
                    *col = j;
                    return 1;
                }
            }
        }
    }

    return 0;
}

// PAGO
int calcularPago(int entrada, int salida, char tipo) {
    int tiempo = (salida >= entrada) ? (salida - entrada)
                                    : (24 - entrada + salida);

    return (tipo == 'C') ? tiempo * 80 : tiempo * 75;
}

// MAIN
int main() {

    int opcion, i, j, salida, pago;
    inicio();

    do {
        std::cout << "\n1. Ingresar\n2. Mostrar\n3. Retirar\n4. Salir\n";
        std::cin >> opcion;

        if (opcion == 1) {
            Vehiculo temp;
            ingresarVehiculo(&temp);

            if (asignarEspacio(&i, &j, temp.tipo)) {
                parqueadero[i][j] = temp;
                std::cout << "Asignado [" << i << "," << j << "]\n";
            }
        }

        else if (opcion == 2) {
            int hora;
            std::cout << "Hora actual: ";
            std::cin >> hora;
            mostrar_mapa(hora);
        }

        else if (opcion == 3) {
            char placa[10];
            std::cout << "Placa: ";
            std::cin >> placa;

            if (buscarVehiculo(placa, &i, &j)) {
                std::cout << "Hora salida: ";
                std::cin >> salida;

                if (salida < 0 || salida > 23) {
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
            }
        }

    } while (opcion != 4);

    return 0;
}
