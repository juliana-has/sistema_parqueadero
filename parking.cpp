#include <iostream>

#define FILAS 16
#define COLS 16

struct Vehiculo {
    char placa[10];
    int horaEntrada;
    int ocupado;
    char tipo;
};

struct Historial {
    char placa[10];
    int entrada;
    int salida;
    int pago;
};

Vehiculo parqueadero[FILAS][COLS];
char mapa[FILAS][COLS];

Historial registros[200];
int totalRegistros = 0;

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

// RUTA VISUAL
void mostrarRuta(int fila, int col) {
    std::cout << "Ruta: EN -> ";
    for (int j = 1; j <= col; j++) {
        std::cout << ".. -> ";
    }
    std::cout << "[" << fila << "," << col << "]\n";
}

// MOSTRAR HISTORIAL
void mostrarHistorial() {
    if (totalRegistros == 0) {
        std::cout << "No hay historial\n";
        return;
    }

    std::cout << "\n--- HISTORIAL ---\n";

    for (int k = 0; k < totalRegistros; k++) {
        std::cout << registros[k].placa
                  << " | Entrada: " << registros[k].entrada
                  << " | Salida: " << registros[k].salida
                  << " | Pago: " << registros[k].pago << std::endl;
    }
}

// MOSTRAR MAPA
void mostrar_mapa(int horaActual) {

    if (horaActual < 0 || horaActual > 23) {
        std::cout << "Hora invalida\n";
        return;
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (mapa[i][j] == 'V') std::cout << "..";

            else if (mapa[i][j] == 'C' || mapa[i][j] == 'M') {
                if (parqueadero[i][j].ocupado)
                    std::cout << parqueadero[i][j].tipo << " ";
                else
                    std::cout << (mapa[i][j] == 'C' ? "c " : "m ");
            }

            else if (mapa[i][j] == 'E') std::cout << "EN";
            else if (mapa[i][j] == 'S') std::cout << "SA";
        }
        std::cout << std::endl;
    }

    std::cout << "\n--- LISTA ---\n";

    int total = 0;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {

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
                          << " | " << tiempo << "h\n";
            }
        }
    }

    if (total == 0)
        std::cout << "No hay vehiculos\n";
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

    return esLetra(placa[0]) && esLetra(placa[1]) && esLetra(placa[2]) &&
           esNumero(placa[3]) && esNumero(placa[4]) && esNumero(placa[5]);
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

// SALIDA
void salidaVehiculo(Vehiculo *v) {
    v->ocupado = 0;
    v->placa[0] = '\0';
}

// TARIFA INTELIGENTE
int calcularPago(int entrada, int salida, char tipo) {

    int tiempo;

    if (salida >= entrada)
        tiempo = salida - entrada;
    else
        tiempo = (24 - entrada) + salida;

    int tarifa;

    if (tipo == 'C') {
        if (entrada >= 18 && entrada <= 22)
            tarifa = 100;
        else
            tarifa = 80;
    } else {
        if (entrada >= 18 && entrada <= 22)
            tarifa = 90;
        else
            tarifa = 75;
    }

    return tiempo * 60 * tarifa;
}

// MAIN
int main() {

    int opcion, i, j, salida, pago;
    inicio();

    do {
        std::cout << "\n1. Ingresar\n2. Mostrar\n3. Retirar\n4. Historial\n5. Salir\n";
        std::cin >> opcion;

        if (opcion == 1) {
            Vehiculo temp;
            ingresarVehiculo(&temp);

            if (asignarEspacio(&i, &j, temp.tipo)) {
                parqueadero[i][j] = temp;
                std::cout << "Asignado [" << i << "," << j << "]\n";

                mostrarRuta(i, j); // 👈 ruta visual
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

                // GUARDAR HISTORIAL
                copiarArreglo(registros[totalRegistros].placa, parqueadero[i][j].placa);
                registros[totalRegistros].entrada = parqueadero[i][j].horaEntrada;
                registros[totalRegistros].salida = salida;
                registros[totalRegistros].pago = pago;
                totalRegistros++;

                salidaVehiculo(&parqueadero[i][j]);
            }
        }

        else if (opcion == 4) {
            mostrarHistorial();
        }

    } while (opcion != 5);

    return 0;
}
