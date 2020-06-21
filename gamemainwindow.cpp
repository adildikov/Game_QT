#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"
#include "mainwindow.h"
#include <QPixmap>

GameMainWindow::GameMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMainWindow)
{
    ui->setupUi(this);
    QPixmap hero_img(":/resource/img/Hero.jpg");
    int w_hero = ui->HeroImage->width();
    int h_hero = ui->HeroImage->height();
    ui->HeroImage->setPixmap(hero_img.scaled(w_hero, h_hero));

    QPixmap money_img(":/resource/img/Coin.jpg");
    int w_money = 71;
    int h_money = 71;
    ui->MoneyImage->setPixmap(money_img.scaled(w_money, h_money));
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}


void GameMainWindow::on_quit_clicked()
{
    close();
}
