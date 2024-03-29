#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define cima 0
#define baixo 1
#define esquerda 2
#define direita 3

using namespace std;

int calculate_heuristica1(int table[4][4], int final[4][4]){
        int valor = 0;
        for(int i = 0; i< 4; i++){
            for(int j = 0; j < 4; j++){
                if (table[i][j] != final[i][j]){
                    valor++;
                }
            }
        }
        return valor;
}

int calculate_heuristica2(int table[4][4], int final[4][4]){
        int valor = 0;
        int valor_pos_anterior = table[0][0];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(table[i][j] < valor_pos_anterior || table[i][j] > (valor_pos_anterior + 1)){
                    valor++;
                }valor_pos_anterior = table[i][j];
            }
        }
        return valor;
}

int calculate_heuristica(int table[4][4], int choice){
    int value = 0;
    int final[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0}};
    switch(choice){
        case 1:
            value = calculate_heuristica1(table, final);
            break;
        case 2:
            value = calculate_heuristica2(table, final);
            break;
    }
    return value;
}

class node{
    public:
        int tabuleiro[4][4];
        int g;
        int h;
        int f;
        node *father;
        int posXY[2];

    node(int tabuleiro[4][4], int g, int h, int f, node *father, int posXY[2]){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                node::tabuleiro[i][j] = tabuleiro[i][j];
            }
        }
        node::g = g; node::h = h; node::f = f; node::father = father;
        node::posXY[0] = posXY[0]; node::posXY[1] = posXY[1];
    }
    node(int table[4][4], int g, int h, int f, node *father, int posXY[2], int action, int heuristica){
        int posx = posXY[0]; int posy = posXY[1];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                node::tabuleiro[i][j] = table[i][j];
            }
        }
        node::g = g;
        node::father = father;
        int c;
        switch(action){
            case cima:
                c = table[posx - 1][posy];
                node::tabuleiro[posx - 1][posy] = 0;
                node::tabuleiro[posx][posy] = c;
                node::posXY[0] = posx - 1;
                node::posXY[1] = posy;
                break;
            case baixo:
                c = table[posx + 1][posy];
                node::tabuleiro[posx + 1][posy] = 0;
                node::tabuleiro[posx][posy] = c;
                node::posXY[0] = posx + 1;
                node::posXY[1] = posy;
                break;
            case esquerda:
                c = table[posx][posy - 1];
                node::tabuleiro[posx][posy - 1] = 0;
                node::tabuleiro[posx][posy] = c;
                node::posXY[1] = posy - 1;
                node::posXY[0] = posx;
                break;
            case direita:
                c = table[posx][posy + 1];
                node::tabuleiro[posx][posy + 1] = 0;
                node::tabuleiro[posx][posy] = c;
                node::posXY[1] = posy + 1;
                node::posXY[0] = posx;
                break;
        }
        node::h = calculate_heuristica(this->tabuleiro, heuristica); node::f = this->g + this->h; 
    }
};

int geraSucessores(node *father, vector<node> *sucessores, int heuristica){
    int posX = father->posXY[0];
    int posY = father->posXY[1];
    node *dir, *esq, *sobe, *desce;
    vector <bool> vaientrar;
    if (posX > 0 && posX < 3){
        node *sobe = new node(father->tabuleiro, (father->g + 1), 0 , 0, father, father->posXY, cima, heuristica);
        node *desce = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, baixo, heuristica);
        sucessores->push_back(*sobe);
        sucessores->push_back(*desce);
    }else if (posX == 0){
        node *desce = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, baixo, heuristica);
        sucessores->push_back(*desce);
    }else if (posX == 3){
        node *sobe = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, cima, heuristica);
        sucessores->push_back(*sobe);
    }
    if (posY > 0 && posY < 3){
        node *dir = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, direita, heuristica);
        node *esq = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, esquerda, heuristica);
        sucessores->push_back(*dir);
        sucessores->push_back(*esq);
    }else if (posY == 0){
        node *dir = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, direita, heuristica);
        sucessores->push_back(*dir);
    }else if (posY == 3){
        node *esq = new node(father->tabuleiro, (father->g + 1), 0, 0, father, father->posXY, esquerda, heuristica);
        sucessores->push_back(*esq);
    }
    return 0;
}

int compare_tabuleiros(node A, node B){
    int value = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(A.tabuleiro[i][j] == B.tabuleiro[i][j]){
                value++;
            }
        }
    }
    return value;
}

void print_sucessores(vector <node> sucessores){
    int tam = sucessores.size();
    printf("\nNUM SUCESSORES = %d", tam);
    printf("\n-------TABULEIRO------\n");
    for(int i = 0; i < tam ; i++){
        for(int j = 0; j < 4; j++){
            printf("|");
            for(int k = 0; k < 4; k++){
                printf(" %d ", sucessores[i].tabuleiro[j][k]);
            }printf("|\n");
        }
        printf("G = %d\n", sucessores[i].g);
        printf("H = %d\n", sucessores[i].h);
        printf("F = %d\n", sucessores[i].f);
        printf("X = %d\n", sucessores[i].posXY[0]);
        printf("Y = %d\n", sucessores[i].posXY[1]);
    }
}

void test_constructor(node test){
    printf("-------TABULEIRO------\n");
    for(int i = 0; i < 4; i++){
        printf("|");
        for(int j = 0; j< 4; j++){
            printf(" %d ", test.tabuleiro[i][j]);
        }
        printf("|\n");
    }
    printf("G = %d\n", test.g);
    printf("H = %d\n", test.h);
    printf("F = %d\n", test.f);
    printf("X = %d\n", test.posXY[0]);
    printf("Y = %d\n", test.posXY[1]);
}

int aestrela(node *start, node *end, int heuristica){
    vector<node>lista_aberta;
    vector<node>lista_fechada;
    vector<node>sucessores;
    start->g = 0;
    start->father = nullptr;
    lista_aberta.push_back(*start);
    node v = *start;
    while(compare_tabuleiros(v, *end) < 16){
        int pos;
        for(int i = 0; i < lista_aberta.size(); i++){
            if(lista_aberta[i].f < v.f) { 
                v = lista_aberta[i];
                pos = i;
            }
        }lista_fechada.erase(lista_fechada.begin() + pos);
        lista_fechada.push_back(v);
        geraSucessores(&v, &sucessores, heuristica);
        for(int i = 0; i < lista_aberta.size(); i++){
            for(int j = 0; j < sucessores.size(); j++){
                if(compare_tabuleiros(sucessores[j], lista_aberta[i]) == 16){
                    if(sucessores[j].g < lista_aberta[i].g){
                        lista_aberta.erase(lista_aberta.begin() + i);
                    }
                }
            }
        }
        for(int i = 0; i < lista_fechada.size(); i++){
            for(int j = 0; j <sucessores.size(); j++){
                if(compare_tabuleiros(sucessores[j], lista_fechada[i]) < 16){
                    sucessores[j].h = calculate_heuristica(sucessores[j].tabuleiro, heuristica);
                    sucessores[j].f = sucessores[j].h + sucessores[j].g;
                    lista_aberta.push_back(sucessores[j]);
                }
            }
        }
        sucessores.clear();
    }
    return v.g;
}