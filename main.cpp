#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("StartMenu");
    w.setWindowIcon(QIcon(":/resource/img/Boss3.jpg"));
    w.show();
    return a.exec();
}
