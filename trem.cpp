#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;

    //aqui cada trem recebe as coordenadas dos cantos de seu retângulo pra que run() fique mais limpo
    switch(ID) {
        case A: xEsq = 180; xDir = 720; yTopo = 40;  yBase = 180; break;
        case B: xEsq = 180; xDir = 450; yTopo = 180; yBase = 320; break;
        case C: xEsq = 450; xDir = 720; yTopo = 180; yBase = 320; break;
        case D: xEsq = 40;  xDir = 310; yTopo = 320; yBase = 460; break;
        case E: xEsq = 310; xDir = 580; yTopo = 320; yBase = 460; break;
        case F: xEsq = 580; xDir = 850; yTopo = 320; yBase = 460; break;
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        //TOPO: Se está em cima e não chegou na esquerda, VAI PARA A ESQUERDA
        if (y == yTopo && x > xEsq)
            x -= 10;
        //ESQUERDA: Se está na esquerda e não chegou na base, DESCE
        else if (x == xEsq && y < yBase)
            y += 10;
        //BASE: Se está na base e não chegou na direita, VAI PARA A DIREITA
        else if (y == yBase && x < xDir)
            x += 10;
        //DIREITA: Se está na direita e não chegou no topo, SOBE
        else if (x == xDir && y > yTopo)
            y -= 10;

        emit updateGUI(ID, x, y);
        msleep(velocidade);
    }
}




