#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow &window) : window(window), player(), isPlaying(true), alienSpawnTimer(sf::Time::Zero), alienSpawnInterval(sf::seconds(2)) {
    init(); // initialization of new game
}

void Game::init() {
    loadTexture(playerTexture, "../resources/sprites/space-ship.png");
    loadTexture(backgroundTexture, "../resources/sprites/background.jpg", true);
    loadFont(font, "../resources/font/ARCADE_I.TTF");

    setupLevelDisplay();

    setupText(playerPositionText, font, fontSize, sf::Color::White);
    setupHealthBar();
    setupAliensKilledOutput();
    setupBackgroundTiles();
    setupPlayer();
    setupCamera();
    setupAmmoDisplay();

    sf::Vector2u windowSize = window.getSize();
    center = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);

    initMenuItems();
}

void Game::loadTexture(sf::Texture& texture, const std::string& path, bool repeated) {
    if (!texture.loadFromFile(path)) std::cerr << "Failed to load " << path << std::endl;
    texture.setRepeated(repeated);
}

void Game::loadFont(sf::Font& font, const std::string& path) {
    if (!font.loadFromFile(path)) std::cerr << "Failed to load " << path << std::endl;
}

void Game::setupText(sf::Text& text, sf::Font& font, unsigned int size, sf::Color color) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
}

void Game::calculateTileNumbers() {
    numberOfTilesX = ceil(static_cast<float>(windowWidth) / tileWidth) + 2;
    numberOfTilesY = ceil(static_cast<float>(windowHeight) / tileHeight) + 2;
}

void Game::setupBackgroundTiles() {
    calculateTileNumbers();
    for (int y = 0; y < numberOfTilesY; ++y) {
        for (int x = 0; x < numberOfTilesX; ++x) {
            sf::Sprite tile(backgroundTexture);
            tile.setPosition(x * tileWidth, y * tileHeight);
            backgroundTiles.push_back(tile);
        }
    }
}

void Game::setupHealthBar() {
    healthBarText.setFont(font);
    healthBarText.setCharacterSize(fontSize);
    healthBarText.setFillColor(sf::Color::White);
    healthBarText.setPosition(10.f, 10.f); // left corner
}

void Game::setupAmmoDisplay() {
    ammoDisplayText.setFont(font);
    ammoDisplayText.setCharacterSize(fontSize);
    ammoDisplayText.setFillColor(sf::Color::White);
    ammoDisplayText.setPosition(10.f, 70.f);
}

void Game::setupAliensKilledOutput() {
    aliensKilledText.setFont(font);
    aliensKilledText.setCharacterSize(fontSize);
    aliensKilledText.setFillColor(sf::Color::White);
    aliensKilledText.setPosition(window.getSize().x - 500, 10);
}

void Game::setupPlayer() {
    player.setTexture(playerTexture);
    float desiredWidth = 80.0f, desiredHeight = 80.0f;
    player.setScale(desiredWidth / playerTexture.getSize().x, desiredHeight / playerTexture.getSize().y);
}

void Game::setupCamera() {
    camera.setSize(window.getSize().x, window.getSize().y);
    camera.setCenter(player.getGlobalPosition());
    previousCameraCenter = camera.getCenter();
}

void Game::setupLevelDisplay() {
    levelText.setFont(font);
    levelText.setCharacterSize(fontSize);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(10.f, window.getSize().y - 50.f); // lower left part of the window...
}

void Game::increaseLevel() {
    level++;
    aliensKilledInLevel = 0;
    aliensToKillForNextLevel *= 2; // double aliens to kill
    alienSpawnInterval /= 1.1f;
    // more changes to increase difficulty...
}

void Game::checkLevelProgress() {
    if (aliensKilledInLevel >= aliensToKillForNextLevel)
        increaseLevel();
}

std::string Game::createHealthBarString(int health, int maxHealth) {
    std::string healthBar = "[";
    int totalSymbols = 20;
    int healthSymbols = static_cast<int>(static_cast<double>(health) / maxHealth * totalSymbols);
    for (int i = 0; i < healthSymbols; ++i)
        healthBar += "#";
    while (healthBar.size() < totalSymbols + 1) // +1 bcs it contains "[" at the beginning
        healthBar += " ";
    healthBar += "]";

    return healthBar;
}

