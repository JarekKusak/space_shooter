#include "Player.h"
Player::Player() : maxHealth(100), health(100), damage(50), currentAngle(0), targetAngle(0), rotationSpeed(800), fireRate(0.1f),
timeSinceLastShot(sf::seconds(0)), globalPosition(0.f, 0.f) {}

void Player::update(sf::Time deltaTime) {
    const float movementSpeed = 600.f; // player speed
    sf::Vector2f movement(0.f, 0.f);

    // player movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= movementSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += movementSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= movementSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += movementSpeed;

    // actualization of global position due to movement
    globalPosition += movement * deltaTime.asSeconds();

    // ROTATION
    // shortest rotation path
    float deltaAngle = targetAngle - currentAngle;
    // floatingpoint modulo
    deltaAngle = fmod(deltaAngle, 360.0f); // delta angle between -360 and 360 degrees
    if (deltaAngle > 180.0f)
        deltaAngle -= 360.0f; // normalization to range between -180 to 180 degrees
    else if (deltaAngle < -180.0f)
        deltaAngle += 360.0f;
    // how fast is sprite suppose to rotate
    float angleStep = rotationSpeed * deltaTime.asSeconds();

    /*
     * This line means that if the difference between the current angle (currentAngle)
     * and the target angle (targetAngle) is less than the angle step (angleStep),
     * which is calculated based on rotation speed and elapsed time (deltaTime),
     * then the current angle is set directly to the target angle.
     * This prevents the sprite from "rolling over" or "wobbling" as it approaches the target angle.
    */
    if (std::abs(deltaAngle) < angleStep)
        currentAngle = targetAngle;
    else // direction of rotation
        currentAngle += angleStep * (deltaAngle > 0 ? 1 : -1);
    // normalization to range between 0 to 359 degrees
    currentAngle = fmod(currentAngle + 360.0f, 360.0f);

    sprite.setRotation(currentAngle);

    if (isReloading && reloadClock.getElapsedTime() >= reloadTime) {
        bulletsInMagazine = magazineCapacity;
        isReloading = false;
    }

    timeSinceLastShot += deltaTime; // update shot timer
}

int Player::getCurrentAmmo(){
    return bulletsInMagazine;
}

int Player::getMaxAmmo(){
    return magazineCapacity;
}

void Player::reload() {
    isReloading = true;
    reloadClock.restart();
}

void Player::shoot(std::vector<Bullet>& bullets) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletsInMagazine > 0 && !isReloading && timeSinceLastShot.asSeconds() >= fireRate) {
        bullets.emplace_back(getGlobalPosition(), currentAngle);
        bulletsInMagazine--;
        if (bulletsInMagazine == 0)
            reload();
        timeSinceLastShot = sf::Time::Zero;
    }
}

int Player::getPlayerDamage() {
    return damage;
}

void Player::handleInput() {
    // which key was pressed -> angle of rotation
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    if (up && right)
        targetAngle = 45;
    else if (up && left)
        targetAngle = 315;
    else if (down && right)
        targetAngle = 135;
    else if (down && left)
        targetAngle = 225;
    else if (up)
        targetAngle = 0;
    else if (down)
        targetAngle = 180;
    else if (left)
        targetAngle = 270;
    else if (right)
        targetAngle = 90;
}

void Player::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

void Player::decrementHealth(int amount) {
    health -= amount;
    if (health < 0)
        health = 0;
}

void Player::incrementHealth(int amount) {
    health += amount;
    if (health > maxHealth)
        health = maxHealth;
}

sf::Vector2f Player::getGlobalPosition() const {
    return globalPosition;
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

bool Player::isAlive() const {
    return health > 0;
}

void Player::setPosition(const sf::Vector2f& position) {
    globalPosition = position;
}

void Player::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Player::draw(sf::RenderWindow &window) {
    sprite.setPosition(globalPosition);
    window.draw(sprite);
}

sf::FloatRect Player::getCollisionMask() const {
    return sprite.getGlobalBounds();
}