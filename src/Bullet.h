//
// Created by Jaroslav Kusák on 26.01.2024.
//

#ifndef SPACESHOOTER_BULLET_H
#define SPACESHOOTER_BULLET_H
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Vector2f position, float angle);

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen(sf::Vector2u windowSize) const;
    sf::FloatRect getBoundingBox() const; // for collision detection

    void markForDeletion();
    bool isMarkedForDeletion() const;

    bool isTooFarFrom(const sf::Vector2f& playerPosition, float maxDistance) const;
    const sf::Vector2f& getPosition() const;

    const sf::CircleShape& getCollisionMask() const {
        return shape;
    }

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    bool markedForDeletion;
};

#endif //SPACESHOOTER_BULLET_H