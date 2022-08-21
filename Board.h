#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "Tile.h"
#include "Random.h"
using namespace std;
class Board 
{
    int winCondition;
    int columnCount;
    int rowCount;
    int mineCount;
    int updateNum = 0;
    bool debug = false;
    bool _isNegative = false;


    // menu
    sf::Sprite faceButton;
    sf::Sprite faceLose;
    sf::Sprite faceWin;
    sf::Sprite test1Button;
    sf::Sprite test2Button;
    sf::Sprite test3Button;
    sf::Sprite debugButton;
    

    // counter
    sf::Sprite negative;
    sf::Sprite tens;
    sf::Sprite ones;

public:
    vector <Tile> gameTiles;
    vector <int> binaryTiles;
    bool gameOver = false;
    bool gameWon = false;
    bool gameRun = true;

    Board();
    Board(int columnCount, int rowCount, int mineCount);

    //base game functions

    void setTiles();
    Board insertBoardData(string filePath);
    void setMenu(float width, float height);
    void setMines(int amtBombs);
    void toggleDebug();
    void setNumber();
    void checkGameOver();
    void checkGameWon();
    void reset();
    void setCounter(float width, float height);
    void updateCounter(int counter);

    // getting things from board
    int GetColumn();
    int GetRow();
    int GetMineCount();
    float GetWidth();
    float GetHeight();
    
    // clickable buttons
    
    sf::Sprite faceSprite();

    sf::Sprite test1Sprite();
    sf::Sprite test2Sprite();
    sf::Sprite test3Sprite();
    sf::Sprite debugSprite();


    //drawing 
    void drawMenu(sf::RenderWindow &window);
    void drawTiles(sf::RenderWindow& window);
    void drawCounter(sf::RenderWindow& window);

    //Clicking functions
    void RevealTile(float x, float y);
    void placeFlag(float x, float y);

    //dumb testboard
    Board testBoardData(string filePath);
    void setTestMines();
    void testReset(int testNum);
};