#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    string matriz[5][9];
    int val=1;
    for(int fila=0; fila<5; fila++){
        for(int colum=0; colum<9; colum++){
            matriz[fila][colum]="A";
            //val++;
            printf("[%s]", matriz[fila][colum].c_str());
        }
        printf("\n");
    }
}
