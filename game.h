#ifndef GAME_H
#define GAME_H

#include "hero.h"
#include "item.h"



class Game
{
public:
    Game();
    Hero* _hero;
    Maze* _maze;

    void peekItem(Hero *hero, int itemIndex);

};

#endif // GAME_H
