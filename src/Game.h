//
// Created by Jaroslav Kusák on 09.11.2023.
//

#ifndef SPACESHOOTER_GAME_H
#define SPACESHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Alien.h"
#include "BasicAlien.h"
#include "AdvancedAlien.h"
#include "HealthKit.h"

class Game {
public:
    Game(sf::RenderWindow &window);
    void run();

private:
    void init();
    void calculateTileNumbers();
    void setupBackgroundTiles();
    void setupPlayer();
    void setupCamera();
    void loadTexture(sf::Texture& texture, const std::string& path, bool repeated = false);
    void loadFont(sf::Font& font, const std::string& path);
    void setupText(sf::Text& text, sf::Font& font, unsigned int size, sf::Color color);
    void setupHealthBar();
    void setupAliensKilledOutput();
    void setupAmmoDisplay();

    void endGame();
    void processEvents();
    void update(sf::Time deltaTime);
    void updateEachAlien(sf::Time deltaTime);
    bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
    void checkAlienCollisionWithPlayer(const std::unique_ptr<Alien>& alien);
    void render();
    void updateBackground();
    void updateBullets(sf::Time deltaTime);
    void updateTextOnScreen();
    void spawnAlien();

    void erasePlayerAndEnemyBullets();
    void eraseDeadAliens();

    void spawnHealthKit();
    void updateHealthKits();

    std::string createHealthBarString(int health, int maxHealth);

    sf::Font font;
    sf::Text playerPositionText;
    sf::Text healthBarText;
    sf::Text aliensKilledText;

    sf::RenderWindow &window;
    sf::View camera; // camera focused on player
    sf::Vector2f previousCameraCenter;

    Player player; // player object
    sf::Texture playerTexture; // player texture
    sf::Texture backgroundTexture;
    std::vector<sf::Sprite> backgroundTiles;

    std::vector<std::unique_ptr<Alien>> aliens;
    sf::Time alienSpawnTimer; // timer for generating aliens
    sf::Time alienSpawnInterval; // interval between spawning aliens

    bool isPlaying;
    const int windowWidth = 1280; // window height
    const int windowHeight = 720; // window width
    const int tileWidth = 1920; // width of tile (background image)
    const int tileHeight = 1080; // height of tile
    int numberOfTilesX;
    int numberOfTilesY;
    std::vector<Bullet> bullets;
    std::vector<EnemyBullet> enemyBullets;

    const int healthBuff = 25;
    const int alienDamageTakenAfterCollision = 100;
    const float distanceForBulletsToDisappear = 800.f;
    const int fontSize = 24;

    std::pair<float,float> chooseRandomSideOfTheScreen(int spawnOffset, int spawnDistance);

    std::vector<HealthKit> healthKits;
    sf::Clock healthKitSpawnTimer;
    const sf::Time healthKitSpawnInterval = sf::seconds(3);
    void checkHealthKitsCollisions();

    int level = 1;
    int aliensKilledInLevel = 0;
    int aliensToKillForNextLevel = 5;
    sf::Text levelText;

    void setupLevelDisplay();
    void increaseLevel();
    void checkLevelProgress();

    sf::Text gameOverText;
    sf::RectangleShape overlay;

    void showGameOver();

    enum class GameState {
        Playing,
        GameMenu
    };

    enum class Action {
        None,
        Continue,
        Exit
    };

    GameState currentState = GameState::Playing;
    void renderGameMenu();
    void toggleGameMenu();

    std::vector<sf::Text> menuItems;
    int selectedItemIndex = 0;
    void handleInput(const sf::Event& event);

    void initMenuItems();
    void drawGameMenu();
    void moveUp();
    void moveDown();
    Action selectOption();
    sf::Vector2f center;

    sf::Text ammoDisplayText;
    void updateAmmoDisplay(int currentAmmo, int maxAmmo);
};

#endif //SPACESHOOTER_GAME_H
