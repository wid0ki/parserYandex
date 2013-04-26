#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/logo.png"));
    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/logo.png"));
    w.show();
    return a.exec();
}
