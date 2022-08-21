#include "Board.h"

Board::Board() {
	columnCount = 0;
	rowCount = 0;
	mineCount = 0;

}
Board::Board(int columnCount, int rowCount, int mineCount) {
	this->columnCount = columnCount;
	this->rowCount = rowCount;
	this->mineCount = mineCount;
}

// setting up the game

Board Board::insertBoardData(string filePath) {
    ifstream file(filePath);
    if (file.is_open()){
        int value;
        vector <int> values;
        Board tempBoard;
        while (file >> value) {
            values.push_back(value);
        }
        tempBoard.columnCount = values.at(0);
        
        tempBoard.rowCount = values.at(1);
        tempBoard.mineCount = values.at(2);
        
        return tempBoard;
}
    else
    {
        cout << "file did not open" << endl;
    }

};
void Board::setMenu(float width, float height) {
    faceButton.setTexture(TextureManager::GetTexture("face_happy"));
    faceButton.setOrigin(32, 32);
    faceButton.setPosition((width / 2), (height - 68));

    faceLose.setTexture(TextureManager::GetTexture("face_lose"));
    faceLose.setOrigin(32, 32);
    faceLose.setPosition((width / 2), (height - 68));

    faceWin.setTexture(TextureManager::GetTexture("face_win"));
    faceWin.setOrigin(32, 32);
    faceWin.setPosition((width / 2), (height - 68));

    test1Button.setTexture(TextureManager::GetTexture("test_1"));
    test1Button.setOrigin(32, 32);
    test1Button.setPosition((width - 160), (height - 68));
    
    test2Button.setTexture(TextureManager::GetTexture("test_2"));
    test2Button.setOrigin(32, 32);
    test2Button.setPosition((width - 96) , (height - 68));

    test3Button.setTexture(TextureManager::GetTexture("test_3"));
    test3Button.setOrigin(32, 32);
    test3Button.setPosition((width - 32), (height - 68));

    debugButton.setTexture(TextureManager::GetTexture("debug"));
    debugButton.setOrigin(32, 32);
    debugButton.setPosition((width - 224), (height - 68));

    

 

}
void Board::toggleDebug() {
    cout << "Debug Toggled" << endl;    
    debug = !debug;
   
}
void Board::setMines(int amtBombs) {
    int counter = 0;
    int mineAmt = 0;
    int mineTile;
    //vector <int> RandomNumberList;
    for (unsigned int i = 0; i < amtBombs; i++) {
        mineTile = Random::Int(0, gameTiles.size() - 1);

       /* if (gameTiles.at(mineTile)._hasMine) {
            mineTile == Random::Int(0, gameTiles.size() - 1);
        }*/

        while (gameTiles.at(mineTile)._hasMine) {
            mineTile = Random::Int(0, gameTiles.size() - 1);
            //counter++;
        }
        //RandomNumberList.push_back(mineTile);
        /*
        for (unsigned int z = 0; z < RandomNumberList.size(); z++) {
            for (unsigned int k = RandomNumberList.size() - 1; k >= 0; k--) {
                if (RandomNumberList.at(z) == RandomNumberList.at(k))
                    cout << "Match Found at z: " << z << " and k: " << k << endl;
            }
        }
    */
       /* for (unsigned int z = 0; z < RandomNumberList.size() - 1 ; z++) {
            if (mineTile == RandomNumberList.at(z)) {
                mineTile = Random::Int(0, gameTiles.size() - 1);
                cout << "AHHHHH Match found" << endl;
            }
        }*/

        gameTiles.at(mineTile).placeMine();
       // cout << "Minetile at: " << mineTile << " For loop at: " << counter << endl;
        /*if (!gameTiles.at(mineTile)._hasMine) {
            gameTiles.at(mineTile).placeMine();
        }
        else
            continue;*/
    }
    for (unsigned int j = 0; j < gameTiles.size(); j++) {
        if (gameTiles.at(j)._hasMine) {
            mineAmt++;
            //cout << "Mine at!: " << j << endl;
        }
    }

    winCondition = gameTiles.size() - amtBombs;
   // cout << "Amount Put IN: " << amtBombs << endl;

    //cout << "Amount repeated in the for: " << counter << endl;
   // cout << "amount of mines: " << mineAmt << endl;
}
void Board::setTiles() {
    gameTiles.clear();
    for (int i = 0; i < columnCount; i++){
        for (int k = 0; k < rowCount; k++) {
            Tile tempTile(i, k);

            gameTiles.push_back(tempTile);
            
        }
    }
}
void Board::drawMenu(sf::RenderWindow &window) {
    if (gameOver) {
        window.draw(faceLose);


        //cout << "drawing lose face" << endl;

    }
    else if (gameWon) {
        window.draw(faceWin);
    }
    else
        window.draw(faceButton);
    //window.draw(faceButton);

    window.draw(test1Button);
    window.draw(test2Button);
    window.draw(test3Button);
    window.draw(debugButton);
    

}
void Board::drawCounter(sf::RenderWindow& window) {
    window.draw(tens);
    window.draw(ones);
    window.draw(negative);
    
}
void Board::drawTiles(sf::RenderWindow& window) {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        window.draw(gameTiles.at(i).GetTile());
        
        if (gameTiles.at(i)._revealed){
            if (gameTiles.at(i)._hasMine) {
                window.draw(gameTiles.at(i).GetMine());
            }
      
            else if (gameTiles.at(i)._hasAdj) {
                window.draw(gameTiles.at(i).GetNumAdj());
            }
        }
        else if (gameTiles.at(i)._hasFlag) {
            window.draw(gameTiles.at(i).GetFlag());
        }
        if (gameOver) {
            if (gameTiles.at(i)._hasMine)
                window.draw(gameTiles.at(i).GetMine());
        }
        else {
            if (debug) {
                if (gameTiles.at(i)._hasMine)
                    window.draw(gameTiles.at(i).GetMine());
            }
        }
    }
}
void Board::RevealTile(float x, float y) {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        if (gameTiles.at(i).GetTile().getGlobalBounds().contains(x, y)) {
            //int tile = 0;
            gameTiles.at(i).Reveal();
            cout << "Tile Clicked in Vector: " << i << endl;
        }
    }
}
void Board::placeFlag(float x, float y) {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        if (gameTiles.at(i).GetFlag().getGlobalBounds().contains(x, y)) {
            if (!gameTiles.at(i)._revealed) {
                gameTiles.at(i).placeFlag();
                cout << "Flag in vector: " << i << endl;
                if (gameTiles.at(i)._hasFlag) {
                    updateNum--;
                }
                else
                    updateNum++;
            }
        }
    }
    cout << "New Counter at: " << updateNum << endl;
    updateCounter(updateNum);
}
void Board::setCounter(float width, float height) {
    updateNum = 0;
    int counter = 0;
    for (unsigned int c = 0; c < gameTiles.size(); c++) {
        if (gameTiles.at(c)._hasMine) {
            counter++;
        }
    }

   cout << "Inital Counter At: " << counter << endl;
  

   int onesDigit = counter % 10;
   counter /= 10;
   int tensDigit = counter % 10;
   counter /= 10;
   int hundDigit = counter & 10;

   /*cout << "Ones: " << onesDigit << endl;
   cout << "Tens: " << tensDigit << endl;
   cout << "Hund: " << hundDigit << endl;*/

   negative.setTexture(TextureManager::GetTexture("digits"));
   negative.setTextureRect(sf::IntRect(21* hundDigit, 0, 21, 32));
   negative.setPosition(0, height - 100);

   tens.setTexture(TextureManager::GetTexture("digits"));
   tens.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));
   tens.setPosition(21, height - 100);

   ones.setTexture(TextureManager::GetTexture("digits"));
   ones.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));
   ones.setPosition(42, height - 100);

  

}
void Board::updateCounter(int counter) {
    int maxFlags = 0;
    for (unsigned int c = 0; c < gameTiles.size(); c++) {
        if (gameTiles.at(c)._hasMine) {
            maxFlags++;
        }
    }
    int hundDigit = maxFlags;
    if (maxFlags > 100) {
        hundDigit = 1;
    }
    else if (maxFlags < 100 && maxFlags > 0) {
        hundDigit = 0;
    }
    maxFlags = maxFlags + counter;
    int onesDigit;
    int tensDigit;
    //int hundDigit = 0;
    //cout << "max Flags" << maxFlags << endl;
    if (maxFlags > 0) {

        onesDigit = maxFlags % 10;
        maxFlags /= 10;
        tensDigit = maxFlags % 10;
        maxFlags /= 10;
        hundDigit = maxFlags % 10;
        _isNegative = false;
      

    }
    else {
        maxFlags = maxFlags * -1;
        onesDigit = maxFlags % 10;
        maxFlags /= 10;
        tensDigit = maxFlags % 10;
        _isNegative = true;
        negative.setTextureRect(sf::IntRect(210, 0, 21, 32));
        hundDigit = 10;
    }
    //cout << "nOnes: " << onesDigit << endl;
    //cout << "nTens: " << tensDigit << endl;
    //cout << "nHund: " << hundDigit << endl;

    if(!_isNegative)
        negative.setTextureRect(sf::IntRect(21 * hundDigit, 0, 21, 32));

    tens.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));

    ones.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));

}
void Board::setNumber() {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        gameTiles[i].adjacentTiles.clear();
        for (unsigned int j = 0; j < 8; j++) {
            gameTiles.at(i).adjacentTiles.push_back(nullptr);
        }
        /*
            0 1 2
            3 * 4
            5 6 7

            */
        // top left
        if (i == 0) {
            //right
            gameTiles.at(i).adjacentTiles.at(4) = &(gameTiles.at(i + GetRow()));
            //bot
            gameTiles.at(i).adjacentTiles.at(6) = &(gameTiles.at(i + 1));
            
            gameTiles.at(i).adjacentTiles.at(7) = &(gameTiles.at(i + GetRow() + 1));
            
        }
        // top right
        else if (i == (gameTiles.size() - GetRow())) {
            //bot
            gameTiles.at(i).adjacentTiles.at(6) = &(gameTiles.at(i + 1));
            //left
            gameTiles.at(i).adjacentTiles.at(3) = &(gameTiles.at(i - GetRow()));

            gameTiles.at(i).adjacentTiles.at(5) = &(gameTiles.at(i - GetRow() + 1));


        }
        // bot left
        else if (i == GetRow() - 1) {
            //top
            gameTiles.at(i).adjacentTiles.at(1) = &(gameTiles.at(i - 1));

            //right
            gameTiles.at(i).adjacentTiles.at(4) = &(gameTiles.at(i + GetRow()));

            gameTiles.at(i).adjacentTiles.at(2) = &(gameTiles.at(i + GetRow() - 1));

        }

        //bot right

        else if (i == (gameTiles.size() - 1)) {
            //top
            gameTiles.at(i).adjacentTiles.at(1) = &(gameTiles.at(i - 1));
            //left
            gameTiles.at(i).adjacentTiles.at(3) = &(gameTiles.at(i - GetRow()));

            gameTiles.at(i).adjacentTiles.at(0) = &(gameTiles.at(i - GetRow() - 1));

        }

        // top row
        else if (i % GetRow() == 0) {
            gameTiles.at(i).adjacentTiles.at(5) = &(gameTiles.at(i - GetRow() + 1));
            gameTiles.at(i).adjacentTiles.at(6) = &(gameTiles.at(i + 1));
            gameTiles.at(i).adjacentTiles.at(7) = &(gameTiles.at(i + GetRow() + 1));
            gameTiles.at(i).adjacentTiles.at(4) = &(gameTiles.at(i + GetRow()));
            gameTiles.at(i).adjacentTiles.at(3) = &(gameTiles.at(i - GetRow()));
        }
        else if (i < GetRow()) {
            gameTiles.at(i).adjacentTiles.at(2) = &(gameTiles.at(i + GetRow() - 1));
            gameTiles.at(i).adjacentTiles.at(7) = &(gameTiles.at(i + GetRow() + 1));
            gameTiles.at(i).adjacentTiles.at(4) = &(gameTiles.at(i + GetRow()));
            gameTiles.at(i).adjacentTiles.at(1) = &(gameTiles.at(i - 1));
            gameTiles.at(i).adjacentTiles.at(6) = &(gameTiles.at(i + 1));

        }

        // bot row
        else if ((i - (GetRow() - 1)) % GetRow() == 0) {
            gameTiles.at(i).adjacentTiles.at(1) = &(gameTiles.at(i - 1));
            gameTiles.at(i).adjacentTiles.at(2) = &(gameTiles.at(i + GetRow() - 1));
            gameTiles.at(i).adjacentTiles.at(0) = &(gameTiles.at(i - GetRow() - 1));
            gameTiles.at(i).adjacentTiles.at(4) = &(gameTiles.at(i + GetRow()));
            gameTiles.at(i).adjacentTiles.at(3) = &(gameTiles.at(i - GetRow()));
        }

        //left col
        
        //right col
        else if (i > (gameTiles.size() - GetRow())) {
            gameTiles.at(i).adjacentTiles.at(0) = &(gameTiles.at(i - GetRow() - 1));
            gameTiles.at(i).adjacentTiles.at(5) = &(gameTiles.at(i - GetRow() + 1));
            gameTiles.at(i).adjacentTiles.at(3) = &(gameTiles.at(i - GetRow()));
            gameTiles.at(i).adjacentTiles.at(1) = &(gameTiles.at(i - 1));
            gameTiles.at(i).adjacentTiles.at(6) = &(gameTiles.at(i + 1));

        }
        else {
            gameTiles.at(i).adjacentTiles.at(7) = &(gameTiles.at(i + GetRow() + 1));
            gameTiles.at(i).adjacentTiles.at(0) = &(gameTiles.at(i - GetRow() - 1));
            gameTiles.at(i).adjacentTiles.at(5) = &(gameTiles.at(i - GetRow() + 1));
            gameTiles.at(i).adjacentTiles.at(3) = &(gameTiles.at(i - GetRow()));
            gameTiles.at(i).adjacentTiles.at(1) = &(gameTiles.at(i - 1));
            gameTiles.at(i).adjacentTiles.at(2) = &(gameTiles.at(i + GetRow() - 1));
            gameTiles.at(i).adjacentTiles.at(4) = &(gameTiles.at(i + GetRow()));
            gameTiles.at(i).adjacentTiles.at(6) = &(gameTiles.at(i + 1));
        }
        gameTiles.at(i).placeNumAdj();
    }
}
void Board::checkGameOver() {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        if (gameTiles.at(i).mineClicked) {
            gameOver = true;
            //cout << "Board registers gameOver" << endl;
        }
    }
}
void Board::checkGameWon() {
    int revealedTileCount = 0;
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        if (gameTiles.at(i)._revealed) {
            if (!debug) {
                revealedTileCount++;
            }
        }
    }
    //cout << "Revealed Tile Count:" << revealedTileCount << endl;
    if (revealedTileCount == winCondition) {
        gameWon = true;
        //cout << "Board Registered Win" << endl;
    }
}
void Board::reset() {
    cout << "Board Registered Reset" << endl;
    gameTiles.clear();
    if (gameOver) {
        gameOver = false;
    }
    if (debug) {
        debug = false;
    }
    if (gameWon) {
        gameWon = false;
    }
    gameRun = false;
    setTiles();
    setMines(GetMineCount());
    setNumber();
    setCounter(GetWidth(), GetHeight());
    updateCounter(0);
}

