#ifndef MAZE_H
#define MAZE_H

#include "room.h"

#include <QList>



class Maze
{
public:
    Maze();
    QList<Room> _rooms;
    void Init();
    Room& operator [] (int index);
};

#endif // MAZE_H
