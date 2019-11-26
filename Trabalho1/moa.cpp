#include "astar.cpp"
#include <iostream>

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
    int tab_inicial[4][4] = {{5, 1, 2, 3}, {9,6,7,4}, {13,10,11,8}, {0,14,15,12}};
    node *inicio = new node(tab_inicial, 0, 0, 0, 0, nullptr, pos0[0], pos0[1]);
    int tab_final[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
    node *final = new node(tab_final, 0, 0, 0, 16, 0, 4, 4);
    vector<node> sucessores;
    geraSucessores(inicio, &sucessores);
    print_sucessores(sucessores);
    //astar(inicio, final, 1);

}