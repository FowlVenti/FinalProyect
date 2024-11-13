#include <cstdio>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void tablero(int filax, int comlumx) {//tablero visual
    string tablero[5][9];
    for(int fila=0; fila<5; fila++){//recorrer matriz
        for(int colum=0; colum<9; colum++){
            if(fila==3 && colum==3 || fila==3 && colum==5){//casillas trampa
                tablero[fila][colum]="XX";

            }
            else if(fila==4 && colum==5){//casilla gannar
                tablero[fila][colum]="WI";

            }
            else if(fila==4 && colum>5){//casillas sobrantes
                tablero[fila][colum]="  ";
            }
            else{//casillas normales
                tablero[fila][colum]="->";
            }
            if(fila==filax && colum==comlumx) {//ubicación jugador, if aparte por si cae en
                tablero[fila][colum]="VI";     //casilla especial pueda observarse el jugador
            }                                  //excepción de la 31, esa lo regresa a la 23
            printf("[%s]", tablero[fila][colum].c_str());
        }
        printf("\n");
    }
}

int casilla(int &fila, int &colum, int *distan, int &ubi, int &optionDice,int &aster) {//saber en que casilla esta
    ubi=0;
    colum += *distan;//saber en que columna esta
    if(colum>8) {//saber cuando hay cambio de fila para el tablero(coordenadas)
        fila+=1;//cambio de fila
        colum=colum-9;//dejando solo las casillas de la nueva fila
    }
    ubi=(fila*9)+colum+1;//numero de casilla
    if (ubi==31) {//regresar a la casilla 23
        printf("You fell into the asteroid belt (space 31) \n");
        printf("You return to the space 23 \n");
        ubi=23;
        colum=4;
        fila=2;
        aster=1;
    }
    else if (ubi==33) {//termiar juego por culpa del hoyo negro
        printf("You fell into the black hole (space 33) \n");
        printf("You die \n");
        optionDice = 0;//para que salga del juego


    }
    else if (ubi>=42) {//ganar
        printf("You win!!!!!!!!!!! \n");
        colum=5;
        fila=4;
        optionDice = 0;//para que salga del juego
        ubi=42;
    }
    return 0;
}


int* siguienteGalaxia(int &tiros) {//Detalle, el dado puede dar 0
    tiros++;//contar los tiros
    srand(time(nullptr));
    int* list = new int[3];
    list[0] = rand() % 10;
    list[1] = rand() % 10;
    list[2] = rand() % 10;
    return list;//los valores de los 3 dados se guardan en la lista
}

bool cercanas(int dados[], int *distan, int &galSumAct){//Retorna verdadero si la proxima galaxia es cercana
    int sum=0, sum1=0;
    bool avan=false;
    sum1=dados[0]+dados[1]+dados[2];//siguiente galxia
    sum=sum1-galSumAct;//distancia entre galaxias
    //sum=1; //por si se necesita pruebas sin aleatoriedad
    if (sum<0) {//por si es negativa la diferencia hacerla positiva
        sum*=-1;
    }
    if(sum>9){              //el valor más alto posible es 2, por lo que solo necesita de una
        sum=sum/10+sum%10;  //segunda verificación para reducir el termino a un digito
    }
    if(sum<=4){
        avan=true;//permite avanzar
        *distan=sum;//solo actualiza la distancia si la galaxia es cercana
        galSumAct=sum1;//Actualizar el valor de la galaxia en donde se esta
    }
    else{
        avan=false;//no avanzar
    }
    return avan;

}

int main() {
    int option=0; // Menu para repetir el juego y la otra checar que sea en caso
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                            //ganar o perder
    do {

        srand(time(nullptr));
        int colora = rand() % 15;
        int colord=rand()%15;//colores aleatorios
        int aster=0;//control de casilla 23
        int fila=0, colum=0, ubi=1, optionDice = 0,galAct[3],tiros=0,galSumAct=0, distancia=0;//variables
        int *distan= &distancia;//puntero con respectiva dirección
        galAct[0]=0;//Para poder tener el valor de la galaxia en donde se esta
        galAct[1]=0;
        galAct[2]=0;

        printf("[0] Exit \n");
        printf("[1] Start game \n");
        printf("Select the option please:");
        scanf("%d", &option);
        if (option != 0) {//jugar o no
            SetConsoleTextAttribute(hConsole, colora);//color
            printf("Welcome to the Intergalactic Traveler's Guide \n");
            do {
                if(tiros==0) {//primer tablero , se imprime al empezar para que el usuario lo vea
                    printf("\n");
                    tablero(fila,colum);
                    printf("You are in space 1 \t Galaxy: 000\n\n");
                }
                printf("[0] Exit \n");
                printf("[1] Roll the dice \n");
                printf("Select the option: ");
                scanf("%d", &optionDice);

                if(optionDice==1) {//tirar

                    int colorb = rand() % 15;//color
                    SetConsoleTextAttribute(hConsole, colorb);
                    int * dados = siguienteGalaxia(tiros);//funcion donde se tira los dados

                    printf("\n");
                    printf("Dice 1: %d \t",dados[0]);
                    printf("Dice 2: %d \t",dados[1]);
                    printf("Dice 3: %d \n",dados[2]);
                    printf("Next galaxy %d%d%d\n", dados[0], dados[1], dados[2]);

                    bool avanzar= cercanas(dados,distan,galSumAct);//verificar si se puede avazar

                    if(avanzar==true && distancia!=0){
                        galAct[0]=dados[0];//mantener la galaxia en la que se prevalece
                        galAct[1]=dados[1];//si es que no avanza después
                        galAct[2]=dados[2];
                        printf("Nearby galaxy, you can advance %d spaces\n", *distan);
                        casilla(fila,colum,distan,ubi,optionDice,aster);
                        if (aster==1) {//control casilla 23, solo cuando es llevado por el cinturon
                            galAct[0]=3;//Galaxia al regresar a la casilla 23 por el cinturon
                            galAct[1]=4;//de asteroides
                            galAct[2]=1;
                            aster=0;//reinicio variable
                        }
                        tablero(fila,colum);//mostrar tablero, solo si se avanza
                    }
                    else{
                        printf("Distant galaxy,you can't advance\n");
                    }
                    printf("You are in space %d\t", ubi);//ubicacion del usuario
                    printf("Galaxy:%d%d%d\n\n", galAct[0],galAct[1],galAct[2]);

                }
                else if(optionDice!=0 && optionDice!=1){//por si se ingresa una opción inválida
                    printf("\nGive me a valid option\n");
                }
                else {//si sale del juego
                    printf("Game over\n");
                }
            }
            while (optionDice != 0);
            printf("You rolled the dice %d times \n", tiros);//al fializar muestra la cantidad de tiros realizados


        }
        else {
            printf("Goodbye \n");
        }
        //esta aparte por cuestiones de visualización en pantalla
        if (option!=0){//se imprime solo si el usuario se sale, pierde o gana la partida anterior
            SetConsoleTextAttribute(hConsole, colord);
            printf("\n\n");
            printf("You wanna play again?\n");
        }
    }while(option!=0);
}