#include "Game.h"
#include <iostream>


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

    buttonSoundBuffer.loadFromFile(BUTTON_SOUND_PATH);
    buttonSound.setBuffer(buttonSoundBuffer);

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
                    buttonSound.play();
                    inInitialScreen = false; 
                    inMainMenu = true;
                   
                }
            }
            else if (inMainMenu) {
                if (playerVsPlayerButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    buttonSound.play();
                    inMainMenu = false;
                    inPlayerVsPlayerScreen = true;
                    gameStarted = true;
                }
                else if (playerVsPcButtonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    buttonSound.play();
                    std::cout<<"Player vs PC"<<std::endl;
                    inMainMenu = false;
                    inPlayerVsPCScreen = true;
                    gameStarted = true;
                }

            }
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

void Game::handleEatButton() {
    int turn = 1;  
    if (player.getHandSize() < 18) {  
        Card drawnCard = mainDeck.drawCard();
        if (turn % 2 == 0) {  // Entity's turn
            
        }
        else {  // Player's turn
            player.addCardToHand(drawnCard);
        }
        totalDrawnCards++;
        turn++;
    }
}

void Game::handleInGamePVE(sf::RenderWindow& window) {
    int turn = 1;
    bool gameOver = false;
    int totalDrawnCards = 0;  // Track the total number of drawn cards



    player.drawInitialHand(mainDeck, 7);
    entity.drawInitialHand(mainDeck, 7);

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("resources/EatButton.png");
    sf::Sprite eatButton(buttonTexture);
    eatButton.setPosition(040, 550);
    eatButton.setScale(0.1f, 0.1f);

    while (window.isOpen() && !gameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (eatButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        handleEatButton();
                    }
                }
            }
        }

        // Simple AI logic
        if (entity.getHandSize() < 3) {
            Card drawnCard = mainDeck.drawCard();
            entity.addCardToHand(drawnCard);
            turn++;
        }

        
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

        window.draw(eatButton);
        stashDeck.displayDeck(window, 640.0, 360.0);

        window.display();

        if (player.getHandSize() == 1) {
            gameOver = true;
        }
    }

    window.clear();
}

void Game::initializeUnoButton() {
    unoButtonTexture.loadFromFile("resources\\UnoButton.png");
    unoButtonSprite.setTexture(unoButtonTexture);
    unoButtonSprite.setPosition(500, 550); 
    unoButtonSprite.setScale(0.1f, 0.1f); 
}

bool Game::shouldDisplayUnoButton() {
    return player.getHandSize() == 1 || entity.getHandSize() == 1;
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
        _window.draw(unoButtonSprite);
        
        HandleInGamePVP(_window);
        
        _window.display();


    }
    else if (inPlayerVsPCScreen) {

	   _window.draw(backgroundSprite2);
		handleInGamePVE(_window);

        if (shouldDisplayUnoButton()) {
            _window.draw(unoButtonSprite);
        }
        
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

