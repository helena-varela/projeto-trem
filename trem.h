#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <atomic>

enum TremID {
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    F = 6
};

extern QMutex mutex1;
extern QMutex mutex2;
extern QMutex mutex3;
extern QMutex mutex4;
extern QMutex mutex5;
extern QMutex mutex6;
extern QMutex mutex7;
extern QMutex mutex8;
extern QMutex mutex9;

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    void run();         //função a ser executada pela thread
    void setVelocidade(int novaVelocidade);//  para alterar a velocidade

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int xEsq, xDir, yTopo, yBase;

   std::atomic<int> velocidade;

   void verificarMutex(int px, int py);
};

#endif // TREM_H