void Game::run() {
    sf::Clock clock;
    isPlaying = true;
    while (isPlaying && window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                // Toggle game menu with Escape key
                if (event.key.code == sf::Keyboard::Escape) {
                    if (currentState == GameState::Playing)
                        toggleGameMenu();
                    else if (currentState == GameState::GameMenu)
                        toggleGameMenu();
                }
                // handle menu navigation if we're in the GameMenu state
                else if (currentState == GameState::GameMenu)
                    handleInput(event);
                break;
        }
    }
}


void Game::showGameOver() {
    // overlay
    overlay.setSize(static_cast<sf::Vector2f>(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // transparent grey color

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    gameOverText.setPosition(sf::Vector2f(window.getSize().x/2.0f, window.getSize().y/2.0f));

    window.draw(overlay);
    window.draw(gameOverText);
    window.display();

    sf::sleep(sf::seconds(2)); // show it for 2 seconds
}

void Game::endGame() {
    isPlaying = false;
    showGameOver();
}

bool Game::checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return rect1.intersects(rect2);
}

/*
 * This logic ensures that whenever a tile moves beyond a certain screen boundary (left, right, top, or bottom),
 * is "recycled" by
 * that it is moved to the opposite side. This makes the background look endless,
 * because as soon as one tile leaves the scene, it appears on the opposite side,
 * which creates the impression of a continuous space.
 */
void Game::updateBackground() {
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f cameraSize = camera.getSize();

    // edges, when to update tiles
    const float edgeThresholdX = tileWidth;
    const float edgeThresholdY = tileHeight;

    // camera movement
    sf::Vector2f cameraMovement = cameraCenter - previousCameraCenter;

    for (auto& tile : backgroundTiles) {
        sf::Vector2f newPosition = tile.getPosition() + cameraMovement;

        // updating tiles if outside the window
        if (newPosition.x + tileWidth < cameraCenter.x - (cameraSize.x / 2) - edgeThresholdX)
            newPosition.x += numberOfTilesX * tileWidth;
        else if (newPosition.x > cameraCenter.x + (cameraSize.x / 2) + edgeThresholdX)
            newPosition.x -= numberOfTilesX * tileWidth;


        if (newPosition.y + tileHeight < cameraCenter.y - (cameraSize.y / 2) - edgeThresholdY)
            newPosition.y += numberOfTilesY * tileHeight;
        else if (newPosition.y > cameraCenter.y + (cameraSize.y / 2) + edgeThresholdY)
            newPosition.y -= numberOfTilesY * tileHeight;

        tile.setPosition(newPosition);
    }

    // saving previous position of camera for next iteration
    previousCameraCenter = cameraCenter;
}

std::pair<float,float> Game::chooseRandomSideOfTheScreen(int spawnOffset, int spawnDistance) {
    //int spawnOffset = 500; // distance outside the window
    //int spawnDistance = 500; // static distance from player

    sf::Vector2f playerPosition = player.getGlobalPosition();

    // choosing side of screen to spawn alien
    int side = rand() % 4;

    float x = 0, y = 0;
    switch (side) {
        case 0: // upper
            x = playerPosition.x + (rand() % spawnDistance) - spawnDistance / 2;
            y = playerPosition.y - spawnOffset;
            break;
        case 1: // right
            x = playerPosition.x + spawnOffset;
            y = playerPosition.y + (rand() % spawnDistance) - spawnDistance / 2;
            break;
        case 2: // down
            x = playerPosition.x + (rand() % spawnDistance) - spawnDistance / 2;
            y = playerPosition.y + spawnOffset;
            break;
        case 3: // left
            x = playerPosition.x - spawnOffset;
            y = playerPosition.y + (rand() % spawnDistance) - spawnDistance / 2;
            break;
    }
    return { x, y };
}

void Game::spawnAlien() {
    int alienTypeChance = rand() % 100;

    std::unique_ptr<Alien> newAlien;

    if (alienTypeChance < 20) // 20 % chance for advanced alien
        newAlien = std::make_unique<AdvancedAlien>();
    else newAlien = std::make_unique<BasicAlien>();

    auto coordinates = chooseRandomSideOfTheScreen(600, 600);
    newAlien->setPosition(coordinates.first, coordinates.second);
    aliens.push_back(std::move(newAlien));
}

void Game::spawnHealthKit() {
    if (healthKitSpawnTimer.getElapsedTime() > healthKitSpawnInterval) {
        auto coordinates = chooseRandomSideOfTheScreen(300,300);
        sf::Vector2f spawnPosition(coordinates.first, coordinates.second);
        HealthKit newHealthKit(spawnPosition, healthBuff);
        healthKits.push_back(std::move(newHealthKit));
        healthKitSpawnTimer.restart();
    }
}

void Game::checkHealthKitsCollisions() {
    // checking collisions with enemies
    for (auto& alien : aliens) {
        sf::FloatRect alienBounds = alien->getBoundingBox();
        for (auto& kit : healthKits)
            if (kit.checkCollisionWithObject(alienBounds))
                kit.markForDeletion();

    }
    // checking collisions with enemy bullets
    for (auto& bullet : enemyBullets) {
        sf::FloatRect bulletBound = bullet.getBoundingBox();
        for (auto& kit : healthKits)
            if (kit.checkCollisionWithObject(bulletBound))
                kit.markForDeletion();
    }
}

void Game::updateHealthKits() {
    for (auto& kit : healthKits) {
        if (kit.checkCollisionWithObject(player.getCollisionMask())) {
            player.incrementHealth(kit.getHealthAmount());
            kit.markForDeletion();
        }
    }
    healthKits.erase(std::remove_if(healthKits.begin(), healthKits.end(),
                                    [](const HealthKit& kit) { return kit.isMarkedForDeletion(); }),
                     healthKits.end());
}

void Game::updateBullets(sf::Time deltaTime) {
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);

        sf::FloatRect bulletBounds = bullet.getBoundingBox();
        for (auto& alien : aliens) {
            sf::FloatRect alienBounds = alien->getBoundingBox();
            if (alien->isAlive() && checkCollision(bulletBounds, alienBounds)) {
                alien->takeDamage(player.getPlayerDamage()); // DAMAGE CAUSED BY BULLET
                if (!alien->isAlive())
                    aliensKilledInLevel += 1;
                bullet.markForDeletion(); // bullet to be deleted
            }
        }
    }

    // updating and controlling collisions with player
    for (EnemyBullet& enemyBullet : enemyBullets) {
        enemyBullet.update(deltaTime);
        if (enemyBullet.checkCollision(player.getCollisionMask())) {
            player.decrementHealth(enemyBullet.returnDamageAmount());
            if (!player.isAlive())
                endGame();
            enemyBullet.markForDeletion();
        }
    }
}

