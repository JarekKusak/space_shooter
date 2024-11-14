#include "Menu.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Space shooter!");
    sf::Font font;

    if (!font.loadFromFile("../resources/font/ARCADE_I.TTF")) {
        // handle error
    }
    // Load texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../resources/sprites/space-ship.png")) {
        // handle error
    }

    Menu menu(window, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            Menu::Action action = menu.handleInput(event);
            if (action == Menu::Action::Play){
                Game game(window);
                game.run();
            }
            else if (action == Menu::Action::Exit)
                window.close();
        }
        window.clear();
        menu.draw();
        window.display();
    }
    return 0;
}