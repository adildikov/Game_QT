#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"
#include "mainwindow.h"
#include "shopwindow.h"
#include "questitem.h"
#include <QMessageBox>
#include <QPixmap>
#include <iostream>

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
    connect(_game->_hero, SIGNAL(money_changed(int)), this, SLOT(show_money(int)));
    connect(_game->_hero, SIGNAL(inventory_changed(QList<std::shared_ptr<Item>>)), this, SLOT(show_inventory(QList<std::shared_ptr<Item>>)));
    connect(_game->_hero, SIGNAL(rage_changed(int)), this, SLOT(show_rage(int)));
    connect(_game->_hero, SIGNAL(endGame()), this, SLOT(on_quit_clicked()));
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

    if(newRoom._bossdescription != ""){
        ui->getDocument->show();
    }else{
        ui->getDocument->hide();
    }


    if(newRoom._ItemsOnFloor.size() > 0){
        ui->ItemsOnFloor->clear();
        ui->PeekButton->show();
        ui->ItemsOnFloor->show();
        ui->label_itemsOnFloor->show();
        for (int i = 0; i < newRoom._ItemsOnFloor.size();i++) {
            ui->ItemsOnFloor->addItem(newRoom._ItemsOnFloor[i]->_name);
        }

    }else{
        ui->PeekButton->hide();
        ui->ItemsOnFloor->hide();
        ui->label_itemsOnFloor->hide();
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
    if(ui->Room4->text() == "Выход"){
        bool flag = false;
        for (int i = 0; i < _game->_hero->_inventory.size() ;i++) {
            if(_game->_hero->_inventory[i]->_name == "Справка ГТО-228"){
                flag = true;
                break;
            }
        }

        if (flag){
            _game->_hero->move(Direction::Room4);
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Alert");
            msgBox.setWindowIcon(QIcon(":/resource/img/Boss3.jpg"));
            msgBox.setText("Вы не можете уйти без нужной вам справки.");
            msgBox.exec();
        }

    }else{
        _game->_hero->move(Direction::Room4);
    }
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
    int current_money = QVariant(ui->MoneyAmount->text()).toInt();
    ui->MoneyAmount->setText(QVariant(current_money + money).toString());
}

void GameMainWindow::show_rage(int rage)
{
    ui->Rage_status->setValue(rage);
}

void GameMainWindow::on_Shop_clicked()
{
    ShopWindow shop(this, _game->_hero);
    shop.setWindowTitle("Shop");
    shop.setWindowIcon(QIcon(":/resource/img/shop_img.jpg"));
    shop.exec();
}

void GameMainWindow::on_useItem_clicked()
{
    QModelIndex currentIndex = ui->InventoryList->currentIndex();
    if (!currentIndex.isValid()){
        return;
    }
    _game->_hero->useItem(currentIndex.row());
}

void GameMainWindow::on_PeekButton_clicked()
{
    QModelIndex currentIndex = ui->ItemsOnFloor->currentIndex();
    if (!currentIndex.isValid()){
        return;
    }
    _game->peekItem(_game->_hero, currentIndex.row());
    ui->ItemsOnFloor->clear();
    for (int i = 0; i < _game->_maze->_rooms[_game->_hero->_currentRoom]._ItemsOnFloor.size();i++) {
        ui->ItemsOnFloor->addItem(_game->_maze->_rooms[_game->_hero->_currentRoom]._ItemsOnFloor[i]->_name);
    }
}

