#ifndef HERO_H
#define HERO_H

#include "maze.h"

#include <QObject>

class Hero : public QObject
{
    Q_OBJECT
public:
    explicit Hero(Maze* maze, QObject *parent = nullptr);
    Maze* _maze;
    int _currentRoom;
    int _rage;
    int _money;

    void move(Direction direction);

signals:
    void hero_moved(int room);

};

#endif // HERO_H