void Game::erasePlayerAndEnemyBullets() {
    // deleting bullets, if too far, or hit something
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [this](const Bullet& bullet) {
                                     return bullet.isMarkedForDeletion() ||
                                            bullet.isTooFarFrom(player.getGlobalPosition(), distanceForBulletsToDisappear);
                                 }),
                  bullets.end());

    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
                                      [this](const EnemyBullet& bullet) {
                                          return bullet.isMarkedForDeletion() ||
                                                bullet.isTooFarFrom(player.getGlobalPosition(), distanceForBulletsToDisappear);
                                      }),
                       enemyBullets.end());
}

void Game::eraseDeadAliens() {
    aliens.erase(std::remove_if(aliens.begin(), aliens.end(),
                                [](const std::unique_ptr<Alien>& alien) {
                                    return !alien->isAlive();
                                }),
                 aliens.end());
}

void Game::checkAlienCollisionWithPlayer(const std::unique_ptr<Alien>& alien) {
    if (alien->isAlive() && checkCollision(player.getCollisionMask(), alien->getBoundingBox())) {
        player.decrementHealth(/*damageAmount*/player.getMaxHealth()); // after collision -> kill the player
        if (!player.isAlive())
            endGame();
        alien->takeDamage(alienDamageTakenAfterCollision); // alien takes damage also
    }
}

void Game::updateEachAlien(sf::Time deltaTime) {
    for (auto& alien : aliens) {
        alien->update(deltaTime, player.getGlobalPosition());
        alien->shoot(player.getGlobalPosition(), enemyBullets);
        checkAlienCollisionWithPlayer(alien);
    }
}

