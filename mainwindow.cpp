#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Criação dos trens com suas posições iniciais (ID, X, Y)
    trem1 = new Trem(1, 450, 40);// A
    trem2 = new Trem(2, 180, 250);//B
    trem3 = new Trem(3, 720, 250);//C
    trem4 = new Trem(4, 40, 380);// D
    trem5 = new Trem(5, 450, 460);//E
    trem6 = new Trem(6, 850, 380);//F

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
    case 1: ui->label_trem1->setGeometry(x, y, 20, 20); break;
    case 2: ui->label_trem2->setGeometry(x, y, 20, 20); break;
    case 3: ui->label_trem3->setGeometry(x, y, 20, 20); break;
    case 4: ui->label_trem4->setGeometry(x, y, 20, 20); break;
    case 5: ui->label_trem5->setGeometry(x, y, 20, 20); break;
    case 6: ui->label_trem6->setGeometry(x, y, 20, 20); break;
    default: break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
