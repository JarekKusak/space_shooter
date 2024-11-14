//
// Created by Jaroslav Kusák on 08.03.2024.
//

#include "AdvancedAlien.h"

#include <cmath>

AdvancedAlien::AdvancedAlien() {
    if (!texture.loadFromFile("../resources/sprites/alien-space-ship-2.png")) {
        // Handle error
    }
    sprite.setScale(0.5f, 0.5f);
    sprite.setTexture(texture);
    speed = 100.f;
    alive = true;
    health = 200;
    damage = 30;
    shootInterval = 0.7f;
}

void AdvancedAlien::takeDamage(int amount) {
    health -= amount;
    if (health <= 0)
        alive = false;
}

sf::FloatRect AdvancedAlien::getBoundingBox() const {
    return sprite.getGlobalBounds();
}

void AdvancedAlien::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void AdvancedAlien::shoot(const sf::Vector2f& targetPosition, std::vector<EnemyBullet>& bullets) {
    if (shootTimer.getElapsedTime().asSeconds() >= shootInterval) {
        bullets.emplace_back(sprite.getPosition(), targetPosition, damage);
        shootTimer.restart();
    }
}

void AdvancedAlien::update(sf::Time deltaTime, sf::Vector2f playerPosition) {
    sf::Vector2f currentPosition = sprite.getPosition();
    sf::Vector2f directionToPlayer = playerPosition - currentPosition;

    // normalization of vector and movement to player
    float magnitude = std::sqrt((directionToPlayer.x * directionToPlayer.x) + (directionToPlayer.y * directionToPlayer.y));
    sf::Vector2f normalizedDirection = directionToPlayer / magnitude;

    sprite.move(normalizedDirection * speed * deltaTime.asSeconds());
}

void AdvancedAlien::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool AdvancedAlien::isAlive() const {
    return alive;
}