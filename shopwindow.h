#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class ShopWindow;
}

struct ShopItemInfo{
    ShopItemInfo() = default;
    ShopItemInfo(QString name, int price);
    QString _name;
    int _price;
};


class ShopModel : public QAbstractTableModel{
    Q_OBJECT
public:
    ShopModel(QVector<ShopItemInfo> *inventory, QObject *parent = nullptr);
    virtual int rowCount(const QModelIndex &parent = QModelIndex())const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex())const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role =Qt::DisplayRole) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QVector<ShopItemInfo> *_inventory;


};

class ShopWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShopWindow(QWidget *parent = nullptr);
    ~ShopWindow();

private:

    Ui::ShopWindow *ui;
    QVector<ShopItemInfo> _inventory;
};

#endif // SHOPWINDOW_H
