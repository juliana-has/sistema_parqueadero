#include <iostream>

#define FILAS 16
#define COLS 16
#define MAX_HIST 100

struct Vehiculo {
    char placa[10];
    int horaEntrada;
    int ocupado;
    char tipo;
};

struct Registro {
    char placa[10];
    int pago;
};

Vehiculo parqueadero[FILAS][COLS];
char mapa[FILAS][COLS];

Registro historial[MAX_HIST];
int totalHist = 0;
int indiceHist = 0;

// COPIAR
void copiarArreglo(char d[], char o[]) {
    int i = 0;
    while(o[i] != '\0') {
        d[i] = o[i];
        i++;
    }
    d[i] = '\0';
}

// DETECTAR TIPO
char detectarTipo(char placa[]) {
    int i = 0;
    while (placa[i] != '\0') i++;
    return (placa[i-1] >= '0' && placa[i-1] <= '9') ? 'C' : 'M';
}

// INICIO
void inicio() {
    for (int i=0;i<FILAS;i++){
        for (int j=0;j<COLS;j++){
            parqueadero[i][j].ocupado=0;

            if(i==0||i==FILAS-1||j==0||j==COLS-1) mapa[i][j]='W';
            else if(i==1&&j==1) mapa[i][j]='E';
            else if(i==1&&j==COLS-2) mapa[i][j]='S';
            else if(j%3==0||i%2==0) mapa[i][j]='V';
            else mapa[i][j]=(i+j)%2==0?'C':'M';
        }
    }
}

// RUTA VISUAL
void mostrarRuta(int fi,int co){
    std::cout<<"\nRuta aproximada:\n";
    std::cout<<"ENTRADA -> ";

    for(int j=1;j<=co;j++) std::cout<<"→";
    for(int i=1;i<=fi;i++) std::cout<<"↓";

    std::cout<<" ["<<fi<<","<<co<<"]\n";
}

// MAPA 
void mostrar_mapa(int hora){
    std::cout<<"\n========= PARQUEADERO =========\n\n";

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLS;j++){

            if(mapa[i][j]=='W') std::cout<<"██";
            else if(mapa[i][j]=='V') std::cout<<"  ";
            else if(mapa[i][j]=='E') std::cout<<"EN";
            else if(mapa[i][j]=='S') std::cout<<"SA";

            else {
                if(parqueadero[i][j].ocupado)
                    std::cout<<parqueadero[i][j].tipo<<" ";
                else
                    std::cout<<(mapa[i][j]=='C'?"c ":"m ");
            }
        }
        std::cout<<"\n";
    }

    std::cout<<"\nLeyenda: c libre | m libre | C carro | M moto\n";
}

// VALIDACION
int placaValida(char p[]){
    if(p[0]<'A'||p[0]>'Z') return 0;
    if(p[1]<'A'||p[1]>'Z') return 0;
    if(p[2]<'A'||p[2]>'Z') return 0;
    if(p[3]<'0'||p[3]>'9') return 0;
    if(p[4]<'0'||p[4]>'9') return 0;
    if(p[5]<'0'||p[5]>'9') return 0;
    return 1;
}

// BUSCAR
int buscarVehiculo(char placa[], int *fi,int *co){
    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLS;j++){
            if(parqueadero[i][j].ocupado){
                int k=0,igual=1;
                while(placa[k]||parqueadero[i][j].placa[k]){
                    if(placa[k]!=parqueadero[i][j].placa[k]){
                        igual=0; break;
                    }
                    k++;
                }
                if(igual){*fi=i;*co=j;return 1;}
            }
        }
    }
    return 0;
}

// INGRESAR
void ingresarVehiculo(Vehiculo *v){
    char placa[10];
    int hora;

    do{
        std::cout<<"Placa (ABC123): ";
        std::cin>>placa;
    }while(!placaValida(placa));

    do{
        std::cout<<"Hora entrada: ";
        std::cin>>hora;
    }while(hora<0||hora>23);

    copiarArreglo(v->placa,placa);
    v->horaEntrada=hora;
    v->ocupado=1;
    v->tipo=detectarTipo(placa);
}

// ASIGNAR
int asignar(int *fi,int *co,char tipo){
    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLS;j++){
            if(!parqueadero[i][j].ocupado){
                if((tipo=='C'&&mapa[i][j]=='C')||(tipo=='M'&&mapa[i][j]=='M')){
                    *fi=i;*co=j; return 1;
                }
            }
        }
    }
    return 0;
}

// TARIFA
int calcularPago(int e,int s,char tipo){
    int t=(s>=e)?(s-e):(24-e+s);

    int tarifa=(tipo=='C')?80:75;

    if(t>5) tarifa-=10;

    return t*tarifa;
}

// HISTORIAL (CIRCULAR)
void guardarHist(char placa[], int pago) {

    copiarArreglo(historial[indiceHist].placa, placa);
    historial[indiceHist].pago = pago;

    indiceHist = (indiceHist + 1) % MAX_HIST;

    if (totalHist < MAX_HIST)
        totalHist++;
}

void mostrarHist() {
    std::cout << "\n====== HISTORIAL ======\n";

    int inicio = (totalHist == MAX_HIST) ? indiceHist : 0;

    for (int i = 0; i < totalHist; i++) {
        int pos = (inicio + i) % MAX_HIST;

        std::cout << historial[pos].placa
                  << " - $" << historial[pos].pago << "\n";
    }
}

// SALIDA
void salidaVehiculo(Vehiculo *v){
    v->ocupado=0;
}

// MAIN
int main(){

    int op,i,j,salida,pago;
    inicio();

    do{
        std::cout<<"\n=========== MENU ===========\n";
        std::cout<<"1. Ingresar\n";
        std::cout<<"2. Mostrar mapa\n";
        std::cout<<"3. Retirar\n";
        std::cout<<"4. Historial\n";
        std::cout<<"5. Salir\n";
        std::cout<<"Opcion: ";
        std::cin>>op;

        if(op==1){
            Vehiculo temp;
            ingresarVehiculo(&temp);

            if(asignar(&i,&j,temp.tipo)){
                parqueadero[i][j]=temp;
                std::cout<<"Asignado en ["<<i<<","<<j<<"]\n";
                mostrarRuta(i,j);
            }else{
                std::cout<<"Sin espacio\n";
            }
        }

        else if(op==2){
            int h;
            std::cout<<"Hora actual: ";
            std::cin>>h;
            mostrar_mapa(h);
        }

        else if(op==3){
            char placa[10];
            std::cout<<"Placa: ";
            std::cin>>placa;

            if(buscarVehiculo(placa,&i,&j)){
                std::cout<<"Hora salida: ";
                std::cin>>salida;

                // VALIDACION 
                if (salida < 0 || salida > 23) {
                    std::cout << "Hora invalida\n";
                    continue;
                }

                pago=calcularPago(
                    parqueadero[i][j].horaEntrada,
                    salida,
                    parqueadero[i][j].tipo
                );

                std::cout<<"Pago: $"<<pago<<"\n";

                guardarHist(placa,pago);
                salidaVehiculo(&parqueadero[i][j]);
            }
        }

        else if(op==4){
            mostrarHist();
        }

    }while(op!=5);

    return 0;
}
