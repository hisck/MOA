#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
//#define TAM 4
#define xmaisum 1
#define xmenosum 2
#define ymaisum 3
#define ymenosum 4

using namespace std;

/*lass Tabuleiro{
    public:
        int matriz[4][4];
        int nullposition[2];

    Tabuleiro::Tabuleiro(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; i<4; i++){
                cin >> matriz[i][j];
                if(matriz[i][j] == 0){
                    nullposition[0] = i;
                    nullposition[1] = j;
                }
            }
        }
    }

    Tabuleiro::Tabuleiro(int posX, int posY, int table[4][4], node* father){
        nullposition[0] = posX; 
        nullposition[1] = posY;
        Tabuleiro::matriz = father->tabuleiro;
    }
};*/

class node{
    public:
        int tabuleiro[4][4];
        int g;
        int h;
        int f;
        int numerocorretas;
        node *father;
        int posX;
        int posY;

    node geraSucessores(node *pai, vector <node> *sucessores){
        //new node(pai->tabuleiro, (pai->g + 1), 0, 0, pai->numerocorretas, pai);
        //Gera sucessor deve pegar e calcular os valores de G e H para todos os possíveis sucessores. Dessa forma, ele escolhe uma das possibilidades
        //Se estivermos nos extremos, temos dois sucessores
        //Se estivermos numa linha extrema, sem ser nos extremos, temos 3 sucessores
        //caso contrário, teremos 4 sucessores
        //sucessores são guardados em um vector.
        int posX = pai->posX;
        int posY = pai->posY;

        if(posX == 0){
            switch(posY){
                case 0:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    break;
                case 1:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 2:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 3:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
            }
        }else if(posX == 1){
            switch(posY){
                case 0:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 1:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    node *d = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 2:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    node *d = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    break;
                case 3:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
            }                
        }else if(posX == 2){
            switch(posY){
                case 0:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
                case 1:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    node *d = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    break;
                case 2:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    node *d = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    break;
                case 3:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
            }           
        }else{
            switch(posY){
                case 0:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    break;
                case 1:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x - 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
                case 2:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x - 1
                    node *c = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
                case 3:
                    node *a = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    node *b = new node(pai->tabuleiro, (pai->g + 1), calculate_heristica1(pai->tabuleiro), ((pai->g + 1) + calculate_heristica1(pai->tabuleiro)), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    break;
            }
        }
    }

    node::node(int matriz[4][4], int g, int h, int f, int numerocorretas, node* father, int posX, int posY){
        node::tabuleiro[4][4] = matriz[4][4];
        node::g = g;
        node::h = h;
        node::f = f;
        node::numerocorretas = numerocorretas;
        node::father = father;
        node::posX = posX;
        node::posY = posY;
    }

    node::node(int matriz[4][4], int g, int h, int f, int numerocorretas, node* father, int posX, int posY, int decisao){
        node::tabuleiro[4][4] = matriz[4][4];
        node::g = g;
        node::h = h;
        node::f = f;
        node::numerocorretas = numerocorretas;
        node::father = father;
        node::posX = posX;
        node::posY = posY;
        int zero = 0;
        int modifica = 0;
        switch(decisao){
            case xmaisum:
                zero = matriz[posX - 1][posY];
                modifica = matriz[posX][posY];
                matriz[posX][posY] = zero;
                matriz[posX - 1][posY] = modifica;
                break;
            case xmenosum:
                zero = matriz[posX + 1][posY];
                modifica = matriz[posX][posY];
                matriz[posX][posY] = zero;
                matriz[posX + 1][posY] = modifica;
                break;
            case ymaisum:
                zero = matriz[posX][posY - 1];
                modifica = matriz[posX][posY];
                matriz[posX][posY] = zero;
                matriz[posX][posY - 1] = modifica;
                break;
            case ymenosum:
                zero = matriz[posX][posY + 1];
                modifica = matriz[posX][posY];
                matriz[posX][posY] = zero;
                matriz[posX][posY + 1] = modifica;
                break;
        }
    }
/*    int geraTabuleiro(){
        int table[4][4];
        int num;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                cin >> num;
                table[i][j] = num;
            }
        }
        return table[4][4];
    }*/

    int calculate_heristica1(int table[4][4]){
        int valor = 0;
        for(int i = 0; i< 4; i++){
            for(int j = 0; j < 4; j++){
                if (table[i][j] != ((1 * i) + j + 1)){
                    valor++;
                }
            }
        }
        return valor;
    }

    int calculate_heristica2(int table[4][4]){
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

    int Teste_Sucessor(node *sucessor){
        if (sucessor->h == 0){
            return 1;
        }else{
            return 0;
        }
    }
};

int astar(int tabuleiro[4][4], int start, int end){

}