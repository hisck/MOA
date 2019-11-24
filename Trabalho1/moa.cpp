#include "astar.cpp"
#include <iostream>

int main(){
    int pos0[2];
    int tab_inicial[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cin >> tab_inicial[i][j];
            if(tab_inicial[i][j] = 0){
                pos0[0] = i;
                pos0[1] = j;
            }
        }
    }
    node *inicio = new node(tab_inicial, 0, 0, 0, 0, nullptr, pos0[0], pos0[1]);

}