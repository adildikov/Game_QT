#include "food.h"

Food::Food(QString name, QString description, int rage_change) : Item(name, description), _rage(rage_change)
{

}

bool Food::useOnce() const
{
    return true;
}

void Food::consume(Hero *hero) const
{
    hero->changeRage(_rage);
}
