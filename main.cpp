#include <cstdio>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;



int main() {
    srand(time(nullptr));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int option = 0, optionDice = 0;

    printf("[0] Exit \n");
    printf("[1] Start game \n");
    printf("Select the option please: ");
    scanf("%d", &option);
    if (option != 0) {
        SetConsoleTextAttribute(hConsole, 10);
        printf("Welcome to the Intergalactic Traveler's Guide \n");
        do {
            const int dado1 = rand()%10, dado2 = rand()%10, dado3 = rand()%10;
            printf("[0] Exit \n");
            printf("[1] Roll the dice \n");
            printf("Select the option: ");

            SetConsoleTextAttribute(hConsole, 3);

            scanf("%d", &optionDice);
            printf("Dice 1: %d \n",dado1);
            printf("Dice 2: %d \n",dado2);
            printf("Dice 3: %d \n\n",dado3);

        }
        while (optionDice != 0);


    }
    else {
        printf("Goodbye \n");
    }





    SetConsoleTextAttribute(hConsole, 13);
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
