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

