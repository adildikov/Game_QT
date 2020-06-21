#ifndef ROOM_H
#define ROOM_H

#include <QMap>
#include <QString>

enum class Direction{Room1=0, Room2, Room3, Room4};

class Room
{
public:
    QString _name;
    QString _description;
    bool _enemy;
    QMap<Direction,int> _neighbourRooms;

    Room(QString roomName,QString roomDescr, int r1, int r2, int r3, int r4);
};

#endif // ROOM_H
