#include "Game.hpp"

int main()
{
    try
    {
        Game game;
        while (game.isRunning())
        {
            game.pollEvents();
            game.update();
            game.draw();
        }
    }
    catch (const std::string &ex)
    {
        Game::logError(ex);
        return -1;
    }

    return 0;
}
