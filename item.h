#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include "hero.h"

class Item : public std::enable_shared_from_this<Item>
{

public:
    QString _name;
    QString _description;

    Item(QString name, QString description);
    QString getName();
    QString getDescription();
    virtual void consume(Hero *hero) const = 0;
    virtual bool useOnce() const = 0;
    void peek(Hero *hero);
};

#endif // ITEM_H
