#include "hero.h"

Hero::Hero(Maze* maze, QObject *parent) : QObject(parent), _maze(maze)
{
    _currentRoom = 0;
    _rage = 15;
    _money = 4;
}


void Hero::move(Direction direction){
    _currentRoom =  _maze->_rooms[_currentRoom]._neighbourRooms[direction];
    hero_moved(_currentRoom);
}

void Hero::addItem(std::shared_ptr<Item> item)
{
    _inventory.append(item);
    inventory_changed(_inventory);
}

QList<std::shared_ptr<Item> > Hero::getItems()
{
    return _inventory;
}

bool Hero::changeMoney(int delta)
{
    if (delta < 0){
        if (_money > delta){
            _money += delta;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        _money += delta;
        return true;
    }
}

int Hero::getMoney()
{
    return _money;
}

int Hero::getRage()
{
    return _rage;
}

void Hero::changeRage(int rage_delta)
{
    if (rage_delta < 0){
        if (_rage > rage_delta){
            _rage += rage_delta;
        }
        else{
            _rage = 0;
        }
    }
    else{
        _rage += rage_delta;
    }
}

