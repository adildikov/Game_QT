#include "shopwindow.h"
#include "ui_shopwindow.h"

ShopWindow::ShopWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShopWindow)
{
    ui->setupUi(this);

    _inventory<<ShopItemInfo("Сэндвич", 10)<<ShopItemInfo("Кофе", 5);


    ui->ShopView->setModel(new ShopModel(& _inventory, ui->ShopView));
    ui->ShopView->resizeColumnsToContents();

}

ShopWindow::~ShopWindow()
{
    delete ui;
}

ShopItemInfo::ShopItemInfo(QString name, int price): _name(name), _price(price)
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
