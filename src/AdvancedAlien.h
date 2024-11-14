//
// Created by Jaroslav Kusák on 08.03.2024.
//

#ifndef SPACESHOOTER_ADVANCEDALIEN_H
#define SPACESHOOTER_ADVANCEDALIEN_H

#include "Alien.h"
#include "EnemyBullet.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AdvancedAlien : public Alien {
public:
    AdvancedAlien();
    virtual void takeDamage(int amount) override;
    virtual void shoot(const sf::Vector2f& targetPosition, std::vector<EnemyBullet>& bullets) override;
    virtual void update(sf::Time deltaTime, sf::Vector2f playerPosition) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual bool isAlive() const override;
    virtual sf::FloatRect getBoundingBox() const override;
    virtual void setPosition(float x, float y) override;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool alive;
    int health;
    int damage;
    sf::Clock shootTimer;
    float shootInterval;
};

#endif //SPACESHOOTER_ADVANCEDALIEN_H
