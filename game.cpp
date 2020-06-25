#include "game.h"
#include "food.h"
class Item;

Game::Game()
{
    _maze = new Maze();
    _hero = new Hero(_maze);
    _hero->addItem(std::make_shared<Food>(Food("Кофе", "Успокаивает вас", 5)));
}
