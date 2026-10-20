#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInterface(int, int, int);

public slots:
    // sliders individuais
    void on_slider_a_valueChanged(int value);
    void on_slider_b_valueChanged(int value);
    void on_slider_c_valueChanged(int value);
    void on_slider_d_valueChanged(int value);
    void on_slider_e_valueChanged(int value);
    void on_slider_f_valueChanged(int value);

    // para o slider mestre
    void on_slider_m_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    // Declaração dos 6 trens (a, b, c, d, e, f)
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
    Trem *trem6;
};

#endif // MAINWINDOW_H