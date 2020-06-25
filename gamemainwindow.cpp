#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"
#include "mainwindow.h"
#include "shopwindow.h"
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

    _game = new Game();
    enterRoom(0);
    connect(_game->_hero, SIGNAL(hero_moved(int)), this, SLOT(enterRoom(int)));
    show_inventory(_game->_hero->_inventory);
    show_money(_game->_hero->getMoney());
    show_rage(_game->_hero->getRage());
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}


void GameMainWindow::on_quit_clicked()
{
    close();
}


void GameMainWindow::enterRoom(int room){
    Room newRoom = _game->_maze->_rooms[room];
    ui->LocationName->setText(newRoom._name);
    ui->LocationDescription->setText(newRoom._description);
    ui->BossDescription->setText(newRoom._bossdescription);
    if (newRoom._neighbourRooms[Direction::Room1] != -1){
        ui->Room1->setText(_game->_maze->_rooms[newRoom._neighbourRooms[Direction::Room1]]._name);
        ui->Room1->show();
    }else{
        ui->Room1->setText("");
        ui->Room1->hide();
    }

    if (newRoom._neighbourRooms[Direction::Room2] != -1){
        ui->Room2->setText(_game->_maze->_rooms[newRoom._neighbourRooms[Direction::Room2]]._name);
        ui->Room2->show();
    }else{
        ui->Room2->setText("");
        ui->Room2->hide();
    }

    if (newRoom._neighbourRooms[Direction::Room3] != -1){
        ui->Room3->setText(_game->_maze->_rooms[newRoom._neighbourRooms[Direction::Room3]]._name);
        ui->Room3->show();
    }else{
        ui->Room3->setText("");
        ui->Room3->hide();
    }

    if (newRoom._neighbourRooms[Direction::Room4] != -1){
        ui->Room4->setText(_game->_maze->_rooms[newRoom._neighbourRooms[Direction::Room4]]._name);
        ui->Room4->show();
    }else{
        ui->Room4->setText("");
        ui->Room4->hide();
    }

    if(newRoom._shop){
        ui->Shop->show();
    }else{
        ui->Shop->hide();
    }
}



void GameMainWindow::on_Room1_clicked()
{
    _game->_hero->move(Direction::Room1);
}

void GameMainWindow::on_Room2_clicked()
{
    _game->_hero->move(Direction::Room2);
}

void GameMainWindow::on_Room3_clicked()
{
    _game->_hero->move(Direction::Room3);
}

void GameMainWindow::on_Room4_clicked()
{
    _game->_hero->move(Direction::Room4);
}

void GameMainWindow::show_inventory(QList<std::shared_ptr<Item> > items)
{
    ui->InventoryList->clear();
    for (int i = 0; i < items.size(); i++){
        ui->InventoryList->addItem(items[i]->getName());
    }
}

void GameMainWindow::show_money(int money)
{
    ui->MoneyAmount->setText(QVariant(money).toString());
}

void GameMainWindow::show_rage(int rage)
{
    ui->Rage_status->setValue(rage);
}

void GameMainWindow::on_Shop_clicked()
{
    ShopWindow shop(this);
    shop.setWindowTitle("Shop");
    shop.setWindowIcon(QIcon(":/resource/img/shop_img.jpg"));
    shop.exec();
}
