#include "Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f position, float angle) : speed(1000.0f), markedForDeletion(false) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);

    // calculating director from the angle in degrees and transfering it to radians
    float radianAngle = (angle - 90.0f) * static_cast<float>(M_PI) / 180.0f;
    direction.x = std::cos(radianAngle);
    direction.y = std::sin(radianAngle);

    velocity = direction * speed;
}

void Bullet::update(sf::Time deltaTime) {
    sf::Vector2f movement = velocity * deltaTime.asSeconds();
    shape.move(movement);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

const sf::Vector2f& Bullet::getPosition() const {
    return shape.getPosition();
}

bool Bullet::isTooFarFrom(const sf::Vector2f& playerPosition, float maxDistance) const {
    sf::Vector2f diff = shape.getPosition() - playerPosition;
    return (diff.x * diff.x + diff.y * diff.y) > (maxDistance * maxDistance);
}

sf::FloatRect Bullet::getBoundingBox() const {
    return shape.getGlobalBounds();
}

void Bullet::markForDeletion() {
    markedForDeletion = true;
}

bool Bullet::isMarkedForDeletion() const {
    return markedForDeletion;
}