#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    sf::RenderWindow _window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture playButtonTexture;
    sf::Sprite playButtonSprite;
    sf::Texture playerVsPlayerButtonTexture;
    sf::Sprite playerVsPlayerButtonSprite;
    sf::Texture playerVsPcButtonTexture;
    sf::Sprite playerVsPcButtonSprite;

    bool inInitialScreen;
    bool inMainMenu;
    bool inPlayerVsPlayerScreen;
    bool inPlayerVsPCScreen;

    void initialize();
    void handleEvents();
    void render();
    void playerVsPlayerGame();
    void update();
};
