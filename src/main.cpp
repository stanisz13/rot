#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window;
    Game::init(&window);
    
    while (Game::window->isOpen())
    {
        float dt = Game::clock.restart().asSeconds();
        
        Event event;
        while (Game::window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                Game::window->close();
        }

        Game::update(dt);
        
        Game::window->clear();
        Game::draw();
        Game::window->display();
    }

    Game::deInit();

    return 0;
}
