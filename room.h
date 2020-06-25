#ifndef ROOM_H
#define ROOM_H

#include <QMap>
#include <QString>
class Item;
#include <memory>

enum class Direction{Room1=0, Room2, Room3, Room4};

class Room
{
public:
    QString _name;
    QString _description;
    QString _bossdescription;
    bool _shop;
    QMap<Direction,int> _neighbourRooms;
    QList<std::shared_ptr<Item>> _ItemsOnFloor;

    std::shared_ptr<Item> peekItem(int index);
    void putItem(std::shared_ptr<Item> item);

    Room(QString roomName,QString roomDescr,QString bossDescr,bool shop,int r1, int r2, int r3, int r4);
};

#endif // ROOM_H
