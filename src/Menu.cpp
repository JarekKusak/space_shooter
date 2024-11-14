#include "Menu.h"
#include <SFML/Graphics.hpp>

void Menu::centerText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x, y);
}

Menu::Menu(sf::RenderWindow &window, const sf::Font &font) : window(&window), font(font), selectedItemIndex(0) {
    sf::Vector2u windowSize = window.getSize();

    // center of window
    centerX = windowSize.x / 2.0f;
    centerY = windowSize.y / 2.0f;

    sf::Text play("Play", font);
    sf::Text settings("Settings", font);
    sf::Text exit("Exit", font);

    centerText(play, centerX, centerY - 50);
    menuItems.push_back(play);

    centerText(settings, centerX, centerY);
    menuItems.push_back(settings);

    centerText(exit, centerX, centerY + 50);
    menuItems.push_back(exit);

    // default selected item
    menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
}

Menu::Action Menu::handleInput(const sf::Event& event) {
    currentAction = Action::None;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            moveUp();
        else if (event.key.code == sf::Keyboard::Down)
            moveDown();
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedItemIndex == 0)
                currentAction = Action::Play;
            else if (selectedItemIndex == 1)
                currentAction = Action::Settings;
            else if (selectedItemIndex == 2)
                currentAction = Action::Exit;
        }
    }
    return currentAction;
}

void Menu::draw() const {
    for (const auto &item : menuItems)
        window->draw(item);
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
