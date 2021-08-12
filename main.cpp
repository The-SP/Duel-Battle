#include "headers/game.h"
#include <ctime>

int main()
{
    srand(time(0));
    Game game;
    game.run();
}