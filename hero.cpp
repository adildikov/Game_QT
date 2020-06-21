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
