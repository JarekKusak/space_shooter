//
// Created by Jaroslav Kusák on 29.02.2024.
//

#ifndef SPACESHOOTER_ENEMYBULLET_H
#define SPACESHOOTER_ENEMYBULLET_H

#include <SFML/Graphics.hpp>

class EnemyBullet {
public:
    EnemyBullet(sf::Vector2f startPos, sf::Vector2f targetPos, int _damageAmount);

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

    bool isTooFarFrom(const sf::Vector2f& playerPosition, float maxDistance) const;
    bool checkCollision(sf::FloatRect playerBounds) const;
    sf::FloatRect getBoundingBox() const;
    void markForDeletion();
    bool isMarkedForDeletion() const;

    int returnDamageAmount() const;

    void draw(sf::RenderWindow& window) const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity; // speed and direction of bullet
    float speed;
    bool markedForDeletion; // mark for deletion, if hit the player or out of player's range
    int damageAmount;
};

#endif //SPACESHOOTER_ENEMYBULLET_H