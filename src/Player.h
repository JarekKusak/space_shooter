#ifndef SPACESHOOTER_PLAYER_H
#define SPACESHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Player {
public:
    Player();
    void setTexture(const sf::Texture &texture);
    void draw(sf::RenderWindow &window);
    void setScale(float scaleX, float scaleY);
    sf::FloatRect getCollisionMask() const;
    void decrementHealth(int amount);
    void incrementHealth(int amount);
    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;

    sf::Vector2f getGlobalPosition() const;
    void setPosition(const sf::Vector2f& position);
    void shoot(std::vector<Bullet>& bullets);
    void update(sf::Time deltaTime);
    void handleInput();
    int getPlayerDamage();

    void reload();
    int getCurrentAmmo();
    int getMaxAmmo();
private:
    sf::Vector2f globalPosition; // global position in game world

    int health;
    int maxHealth;
    sf::Sprite sprite;
    float currentAngle;
    float targetAngle; // target angle to rotate
    float rotationSpeed;
    int damage;

    float fireRate;
    sf::Time timeSinceLastShot;

    int magazineCapacity = 10;
    int bulletsInMagazine = 10;
    bool isReloading = false;
    sf::Time reloadTime = sf::seconds(2);
    sf::Clock reloadClock;
};

#endif //SPACESHOOTER_PLAYER_H