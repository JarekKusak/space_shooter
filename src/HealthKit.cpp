//
// Created by Jaroslav Kusák on 08.03.2024.
//

// HealthKit.cpp
#include "HealthKit.h"

HealthKit::HealthKit(const sf::Vector2f& position, int healthAmount)
        : healthAmount(healthAmount) {
    if (!texture.loadFromFile("../resources/sprites/health-kit.png")) {
        // Handle loading error
    }
    sprite.setTexture(texture);

    float desiredWidth = 50.0f;
    float desiredHeight = 50.0f;

    float scaleFactorX = desiredWidth / sprite.getLocalBounds().width;
    float scaleFactorY = desiredHeight / sprite.getLocalBounds().height;

    sprite.setScale(scaleFactorX, scaleFactorY);

    sprite.setPosition(position);
}

void HealthKit::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool HealthKit::checkCollisionWithObject(const sf::FloatRect& playerBounds) const {
    return sprite.getGlobalBounds().intersects(playerBounds);
}
void HealthKit::markForDeletion() {
    markedForDeletion = true;
}

bool HealthKit::isMarkedForDeletion() const {
    return markedForDeletion;
}

float HealthKit::getHealthAmount() const {
    return healthAmount;
}

void HealthKit::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

