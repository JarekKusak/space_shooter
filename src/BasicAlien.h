//
// Created by Jaroslav Kusák on 19.02.2024.
//

#ifndef SPACESHOOTER_BASICALIEN_H
#define SPACESHOOTER_BASICALIEN_H

#include "Alien.h"
#include "EnemyBullet.h"
#include <SFML/Graphics.hpp>

class BasicAlien : public Alien {
public:
    BasicAlien();

    sf::Clock shootTimer;
    float shootInterval = 2.0f;

    virtual void update(sf::Time deltaTime, sf::Vector2f playerPosition) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual bool isAlive() const override;

    virtual void takeDamage(int amount) override;
    virtual sf::FloatRect getBoundingBox() const override;
    virtual void setPosition(float x, float y) override;

    virtual void shoot(const sf::Vector2f& targetPosition, std::vector<EnemyBullet>& bullets) override;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    int health;
    float speed;
    bool alive;
    int damage;
};

#endif //SPACESHOOTER_BASICALIEN_H
