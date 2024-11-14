//
// Created by Jaroslav Kusák on 19.02.2024.
//

#include "BasicAlien.h"
#include <iostream>

BasicAlien::BasicAlien() {
    if (!texture.loadFromFile("../resources/sprites/basic-alien.png")) {
        // Handle error
    }
    sprite.setScale(80.0f / texture.getSize().x, 80.0f / texture.getSize().y);
    sprite.setTexture(texture);
    speed = 30.f;
    alive = true;
    health = 100;
    damage = 20;
}

void BasicAlien::takeDamage(int amount) {
    health -= amount;
    if (health <= 0)
        alive = false;
}

sf::FloatRect BasicAlien::getBoundingBox() const {
    return sprite.getGlobalBounds();
}

void BasicAlien::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void BasicAlien::shoot(const sf::Vector2f& targetPosition, std::vector<EnemyBullet>& bullets) {
    if (shootTimer.getElapsedTime().asSeconds() >= shootInterval) {
        bullets.emplace_back(sprite.getPosition(), targetPosition, damage);
        shootTimer.restart();
    }
}

void BasicAlien::update(sf::Time deltaTime, sf::Vector2f playerPosition) {
    sf::Vector2f currentPosition = sprite.getPosition();
    sf::Vector2f directionToPlayer = playerPosition - currentPosition;

    // normalization of vector and movement to player
    float magnitude = std::sqrt((directionToPlayer.x * directionToPlayer.x) + (directionToPlayer.y * directionToPlayer.y));
    sf::Vector2f normalizedDirection = directionToPlayer / magnitude;

    float speed = 50.f; // SPEED
    sprite.move(normalizedDirection * speed * deltaTime.asSeconds());
}

void BasicAlien::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool BasicAlien::isAlive() const {
    return alive;
}