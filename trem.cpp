#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1: // Trem 1
            // 1. TOPO: Se está em cima e não chegou na esquerda, VAI PARA A ESQUERDA
            if (y == 30 && x > 60)
                x -= 10;
            // 2. ESQUERDA: Se está na esquerda e não chegou na base, DESCE
            else if (x == 60 && y < 150)
                y += 10;
            // 3. BASE: Se está em baixo e não chegou na direita, VAI PARA A DIREITA
            else if (y == 150 && x < 330)
                x += 10;
            // 4. DIREITA: Se está na direita e não chegou no topo, SOBE
            else if (x == 330 && y > 30)
                y -= 10;
            break;
        }
        emit updateGUI(ID, x, y);
        msleep(velocidade);
    }
}




