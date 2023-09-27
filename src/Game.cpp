#include "Game.h"

#define BACKGROUND_IMAGE_PATH "./resources/background1.jpg"
#define BUTTON_PLAY_PATH "./resources/buttonPlay.png"
#define BUTTON_PLAYER_VS_PLAYER_PATH "./resources/buttonPlayerVsPlayer.png"
#define BUTTON_PLAYER_VS_PC_PATH "./resources/buttonPlayerVsPC.png"
#define BUTTON_START_GAME_PATH "./resources/start.png"



Game::Game() : _window(sf::VideoMode(1280, 720), "UNO Game") {
    // Initialize screen states
    inInitialScreen = true;
    inMainMenu = false;
    inPlayerVsPlayerScreen = false;
    inPlayerVsPCScreen = false;
    gameStarted = false;

    currentTurn = 0;



   
    // Set frame rate limit
    _window.setFramerateLimit(15);

    // Load textures
    backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
    playButtonTexture.loadFromFile(BUTTON_PLAY_PATH);
    playerVsPlayerButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PLAYER_PATH);
    playerVsPcButtonTexture.loadFromFile(BUTTON_PLAYER_VS_PC_PATH);
    startButtonTexture.loadFromFile(BUTTON_START_GAME_PATH);

    // Configure sprites
    backgroundSprite.setTexture(backgroundTexture);

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

    // CREATE A DECK OBJECT AND FILL IT WITH CARDS AND SHUFFLE IT
    Deck mainDeck;
    mainDeck.fillDeck();
    mainDeck.shuffle();

    Deck stashDeck;


    // CREATE A PLAYER OBJECT AND AN ENTITY OBJECT IN ORDER TO PLAY THE GAME
    Player player;
    Player entity;

    // DRAW 7 CARDS FOR THE PLAYER AND THE ENTITY
    player.drawInitialHand(mainDeck, 7);
    entity.drawInitialHand(mainDeck, 7);

    // START THE GAME LOOP
    while (window.isOpen() && !gameOver) {
        //std::cout << "Current turn: " << turn << std::endl;	
        // CHECK IF THE PLAYER'S TURN IS OVER
        if (turn % 2 == 0) {
            window.clear();
            _window.draw(backgroundSprite);
            
            player.handleHand(window, false, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
            entity.handleHand(window, true, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS CONTROLLABLE


        }
        else {
            window.clear();
            _window.draw(backgroundSprite);
           
            player.handleHand(window, true, turn, player.getHand(), entity.getHand(), stashDeck, mainDeck); // DISPLAY THE PLAYER'S HAND AS CONTROLLABLE
            entity.handleHand(window, false, turn, entity.getHand(), player.getHand(), stashDeck, mainDeck); // DISPLAY THE ENTITY'S HAND AS NOT CONTROLLABLE (OFFSET BY 22.0, 7.0) ->AND SCALE BY 0.5 BY DEFAULT<-
        }

        // DISPLAY THE MAIN DECK AS DEBUG 
        //mainDeck.displayDeck(window, 22.0, 90.0); // Display the main deck

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


void Game::render() {
    _window.clear();
    _window.draw(backgroundSprite);

    if (inInitialScreen) {
        _window.draw(playButtonSprite);
    }
    else if (inMainMenu) {
        _window.draw(playerVsPlayerButtonSprite);
        _window.draw(playerVsPcButtonSprite);
    }
    else if (inPlayerVsPlayerScreen) {
		// Handle in-game rendering for player vs. player
		_window.draw(backgroundSprite);
        HandleInGamePVP(_window);
        
        _window.draw(backgroundSprite);

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