void Game::updateTextOnScreen() {
    //sf::Vector2f globalPosition = player.getGlobalPosition();
    // TO DELETE LATER
    //playerPositionText.setString("X: " + std::to_string(globalPosition.x) + " Y: " + std::to_string(globalPosition.y));
    healthBarText.setString(createHealthBarString(player.getHealth(), player.getMaxHealth()));
    aliensKilledText.setString("Aliens killed: " + std::to_string(aliensKilledInLevel) + '/' + std::to_string(aliensToKillForNextLevel));
    levelText.setString("Level: " + std::to_string(level));
    int currentAmmo = player.getCurrentAmmo();
    int maxAmmo = player.getMaxAmmo();
    updateAmmoDisplay(currentAmmo, maxAmmo);
}

void Game::toggleGameMenu() {
    if (currentState == GameState::Playing)
        currentState = GameState::GameMenu;
    else if (currentState == GameState::GameMenu)
        currentState = GameState::Playing;
}

void Game::renderGameMenu() {
    if (currentState == GameState::GameMenu) {
        window.setView(window.getDefaultView());

        // semi transparent overlay
        overlay.setSize(static_cast<sf::Vector2f>(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150)); // semitransparent gray
        window.draw(overlay);

        drawGameMenu();
    }
}

void Game::update(sf::Time deltaTime) {
    if (currentState == GameState::Playing) {
        player.handleInput();
        player.update(deltaTime);

        updateBackground();

        camera.setCenter(player.getGlobalPosition());

        player.shoot(bullets); // creating bullets

        updateBullets(deltaTime);

        alienSpawnTimer += deltaTime;
        if (alienSpawnTimer >= alienSpawnInterval) {
            alienSpawnTimer = sf::Time::Zero; // timer reset
            spawnAlien();
        }

        updateEachAlien(deltaTime);

        erasePlayerAndEnemyBullets();
        eraseDeadAliens();

        updateTextOnScreen();

        spawnHealthKit();
        updateHealthKits();
        checkHealthKitsCollisions();

        checkLevelProgress();

        previousCameraCenter = camera.getCenter();
    }
}

void Game::updateAmmoDisplay(int currentAmmo, int maxAmmo) {
    std::string ammoString = "Ammo: [";
    for (int i = 0; i < maxAmmo; ++i)
        ammoString += i < currentAmmo ? "I" : " ";
    ammoString += "]";
    ammoDisplayText.setString(ammoString);
}

void Game::render() {
    window.setView(camera);
    window.clear();

    // rendering tiles
    for (const auto& tile : backgroundTiles)
        window.draw(tile);

    player.draw(window);

    for (const Bullet& bullet : bullets)
        bullet.draw(window);

    for (const EnemyBullet& bullet : enemyBullets)
        bullet.draw(window);

    for (const auto& alien : aliens)
        alien->draw(window);

    for (const HealthKit& kit : healthKits)
        kit.draw(window);

    window.setView(window.getDefaultView());
    window.draw(ammoDisplayText);

    window.draw(healthBarText);
    window.draw(aliensKilledText);
    window.draw(levelText);
    // position of text of player coordinates

    //playerPositionText.setPosition(window.getSize().x - 1000, 20);
    //window.draw(playerPositionText);

    if (currentState == GameState::GameMenu)
        renderGameMenu();

    // ......rendering objects......
    window.display();
}

void Game::initMenuItems() {
    sf::Text continueGame("Continue", font, fontSize);
    continueGame.setPosition(center.x, center.y - 20); // adjust as needed
    continueGame.setFillColor(sf::Color::Red); // highlight the first option by default
    menuItems.push_back(continueGame);

    sf::Text exitGame("Exit", font, fontSize);
    exitGame.setPosition(center.x, center.y + 20); // adjust as needed
    menuItems.push_back(exitGame);
}
void Game::drawGameMenu() {
    for (const auto& item : menuItems)
        window.draw(item);
}

void Game::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                moveUp();
                break;
            case sf::Keyboard::Down:
                moveDown();
                break;
            case sf::Keyboard::Enter:
                selectOption();
                break;
            case sf::Keyboard::Escape:
                currentState = GameState::Playing;
                break;
        }
    }
}

Game::Action Game::selectOption() {
    switch (selectedItemIndex) {
        case 0: // Continue
            currentState = GameState::Playing;
            return Action::Continue;
        case 1: // Exit
            isPlaying = false; // return to main menu
            return Action::Exit;
        default:
            return Action::None;
    }
}

void Game::moveUp() {
    if (selectedItemIndex > 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Game::moveDown() {
    if (selectedItemIndex < menuItems.size() - 1) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}