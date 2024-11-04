#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    string matriz[5][9];
    int val=1;
    for(int fila=0; fila<5; fila++){
        for(int colum=0; colum<9; colum++){
            if(fila==3 && colum==3 || fila==3 && colum==5){
                matriz[fila][colum]="X";
            }
            else if(fila==4 && colum==5){
                matriz[fila][colum]="W";

            }
            else if(fila==4 && colum>5){
                matriz[fila][colum]="_";
            }
            else{
                matriz[fila][colum]="->";
            }
            printf("[%s]", matriz[fila][colum].c_str());
        }
        printf("\n");
    }
}
