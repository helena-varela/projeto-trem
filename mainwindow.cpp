#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Criação dos trens com suas posições iniciais (ID, X, Y)
    trem1 = new Trem(A, 450, 40);
    trem2 = new Trem(B, 180, 250);
    trem3 = new Trem(C, 720, 250);
    trem4 = new Trem(D, 40, 380);
    trem5 = new Trem(E, 450, 460);
    trem6 = new Trem(F, 850, 380);

    // Conexão dos sinais updateGUI à interface
    connect(trem1, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem2, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem3, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem4, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem5, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem6, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));

    // Inicialização automática do movimento dos trens (Threads)
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

// Atualização da posição dos trens na tela
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
        case A: ui->label_trem1->setGeometry(x, y, 20, 20); break;
        case B: ui->label_trem2->setGeometry(x, y, 20, 20); break;
        case C: ui->label_trem3->setGeometry(x, y, 20, 20); break;
        case D: ui->label_trem4->setGeometry(x, y, 20, 20); break;
        case E: ui->label_trem5->setGeometry(x, y, 20, 20); break;
        case F: ui->label_trem6->setGeometry(x, y, 20, 20); break;
        default: break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
