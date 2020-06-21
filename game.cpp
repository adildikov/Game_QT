#include "game.h"

Game::Game()
{
    _maze = new Maze();
    _hero = new Hero(_maze);
}
