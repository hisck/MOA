//#include "astar.cpp"
#include <iostream>
#include "astar2.cpp"

int main(){
    printf("---INICIEI O PROGRAMA----");
    int pos0[2];
    //int tab_inicial[4][4];
    /*for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cin >> tab_inicial[i][j];
            if(tab_inicial[i][j] = 0){
                pos0[0] = i;
                pos0[1] = j;
            }
        }
    }*/
    //2 3 0 8 1 5 4 7 9  6 10 12 13 14 11  15
    int tab_inicial[4][4] = {{2, 3, 0, 8}, {1,5,4,7}, {9,6,10,12}, {13,14,11,15}};
    int posXY[2] = {0, 2};
    node *inicio = new node(tab_inicial, 0, 0, 0, nullptr, posXY);
    //test_constructor(*inicio);
    int tab_final[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
    int posXY_final[2] = {3 , 3};
    node *final = new node(tab_final, 0, 0, 0, nullptr, posXY_final);
    //test_constructor(*final);
    //vector<node> sucessores;
    //geraSucessores(inicio, &sucessores, 1);
    //print_sucessores(sucessores);
    int valor = aestrela(inicio, final, 1);
    printf("Valor = %d\n", valor);
}