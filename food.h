#ifndef FOOD_H
#define FOOD_H
#include "item.h"

class Food : public Item
{
public:
    int _rage;
    QString _name;
    QString _description;

    Food(QString name, QString description, int rage_change);
    bool useOnce() const override;
    void consume(Hero *hero) const override;
};

#endif // FOOD_H
