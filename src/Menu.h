//
// Created by Jaroslav Kusák on 09.11.2023.
//

#ifndef SPACESHOOTER_MENU_H
#define SPACESHOOTER_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    enum class Action {
        None,
        Play,
        Settings,
        Exit
    };
    Menu(sf::RenderWindow &window, const sf::Font &font);
    // Methods
    Action handleInput(const sf::Event& event);
    void draw() const;
    void moveUp();
    void moveDown();
    int getPressedItem() const { return selectedItemIndex; }
private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    sf::RenderWindow *window;
    float centerX;
    float centerY;
    Action currentAction;
    // Methods
    void centerText(sf::Text &text, float x, float y);
};

#endif //SPACESHOOTER_MENU_H
