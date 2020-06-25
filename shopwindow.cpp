#include "shopwindow.h"
#include "ui_shopwindow.h"
#include "food.h"
#include <iostream>

ShopWindow::ShopWindow(QWidget *parent, Hero* hero) :
    QDialog(parent), ui(new Ui::ShopWindow), _hero(hero)
{
    ui->setupUi(this);

    _inventory<<ShopItemInfo("Сэндвич", "Вкусный сендвич, успокоит вас на 10", 15, 10)<<ShopItemInfo("Кофе", "Ароматный кофе 3 в 1, который немного успокоит вас", 5, 5);


    ui->ShopView->setModel(new ShopModel(& _inventory, ui->ShopView));
    ui->ShopView->resizeColumnsToContents();
    ui->MoneyValue->setText(QVariant(_hero->_money).toString());
}

ShopWindow::~ShopWindow()
{
    delete ui;
}

void ShopWindow::showMoney(int money)
{
    ui->MoneyValue->setText(QVariant(money).toString());
}


ShopItemInfo::ShopItemInfo(QString name, QString description, int rage_change, int price): _name(name), _description(description),
    _rage(rage_change), _price(price)
{

}

ShopModel::ShopModel(QVector<ShopItemInfo> *inventory, QObject *parent) : QAbstractTableModel(parent), _inventory(inventory)
{

}

int ShopModel::rowCount(const QModelIndex &parent) const
{
    return _inventory->count();
}

int ShopModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ShopModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation == Qt::Horizontal){
        switch(section){
        case 0: return "Предмет";
        case 1: return "Цена";
        default: return QVariant();
        }
    }
    else{
        return QString("%1").arg(section + 1);
    }
}

QVariant ShopModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }

    switch (index.column()) {
    case 0: return (*_inventory)[index.row()]._name;
    case 1: return QString("%1").arg((*_inventory)[index.row()]._price);
    default: return QVariant();
    }

    return QVariant();
}

void ShopWindow::on_Buy_clicked()
{
    QModelIndex currentIndex = ui->ShopView->currentIndex();
    if(!currentIndex.isValid())
    {
        return;
    }
    int currentRow = currentIndex.row();
    currentRow++;
    if (_hero->changeMoney(-1 *_inventory[currentRow - 1]._price)){
        _hero->addItem(std::make_shared<Food>(Food(_inventory[currentRow - 1]._name, _inventory[currentRow - 1]._description
                                                   , _inventory[currentRow - 1]._rage)));
        _hero->money_changed(-1 * _inventory[currentRow - 1]._price);
        _hero->inventory_changed(_hero->_inventory);
        ui->MoneyValue->setText(QVariant(_hero->_money).toString());
    }
    else{
        return;
    }
}
