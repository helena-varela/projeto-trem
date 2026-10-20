#include "trem.h"
#include <QtCore>

QMutex mutex1;
QMutex mutex2;
QMutex mutex3;
QMutex mutex4;
QMutex mutex5;
QMutex mutex6;
QMutex mutex7;
QMutex mutex8;
QMutex mutex9;

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

void Trem::setVelocidade(int novaVelocidade) {
    this->velocidade.store(novaVelocidade);
}

void Trem::run() {
    while(true) {
        int vel = velocidade.load();

        // se a velocidade for 0 o trem para
        if (vel == 0) {
          msleep(100);
          continue;
        }

        // verifica se precisa de bloquear mutexes para a posição atual
        verificarMutex(x, y);

        // movimentação anti horario
        // se está em cima e não chegou na esquerda, vai pra esquerda
        if (y == yTopo && x > xEsq)
            x -= 10;
        // se está na esquerda e não chegou na base, desce
        else if (x == xEsq && y < yBase)
            y += 10;
        // se está na base e não chegou na direita, vai para a direita
        else if (y == yBase && x < xDir)
            x += 10;
        // se está na direita e não chegou no topo, sobe
        else if (x == xDir && y > yTopo)
            y -= 10;

        emit updateGUI(ID, x, y);

        int tempoEspera = 202 - vel;
        msleep(tempoEspera);
    }
}

void Trem::verificarMutex(int px, int py) {
    switch(ID) {
        case A:
            // Vai atravessar as Regiões 1 e 2.
            // Pede as duas chaves juntas ANTES de descer para o trilho compartilhado
            if (px == 180 && py == 160) {
                mutex1.lock();
                mutex2.lock();
            }
            // Passou do cruzamento central (450 + 20 = 470), libera a Região 1
            if (px == 470 && py == 180) {
                mutex1.unlock();
            }
            // Subiu na direita, libera a Região 2
            if (px == 720 && py == 160) {
                mutex2.unlock();
            }
            break;

        case B:
            // Vai atravessar as Regiões 4, 5, 3 e 1 em sequência.
            // Pede todas em ordem crescente (1 -> 3 -> 4 -> 5) antes de entrar na Região 4
            if (px == 180 && py == 300) {
                mutex1.lock();
                mutex3.lock();
                mutex4.lock();
                mutex5.lock();
            }
            // Passou da quina com D (310 + 20 = 330), libera a Região 4
            if (px == 330 && py == 320) {
                mutex4.unlock();
            }
            // Subiu pela parede central e desocupou a base (320 - 20 = 300), libera a Região 5
            if (px == 450 && py == 300) {
                mutex5.unlock();
            }
            // Virou à esquerda no teto e desocupou a parede central (450 - 20 = 430), libera a Região 3
            if (px == 430 && py == 180) {
                mutex3.unlock();
            }
            // Desceu na parede esquerda e desocupou o teto (180 + 20 = 200), libera a Região 1
            if (px == 180 && py == 200) {
                mutex1.unlock();
            }
            break;

        case C:
            // Vai atravessar as Regiões 2, 3, 6 e 7 em sequência.
            // Pede todas em ordem crescente (2 -> 3 -> 6 -> 7) antes de entrar na Região 2
            if (px == 720 && py == 200) {
                mutex2.lock();
                mutex3.lock();
                mutex6.lock();
                mutex7.lock();
            }
            // Desceu pela parede central e desocupou o teto (180 + 20 = 200), libera a Região 2
            if (px == 450 && py == 200) {
                mutex2.unlock();
            }
            // Virou à direita na base e desocupou a parede central (450 + 20 = 470), libera a Região 3
            if (px == 470 && py == 320) {
                mutex3.unlock();
            }
            // Passou da quina com F (580 + 20 = 600), libera a Região 6
            if (px == 600 && py == 320) {
                mutex6.unlock();
            }
            // Subiu na parede direita e desocupou a base (320 - 20 = 300), libera a Região 7
            if (px == 720 && py == 300) {
                mutex7.unlock();
            }
            break;

        case D:
            // Vai atravessar as Regiões 8 e 4.
            // Pede em ordem crescente (4 -> 8) antes de entrar na parede da Região 8
            if (px == 290 && py == 460) {
                mutex4.lock();
                mutex8.lock();
            }
            // Virou à esquerda no teto e desocupou a parede (310 - 20 = 290), libera a Região 8
            if (px == 290 && py == 320) {
                mutex8.unlock();
            }
            // Passou da quina com B indo para a esquerda (180 - 20 = 160), libera a Região 4
            if (px == 160 && py == 320) {
                mutex4.unlock();
            }
            break;

        case E:
            // Vai atravessar as Regiões 9, 6, 5 e 8 em sequência.
            // Pede todas em ordem crescente (5 -> 6 -> 8 -> 9) antes de entrar na Região 9
            if (px == 560 && py == 460) {
                mutex5.lock();
                mutex6.lock();
                mutex8.lock();
                mutex9.lock();
            }
            // Virou à esquerda no teto e desocupou a parede direita (580 - 20 = 560), libera a Região 9
            if (px == 560 && py == 320) {
                mutex9.unlock();
            }
            // Passou do cruzamento central (450 - 20 = 430), libera a Região 6
            if (px == 430 && py == 320) {
                mutex6.unlock();
            }
            // Desceu pela parede esquerda e desocupou o teto (320 + 20 = 340), libera a Região 5
            if (px == 310 && py == 340) {
                mutex5.unlock();
            }
            // Virou à direita na base e desocupou a parede esquerda (310 + 20 = 330), libera a Região 8
            if (px == 330 && py == 460) {
                mutex8.unlock();
            }
            break;

        case F:
            // Vai atravessar as Regiões 7 e 9.
            // Pede em ordem crescente (7 -> 9) antes de entrar na Região 7
            if (px == 740 && py == 320) {
                mutex7.lock();
                mutex9.lock();
            }
            // Desceu pela parede esquerda e desocupou o teto (320 + 20 = 340), libera a Região 7
            if (px == 580 && py == 340) {
                mutex7.unlock();
            }
            // Virou à direita na base e desocupou a parede esquerda (580 + 20 = 600), libera a Região 9
            if (px == 600 && py == 460) {
                mutex9.unlock();
            }
            break;
    }
}