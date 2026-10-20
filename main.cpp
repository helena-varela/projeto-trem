#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_STYLE_OVERRIDE", "Fusion");
    qputenv("QT_QPA_PLATFORMTHEME", "generic");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
