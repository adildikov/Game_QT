#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamemainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap building_img(":/resource/img/building.jpg");
    int w_bl = ui->BuildingImg->width();
    int h_bl = ui->BuildingImg->height();
    ui->BuildingImg->setPixmap(building_img.scaled(w_bl, h_bl));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_clicked()
{
    GameMainWindow game(this);
    game.exec();
}