//Getting aspects of the board

int Board::GetColumn() {
    return this->columnCount;
}
int Board::GetRow() {
    return this->rowCount;
}
int Board::GetMineCount() {
    return this->mineCount;
}
float Board::GetWidth() {
    //cout << "widht runnnig";
    float width = this->columnCount * 32;
    //cout << width;
    return width;
}
float Board::GetHeight() {
    float height = (this->rowCount * 32) + 100;
   // cout << "height: " << height << endl;
    return height;
}

// Button Sprites

sf::Sprite Board::debugSprite() {
    return debugButton;

}
sf::Sprite Board::faceSprite() {
    if (gameOver) {
        return faceLose;
    }
    else
        return faceButton;
}
sf::Sprite Board::test1Sprite() {
    return test1Button;
}
sf::Sprite Board::test2Sprite() {
    return test2Button;

}
sf::Sprite Board::test3Sprite() {
    return test3Button;

}



//dumb test
Board Board::testBoardData(string filePath) {
    gameTiles.clear();
    binaryTiles.clear();
    fstream file;
    string line;
    int c = 0;
    int p = 0;
    file.open(filePath);
   // cout << "made it here" << endl;
    if (file.is_open()) {
        Board tempBoard;

        while (getline(file,line)){
            auto iter = line.begin();
            while (iter != line.end()) {
                int temp = (*iter) - 48;
             
                binaryTiles.push_back(temp);

                iter++;
                
            }
            //cout << line << endl;

        }
        cout << "Testing Board: " << filePath << endl;
        tempBoard.columnCount = 25;
        tempBoard.rowCount = 16;
        tempBoard.mineCount = c;
        return tempBoard;
    }
    else {
        cout << "test file could not be open" << endl;
    }
    //file.close();
    for (unsigned i = 0; i < binaryTiles.size(); i++) {
        if (binaryTiles.at(i) == 1) {
            c++;
        }
    }
    file.close();
}
void Board::setTestMines() {
    int winC = 0;
    for (unsigned int i = 0; i < 400; i++) {
        int row = 0;
        int col = 0;
        if (binaryTiles.at(i) == 1){
            int f = i;
            while (f % 25 != 0) {
                f--;
                row++;
            }
            col = f / 25;

            for (unsigned int i = 0; i < gameTiles.size(); i++) {
                if (gameTiles.at(i).GetTilePosX() == row) {
                    if (gameTiles.at(i).GetTilePosY() == col) {
                        gameTiles.at(i).placeMine();
                    }
                }

            }

            
            
            //gameTiles.at(i).placeMine();
           /* cout << "Col: " << gameTiles.at(i).GetTilePosX() << " Row: " << gameTiles.at(i).GetTilePosY() << endl;
            cout << "Vector: " << i << endl;*/
            winC++;
        }
    }
    //for (unsigned int c = 0; c < gameTiles.size(); c++) {
    //    if (gameTiles.at(c)._hasMine) {
    //        //winC++;
    //    }
    //}
    winCondition = gameTiles.size() - winC;
    //cout << "Mine count: " << mineCount << endl;
    cout << "Win cond: " << winCondition << endl;
}
void Board::testReset(int testNum) {
    cout << "Board Registered Reset" << endl;
    gameTiles.clear();
    if (gameOver) {
        gameOver = false;
    }
    if (debug) {
        debug = false;
    }
    if (gameWon) {
        gameWon = false;
    }
    gameRun = false;

    if (testNum == 1) {
        testBoardData("boards/testboard1.brd");

    }
    else if (testNum == 2) {
        testBoardData("boards/testboard2.brd");

    }
    else if (testNum == 3) {
        testBoardData("boards/testboard3.brd");

    }
    cout << "Testing Board: " << testNum << endl;

    setTiles();
    setTestMines();
    setNumber();
    setCounter(GetWidth(), GetHeight());
    updateCounter(0);
  

}