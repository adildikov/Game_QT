#include "questitem.h"

QuestItem::QuestItem(QString name, QString description) : Item(name, description)
{

}

bool QuestItem::useOnce() const
{
    return false;
}
