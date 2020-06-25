#include "room.h"

std::shared_ptr<Item> Room::peekItem(int index)
{
    std::shared_ptr<Item> item = _ItemsOnFloor[index];
    _ItemsOnFloor.removeAt(index);
    return item;
}

void Room::putItem(std::shared_ptr<Item> item)
{
    _ItemsOnFloor.append(item);
}

Room::Room(QString roomName, QString roomDescr, QString bossDescr, bool shop, int r1, int r2, int r3, int r4):_name(roomName),
    _description(roomDescr), _bossdescription(bossDescr), _shop(shop)
{
        _neighbourRooms[Direction::Room1] = r1;
        _neighbourRooms[Direction::Room2] = r2;
        _neighbourRooms[Direction::Room3] = r3;
        _neighbourRooms[Direction::Room4] = r4;
}
