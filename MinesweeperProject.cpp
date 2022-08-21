#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Random.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



int main()
{
    
    Board board;
    bool def = true;
    
    board = board.insertBoardData("boards/config.cfg");

    // setting the dimensions for the board
    int width = board.GetColumn();
    float widthVideo = width * 32;
    int height = board.GetRow();
    float heightVideo = (height * 32) + 100;
    int mineCount = board.GetMineCount();
    int tileCount = height * width;


    
    cout << "Video dimensions: " << widthVideo << " , " << heightVideo << endl;

    cout << "Column and Height: " << board.GetColumn() << ", " << board.GetRow() << endl;

    // Board information

    cout << "Column count is: " << board.GetColumn() << endl;
    cout << "Row count is: " << board.GetRow() << endl;
    cout << "Mine count is: " << board.GetMineCount() << endl;
    cout << "Tile count is: " << tileCount << endl;
    cout << "Size of screen is: " << widthVideo << " x " << heightVideo << endl;

    sf::RenderWindow window(sf::VideoMode(widthVideo, heightVideo), "Minesweeper");



        board.setMenu(widthVideo, heightVideo);
        board.setTiles();
        board.setMines(mineCount);
        board.setNumber();
        board.setCounter(widthVideo, heightVideo);

        while (window.isOpen())
        {
            board.checkGameOver();
            board.checkGameWon();
            sf::Event event;
            while (window.pollEvent(event))

                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    // LEFT CLICK

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        cout << "Postion clicked: " << mousePosition.x << " ," << mousePosition.y << endl;
                        if (mousePosition.y <= (heightVideo - 100)) {

                            //CLICK ON TILE
                            if(!board.gameOver)
                                board.RevealTile(mousePosition.x, mousePosition.y);
                        }
                        if (board.debugSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            if (!board.gameOver && !board.gameWon) {
                                board.toggleDebug();
                            }
                        }
                        if (board.faceSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            board.gameRun = false;
                            cout << "Reset clicked" << endl;
                            board.reset();
                            
                        }
                        if (board.test1Sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            cout << "Test 1 Clicked" << endl;
                            board.testReset(1);
                        }
                        if (board.test2Sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                           board.testReset(2);

                        }
                        if (board.test3Sprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                           board.testReset(3);

                        }


                        //other test buttons and smiley
                    }



                    // RIGHT CLICK


                    if (event.mouseButton.button == sf::Mouse::Right) {
                        //flag it
                        if(!board.gameOver && !board.gameWon)
                            board.placeFlag(mousePosition.x, mousePosition.y);
                    }
                } break;


                default:
                    break;
                }




            window.clear();

            board.drawMenu(window);
            board.drawTiles(window);
            board.drawCounter(window);

            window.display();
        }

    

    return 0;
}