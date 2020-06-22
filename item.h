#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include "hero.h"

class Item
{

public:
    QString _name;
    QString _description;

    Item(QString name, QString description);
    QString getName();
    QString getDescription();
    virtual void consume() const = 0;
    virtual bool useOnce() const = 0;
};

#endif // ITEM_H
