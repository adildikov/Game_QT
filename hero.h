#ifndef HERO_H
#define HERO_H

class Item;
#include "maze.h"
#include <memory>
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
    QList<std::shared_ptr<Item>> _inventory;

    void move(Direction direction);
    void addItem(std::shared_ptr<Item> item);
    QList<std::shared_ptr<Item>> getItems();
    bool changeMoney(int delta);
    int getMoney();

signals:
    void hero_moved(int room);
    void inventory_changed(QList<std::shared_ptr<Item>> items);
    void money_changed(int money);

};

#endif // HERO_H
