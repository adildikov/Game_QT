#include "maze.h"

Maze::Maze()
{
    Init();
}


Room& Maze::operator [] (int index){
    return _rooms[index];
}


void Maze::Init(){
    _rooms.append(Room("Коридор", "Описание коридора и задачи игрока",1,5,3,7));
    _rooms.append(Room("Буфет","Описание буфета",0,2,-1,-1));
    _rooms.append(Room("Туалет", "Описание туалета",1,3,-1,-1));
    _rooms.append(Room("Чиновник 1","Описание",0,5,2,-1));
    _rooms.append(Room("Чиновник 2","Описание", 5,-1,-1,-1));
    _rooms.append(Room("Приёмная","Описание приёмной",0,3,4,6));
    _rooms.append(Room("Чиновник 3","Описание чиновника 3",5,-1,-1,-1));
    _rooms.append(Room("Выход","Благоданости", -1,-1,-1,-1));
}
