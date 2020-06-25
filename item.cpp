#include "item.h"

Item::Item(QString name, QString description) : _name(name),
    _description(description)
{

}

QString Item::getName(){
    return _name;
}

QString Item::getDescription(){
    return _description;
}

void Item::peek(Hero *hero)
{
    hero->addItem(shared_from_this());
}

