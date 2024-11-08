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
    int option = 0, optionDice = 0;
    int distancia=0;//variable original
    int *distan= &distancia;//puntero con respectiva dirección

    printf("[0] Exit \n");
    printf("[1] Start game \n");
    printf("Select the option please: ");
    scanf("%d", &option);
    if (option != 0) {
        SetConsoleTextAttribute(hConsole, 10);
        printf("Welcome to the Intergalactic Traveler's Guide \n");
        do {

            printf("[0] Exit \n");
            printf("[1] Roll the dice \n");
            printf("Select the option: ");
            scanf("%d", &optionDice);

            SetConsoleTextAttribute(hConsole, 3);
            int * dados = siguienteGalaxia();


            printf("Dice 1: %d \n",dados[0]);
            printf("Dice 2: %d \n",dados[1]);
            printf("Dice 3: %d \n\n",dados[2]);

            bool avanzar= cercanas(dados,distan);
            if(avanzar==true){
                printf("You can advance %d spaces\n", *distan);
            }
            else{
                printf("You can't advance \n");
            }

        }
        while (optionDice != 0);


    }
    else {
        printf("Goodbye \n");
    }
}

