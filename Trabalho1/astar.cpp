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

    node(int matriz[4][4], int g, int h, int f, int numerocorretas, node* father, int posX, int posY){
        for (int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                node::tabuleiro[i][j] = matriz[i][j];
            }
        }
        node::g = g;
        node::h = h;
        node::f = f;
        node::numerocorretas = numerocorretas;
        node::father = father;
        node::posX = posX;
        node::posY = posY;
    }

    node(int matriz[4][4], int g, int h, int f, int numerocorretas, node* father, int posX, int posY, int decisao){
        for (int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                node::tabuleiro[i][j] = matriz[i][j];
            }
        }
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
                zero = node::tabuleiro[posX - 1][posY];
                modifica = node::tabuleiro[posX][posY];
                node::tabuleiro[posX][posY] = zero;
                node::tabuleiro[posX - 1][posY] = modifica;
                break;
            case xmenosum:
                zero = node::tabuleiro[posX + 1][posY];
                modifica = node::tabuleiro[posX][posY];
                node::tabuleiro[posX][posY] = zero;
                node::tabuleiro[posX + 1][posY] = modifica;
                break;
            case ymaisum:
                zero = node::tabuleiro[posX][posY - 1];
                modifica = node::tabuleiro[posX][posY];
                node::tabuleiro[posX][posY] = zero;
                node::tabuleiro[posX][posY - 1] = modifica;
                break;
            case ymenosum:
                zero = node::tabuleiro[posX][posY + 1];
                modifica = node::tabuleiro[posX][posY];
                node::tabuleiro[posX][posY] = zero;
                node::tabuleiro[posX][posY + 1] = modifica;
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

};

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
    printf("NUM_CORRETAS = %d\n", test.numerocorretas);
    printf("X = %d\n", test.posX);
    printf("Y = %d\n", test.posY);
}

int calculate_heuristica1(int table[4][4]){
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

int calculate_heuristica2(int table[4][4]){
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
    switch(choice){
        case 1:
            value = calculate_heuristica1(table);
            break;
        case 2:
            value = calculate_heuristica2(table);
            break;
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
        printf("NUM_CORRETAS = %d\n", sucessores[i].numerocorretas);
        printf("X = %d\n", sucessores[i].posX);
        printf("Y = %d\n", sucessores[i].posY);
    }
}

int geraSucessores(node *pai, vector <node> *sucessores){
        //new node(pai->tabuleiro, (pai->g + 1), 0, 0, pai->numerocorretas, pai);
        //Gera sucessor deve pegar e calcular os valores de G e H para todos os possíveis sucessores. Dessa forma, ele escolhe uma das possibilidades
        //Se estivermos nos extremos, temos dois sucessores
        //Se estivermos numa linha extrema, sem ser nos extremos, temos 3 sucessores
        //caso contrário, teremos 4 sucessores
        //sucessores são guardados em um vector.
        int posX = pai->posX;
        int posY = pai->posY;
        node *a, *b, *c, *d;
        if(posX == 0){
            switch(posY){
                case 0:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    break;
                case 1:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 2:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 3:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
            }
        }else if(posX == 1){
            switch(posY){
                case 0:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 1:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    d = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
                case 2:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    d = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    break;
                case 3:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    //deve ir em alguma estrutura para guardar sucessores
                    break;
            }                
        }else if(posX == 2){
            switch(posY){
                case 0:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
                case 1:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    d = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    break;
                case 2:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x + 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    d = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    sucessores->push_back(*d);
                    break;
                case 3:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX + 1), pai->posY, xmaisum);//x+1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
            }           
        }else if (posX == 3){
            switch(posY){
                case 0:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y+1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1 
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    break;
                case 1:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x - 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
                case 2:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY + 1), ymaisum);//y + 1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x - 1
                    c = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y - 1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    sucessores->push_back(*c);
                    break;
                case 3:
                    a = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, pai->posX, (pai->posY - 1), ymenosum);//y-1
                    b = new node(pai->tabuleiro, (pai->g + 1), 0, ((pai->g + 1) + 0), pai->numerocorretas, pai, (pai->posX - 1), pai->posY, xmenosum);//x-1
                    //deve ir em alguma estrutura para guardar sucessores
                    sucessores->push_back(*a);
                    sucessores->push_back(*b);
                    break;
            }
        }
        return 0;
    }

int compare_tabuleiros(node A, node B){
    int value = 0;
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            if(A.tabuleiro[i][j] == B.tabuleiro[i][j]){
                value++;
            }
        }
    }
    return value;
}

int astar(node *start, node *end, int heuristica){
    vector<node> lista_aberta;
    vector<node> lista_fechada;
    vector<node> sucessores;
    start->g = 0;
    start->father = nullptr;
    lista_aberta.push_back(*start);
    node *min = new node(nullptr, 0, 0, 0, 0, nullptr, 0, 0);
    int pos;
    while(lista_aberta.size() > 0){
        *min = lista_aberta[0];
        for(int i = 0; i < lista_aberta.size() ; i++){
            if (min->f > lista_aberta[i].f){
                *min = lista_aberta[i];
                pos = i;
            }
        }
        if(compare_tabuleiros(lista_aberta[pos], *end) == 16){
            break;
        }
        lista_aberta.erase(lista_aberta.begin()+pos);
        lista_fechada.push_back(*min);
        geraSucessores(min, &sucessores);
        if(lista_aberta.size() != 0){
            for(int i = 0; i < lista_aberta.size() ; i++){
                for(int j = 0; j < sucessores.size(); j++){
                    int is_equal = compare_tabuleiros(lista_aberta[i], sucessores[j]);
                    if(is_equal == 16){
                        if(sucessores[j].g < lista_aberta[i].g){
                            lista_aberta.erase(lista_aberta.begin()+i);
                        }
                    }
                }
            }
        }
        for(int i = 0; i < sucessores.size() ; i++){
            sucessores[i].h = calculate_heuristica(sucessores[i].tabuleiro, heuristica);
            sucessores[i].f = sucessores[i].g + sucessores[i].h;
            lista_aberta.push_back(sucessores[i]);
        }
    }
    return min->g ;
}
