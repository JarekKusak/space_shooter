//
// Created by Jaroslav Kusák on 19.02.2024.
//

#ifndef SPACESHOOTER_ALIEN_H
#define SPACESHOOTER_ALIEN_H

#include <SFML/Graphics.hpp>
#include "EnemyBullet.h"

class Alien {
public:
    virtual ~Alien() {}

    virtual void update(sf::Time deltaTime, sf::Vector2f playerPosition) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void takeDamage(int amount) = 0;
    virtual sf::FloatRect getBoundingBox() const = 0;
    virtual bool isAlive() const { return health > 0; }
    virtual void shoot(const sf::Vector2f& targetPosition, std::vector<EnemyBullet>& bullets) = 0;
    virtual void setPosition(float x, float y) = 0;

protected:
    sf::Sprite sprite;
    float speed;
    bool alive;
    int health;
    int damage;
};

#endif //SPACESHOOTER_ALIEN_H
