#include "room.h"

Room::Room(QString roomName,QString roomDescr, int r1, int r2, int r3, int r4):_name(roomName),
    _description(roomDescr)
{
        _neighbourRooms[Direction::Room1] = r1;
        _neighbourRooms[Direction::Room2] = r2;
        _neighbourRooms[Direction::Room3] = r3;
        _neighbourRooms[Direction::Room4] = r4;
}