void GameMainWindow::on_getDocument_clicked()
{
    int flag = 0;
    int index;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Alert");
    msgBox.setWindowIcon(QIcon(":/resource/img/Boss3.jpg"));

    for (int i = 0; i < _game->_hero->_inventory.size(); i++){
        if(_game->_hero->_inventory[i]->_name == "Ручка"){
            flag++;
            break;
        }
    }

    if(_game->_hero->_currentRoom == 3){

        for (int i = 0; i < _game->_hero->_inventory.size(); i++){
            if(_game->_hero->_inventory[i]->_name == "Бумага"){
                flag++;
                index = i;
                break;
            }
        }


        if(flag == 0){
            msgBox.setText("У тебя ни ручки, ни бумаги. Чего ты от меня хочешь?");
            _game->_hero->changeRage(15);
        }else if(flag == 1){
            msgBox.setText("Чего-то не хватает...");
            _game->_hero->changeRage(10);
        }else if(flag == 2){
            msgBox.setText("Так уж и быть, держите свою справку");
            _game->_hero->changeRage(5);
            _game->_hero->addItem(std::make_shared<QuestItem>(QuestItem("Справка ГПК-001","Справка ГПК-001, но это не то, что вам нужно.")));
            _game->_hero->_inventory.removeAt(index);
            _game->_hero->inventory_changed(_game->_hero->_inventory);
            _game->_maze->_rooms[_game->_hero->_currentRoom]._bossdescription = "";
            _game->_maze->_rooms[_game->_hero->_currentRoom]._description = " Петров куда-то ушел. Повезло, что вы успели взять у него\n справку";
            ui->getDocument->hide();
        }
    }else if(_game->_hero->_currentRoom == 4){

        for (int i = 0; i < _game->_hero->_inventory.size(); i++){
            if(_game->_hero->_inventory[i]->_name == "Бумага"){
                flag++;
                index = i;
                break;
            }
        }

        for (int i = 0; i < _game->_hero->_inventory.size(); i++){
            if(_game->_hero->_inventory[i]->_name == "Справка ГПК-001"){
                flag++;
                break;
            }
        }

        if(flag == 0){
            msgBox.setText("У тебя ничего нет. Чего ты от меня хочешь?");
            _game->_hero->changeRage(15);
        }else if(flag == 1 || flag == 2){
            msgBox.setText("Чего-то не хватает...");
            _game->_hero->changeRage(10);
        }else if(flag == 3){
            msgBox.setText("Так уж и быть, держите свою справку");
            _game->_hero->changeRage(5);
            _game->_hero->addItem(std::make_shared<QuestItem>(QuestItem("Справка У-002","Ценная бумага, но вы здесь не за этим.")));
            _game->_hero->_inventory.removeAt(index);
            _game->_hero->inventory_changed(_game->_hero->_inventory);
            _game->_maze->_rooms[_game->_hero->_currentRoom]._bossdescription = "";
            _game->_maze->_rooms[_game->_hero->_currentRoom]._description = " Смирнов куда-то ушел. Повезло, что вы успели взять у него\n справку";
            ui->getDocument->hide();
        }
    }else if(_game->_hero->_currentRoom == 6){

        for (int i = 0; i < _game->_hero->_inventory.size(); i++){
            if(_game->_hero->_inventory[i]->_name == "Бумага"){
                flag++;
                index = i;
                break;
            }
        }

        for (int i = 0; i < _game->_hero->_inventory.size(); i++){
            if(_game->_hero->_inventory[i]->_name == "Справка ГПК-001"){
                flag++;
                break;
            }
        }

        for (int i = 0; i < _game->_hero->_inventory.size(); i++){
            if(_game->_hero->_inventory[i]->_name == "Справка У-002"){
                flag++;
                break;
            }
        }

        if(flag == 0){
            msgBox.setText("У тебя ничего нет. Чего ты от меня хочешь?");
            _game->_hero->changeRage(15);
        }else if(flag == 1 || flag == 2 || flag == 3){
            msgBox.setText("Чего-то не хватает...");
            _game->_hero->changeRage(10);
        }else if(flag == 4){
            msgBox.setText("Так уж и быть, держите свою справку");
            _game->_hero->changeRage(5);
            _game->_hero->addItem(std::make_shared<QuestItem>(QuestItem("Справка ГТО-228","Это как раз то, что вам нужно.")));
            _game->_hero->_inventory.removeAt(index);
            _game->_hero->inventory_changed(_game->_hero->_inventory);
            _game->_maze->_rooms[_game->_hero->_currentRoom]._bossdescription = "";
            _game->_maze->_rooms[_game->_hero->_currentRoom]._description = " Слутин куда-то ушел. Повезло, что вы успели взять у него\n справку";
            ui->getDocument->hide();
        }
    }
    msgBox.exec();
    if (_game->_hero->_rage >= 100){
        msgBox.setText("Вы слишком перенервничали");
        msgBox.exec();
        _game->_hero->endGame();
    }

}
