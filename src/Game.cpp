#include "Game.h"
#include <iostream>

#define BACKGROUND_IMAGE_PATH "./resources/background1.jpg"
#define BUTTON_PLAY_PATH "./resources/buttonPlay.png"
#define BUTTON_PLAYER_VS_PLAYER_PATH "./resources/buttonPlayerVsPlayer.png"
#define BUTTON_PLAYER_VS_PC_PATH "./resources/buttonPlayerVsPC.png"
#define BUTTON_START_GAME_PATH "./resources/start.png"
#define UNO_BUTTON_IMAGE_PATH "./resources/UnoButton.png"
#define BACKGROUND_IMAGE_PATH2 "./resources/background2.jpg"


Game::Game() : _window(sf::VideoMode(1280, 720), "UNO Game") {
    // Initialize screen states
    inInitialScreen = true;
    inMainMenu = false;
    inPlayerVsPlayerScreen = false;
    inPlayerVsPCScreen = false;
    gameStarted = false;

    currentTurn = 0;


    mainDeck.fillDeck();
    mainDeck.shuffle();
    stashDeck.initializeStash(mainDeck);
   
    // Set frame rate limit
    _window.setFramerateLimit(15);

    // Load textures
    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
    backgroundTexture2.loadFromFile(BACKGROUND_IMAGE_PATH2);
    playButtonTexture.loadFromFile(BUTTON_PLAY_PATH);
    playerVsPlayerButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PLAYER_PATH);
    playerVsPcButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PC_PATH);
    startButtonTexture.loadFromFile(BUTTON_START_GAME_PATH);
    unoButtonTexture.loadFromFile(UNO_BUTTON_IMAGE_PATH);

    // Configure sprites
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture2);

    unoButtonSprite.setTexture(unoButtonTexture);
    unoButtonSprite.setPosition(300, 100);

    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(580, 360);
    playButtonSprite.setScale(0.7f, 0.7f);

    playerVsPlayerButtonSprite.setTexture(playerVsPlayerButtonTexture);
    playerVsPlayerButtonSprite.setPosition(550, 220);

    playerVsPcButtonSprite.setTexture(playerVsPcButtonTexture);
    playerVsPcButtonSprite.setPosition(550, 400);

    startButtonSprite.setTexture(startButtonTexture);
    startButtonSprite.setPosition(600, 220);
    startButtonSprite.setScale(0.2f, 0.2f);
}

Game::~Game() {
}



void Game::handleEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (inInitialScreen) {
                if (playButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    inInitialScreen = false; 
                    inMainMenu = true;
                   
                }
            }
            else if (inMainMenu) {
                if (playerVsPlayerButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                   
                    inMainMenu = false;
                    inPlayerVsPlayerScreen = true;
                    gameStarted = true;
                }
                else if (inPlayerVsPCScreen) {
                    
                    // Handle in-game events for player vs. PC
                }
            }
      // Llama a la función específica para el modo jugador contra jugad
        }
    }
}




void Game::InitializeGame() {
    // Initialize the game state
}

void Game::nextTurn() {


}
void Game::HandleInGamePVP(sf::RenderWindow& window) {
    
    // CREATE A TURN VARIABLE TO KEEP TRACK OF THE CURRENT TURN
    int turn = 1;

    // CREATE A BOOLEAN VARIABLE TO KEEP TRACK OF THE GAME OVER STATE
    bool gameOver = false;

    // CREATE A PLAYER OBJECT AND AN ENTITY OBJECT IN ORDER TO PLAY THE GAME
    Player player;
    Player entity;

    // DRAW 7 CARDS FOR THE PLAYER AND THE ENTITY
    player.drawInitialHand(mainDeck, 7);
    entity.drawInitialHand(mainDeck, 7);

    // Create the button
    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("resources\\EatButton.png");
        // Handle the case where loading the image failed
        // You can add error handling here
    

    sf::Sprite eatButton(buttonTexture);
    eatButton.setPosition(040, 550);
    eatButton.setScale(0.1f, 0.1f);

  

    // START THE GAME LOOP
    while (window.isOpen() && !gameOver) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Button click detection
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (eatButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        // The button was clicked, eat (draw) a card from the main deck
                        Card drawnCard = mainDeck.drawCard();
                        if (turn % 2 == 0) {
                            entity.addCardToHand(drawnCard);
                            
                        }
                        else {
                            player.addCardToHand(drawnCard);

                        }
                    }
                }
            }
        }

        // CHECK IF THE PLAYER'S TURN IS OVER
        if (turn % 2 == 0) {
            window.clear();
            
            window.draw(backgroundSprite2);
            player.handleHand(window, false, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck);
            entity.handleHand(window, true, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck);
        }
        else {
            window.clear();
            
            window.draw(backgroundSprite2);
            player.handleHand(window, true, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck);
            entity.handleHand(window, false, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck);
        }

        // Draw the button
        window.draw(eatButton);

        stashDeck.displayDeck(window, 640.0, 360.0); // Display the stash deck
    

        // DISPLAY THE MAIN WINDOW
        window.display();

        // GAME OVER LOGIC (CURRENTLY ONLY CHECKS IF THE PLAYER'S HAND IS EMPTY)
        if (player.getHandSize() == 1) {
            gameOver = true;
        }
    }

    // GAME OVER SCREEN
    window.clear();
}

void Game::handleInGamePVE(sf::RenderWindow& window) {

}





void Game::render() {
    _window.clear();
   
    

    if (inInitialScreen) {
        _window.draw(backgroundSprite);
        _window.draw(playButtonSprite);
    }
    else if (inMainMenu) {
        _window.draw(backgroundSprite);
        _window.draw(playerVsPlayerButtonSprite);
        _window.draw(playerVsPcButtonSprite);
    }
    else if (inPlayerVsPlayerScreen) {


        _window.draw(backgroundSprite2);
        
        HandleInGamePVP(_window);
        
        _window.display();


    }
    else if (inPlayerVsPCScreen) {
        // Handle in-game rendering for player vs. PC
    }

    _window.display();
}

void Game::run() {
    InitializeGame();
    
    while (_window.isOpen()) {
        handleEvents();
        render();

       
    }
}

