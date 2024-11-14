//
// Created by Jaroslav Kusák on 08.03.2024.
//

#ifndef SPACESHOOTER_HEALTHKIT_H
#define SPACESHOOTER_HEALTHKIT_H

#include <SFML/Graphics.hpp>
class HealthKit {
public:
    HealthKit(const sf::Vector2f& position, int healthAmount);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool checkCollisionWithObject(const sf::FloatRect& playerBounds) const;
    float getHealthAmount() const;
    void setPosition(const sf::Vector2f& position);
    void markForDeletion();
    bool isMarkedForDeletion() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    int healthAmount;
    bool markedForDeletion;
};

#endif //SPACESHOOTER_HEALTHKIT_H
