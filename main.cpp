#include <cstdio>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <list>
using namespace std;

void tablero() {//tablero visual

    string tablero[5][9];
    for(int fila=0; fila<5; fila++){
        for(int colum=0; colum<9; colum++){
            if(fila==3 && colum==3 || fila==3 && colum==5){
                tablero[fila][colum]="XX";
            }
            else if(fila==4 && colum==5){
                tablero[fila][colum]="WI";

            }
            else if(fila==4 && colum>5){
                tablero[fila][colum]="  ";
            }
            else{
                tablero[fila][colum]="->";
            }
            printf("[%s]", tablero[fila][colum].c_str());
        }
        printf("\n");
    }
}

int casilla(int &fila, int &colum, int *distan, int &ubi) {//saber en que casilla esta
    ubi=0;
    colum=colum + *distan;//saber en que columna esta
    if(colum>8) {//saber cuando hay cambio de fila para el tablero(coordenadas)
        fila+=1;//cambio de fila
        colum=colum-9;//dejando solo las casillas de la nueva fila
    }
    ubi=(fila*9)+colum+1;//numero de casilla
    return 0;
}


int* siguienteGalaxia() {//CHECAR, NO DERIA DAR VALORES 0, LOS DADOS NO TIENEN CEROS
    srand(time(nullptr));
    int* list = new int[3];
    list[0] = rand() % 10;
    list[1] = rand() % 10;
    list[2] = rand() % 10;
    return list;
}

bool cercanas(int dados[], int *distan){//Retorna verdadero si la proxima galaxia es cercana
    int sum=0;
    sum=dados[0]+dados[1]+dados[2];
    bool avan=false;
    if(sum>9){              //el valor más alto posible es 2, por lo que solo necesita de una
        sum=sum/10+sum%10;  //segunda verificación para reducir el termino a un digito
    }
    if(sum<=4){
        avan=true;
        *distan=sum;        //solo actualiza la distancia si la galaxia es cercana
    }
    else{
        avan=false;
    }
    return avan;

}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int option = 0, fila=0, colum=-1, ubi=1, optionDice = 0,galAct[3], distancia=0;//variable original
    int *distan= &distancia;//puntero con respectiva dirección
    galAct[0]=0;
    galAct[1]=0;
    galAct[2]=0;

    printf("[0] Exit \n");
    printf("[1] Start game \n");
    printf("Select the option please:");
    scanf("%d", &option);
    if (option != 0) {
        SetConsoleTextAttribute(hConsole, 10);
        printf("Welcome to the Intergalactic Traveler's Guide \n");
        do {
            printf("[0] Exit \n");
            printf("[1] Roll the dice \n");
            printf("Select the option: ");
            scanf("%d", &optionDice);

            if(optionDice==1) {
                SetConsoleTextAttribute(hConsole, 3);
                int * dados = siguienteGalaxia();

                printf("\n");
                printf("Dice 1: %d \t",dados[0]);
                printf("Dice 2: %d \t",dados[1]);
                printf("Dice 3: %d \n",dados[2]);

                bool avanzar= cercanas(dados,distan);
                if(avanzar==true){
                    galAct[0]=dados[0];//mantener la galaxia en la que se prevalece
                    galAct[1]=dados[1];//si es que no avanza
                    galAct[2]=dados[2];
                    printf("Nearby galaxy, you can advance %d spaces\n", *distan);
                    casilla(fila,colum,distan,ubi);
                }
                else{
                    printf("Distant galaxy,you can't advance\n");
                }
                printf("You are in space %d\t", ubi);
                printf("Galaxy:%d%d%d\n\n", galAct[0],galAct[1],galAct[2]);

            }
            else if(optionDice!=0 && optionDice!=1){
                printf("Give me a valid option\n");
            }
            else {
                printf("Game over\n");
            }
        }
        while (optionDice != 0);


    }
    else {
        printf("Goodbye \n");
    }
}
