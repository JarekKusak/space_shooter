//
// Created by Jaroslav Kusák on 29.02.2024.
//

#include "EnemyBullet.h"
#include <cmath>

EnemyBullet::EnemyBullet(sf::Vector2f startPos, sf::Vector2f targetPos, int _damageAmount)
        : speed(500.0f), markedForDeletion(false), damageAmount(_damageAmount) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startPos);

    // direction to target (player position)
    sf::Vector2f direction = targetPos - startPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = direction / length * speed;
}

void EnemyBullet::update(sf::Time deltaTime) {
    shape.move(velocity * deltaTime.asSeconds());
}

sf::FloatRect EnemyBullet::getBoundingBox() const {
    return shape.getGlobalBounds();
}

void EnemyBullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool EnemyBullet::isTooFarFrom(const sf::Vector2f& playerPosition, float maxDistance) const {
    sf::Vector2f diff = shape.getPosition() - playerPosition;
    return (diff.x * diff.x + diff.y * diff.y) > (maxDistance * maxDistance);
}

bool EnemyBullet::checkCollision(sf::FloatRect playerBounds) const {
    return shape.getGlobalBounds().intersects(playerBounds);
}

void EnemyBullet::markForDeletion() {
    markedForDeletion = true;
}

int EnemyBullet::returnDamageAmount() const {
    return damageAmount;
}

bool EnemyBullet::isMarkedForDeletion() const {
    return markedForDeletion;
}

void EnemyBullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}