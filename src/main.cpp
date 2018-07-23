#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"

using namespace std;
using namespace sf;

int main()
{
    Game game;
    
    game.init();
    
    while (game.window.isOpen())
    {
        float dt = game.clock.restart().asSeconds();
        
        Event event;
        while (game.window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                game.window.close();
        }

        game.update(dt);
        
        game.window.clear();
        game.draw();
        game.window.display();
    }

    game.deInit();

    return 0;
}
