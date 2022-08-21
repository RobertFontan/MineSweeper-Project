#include "Tile.h"

Tile::Tile(int x, int y) {
	int width = x * 32;
	int height = y * 32;
	this->x = x;
	this->y = y;
	
	hidden.setPosition(width, height);
	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealed.setPosition(width, height);
	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	mine.setPosition(width, height);
	mine.setTexture(TextureManager::GetTexture("mine"));
	numAdj.setPosition(width, height);
	flagIcon.setTexture(TextureManager::GetTexture("flag"));
	flagIcon.setPosition(width, height); 
	_hasAdj = false;
	_hasMine = false;
	_hasFlag = false;
	_revealed = false;
	_hidden = true;
	mineClicked = false;
	
}

//Get Row/Column

int Tile::GetTilePosX() {
	return this->x;
}
int Tile::GetTilePosY() {
	return this->y;
}

// Sprites

sf::Sprite Tile::GetTile() {

	if (_revealed) {
		if (_hasMine) {
			return revealed;
		}
		return revealed;
	}
	else
		return hidden;
}
sf::Sprite Tile::GetFlag() {
	
	//_hasFlag = !_hasFlag;

	return flagIcon;
}
sf::Sprite Tile::GetMine() {
	return mine;
}
sf::Sprite Tile::GetNumAdj() {
	return numAdj;
}

//tile functions

void Tile::Reveal() {
	//cout << "Revealed Tile at: (" << GetTilePosX() << ", " << GetTilePosY() << ")" << endl;
	if (!_revealed && !_hasFlag) {
		_revealed = true;
		if (_hasMine) {
			cout << "Mine Clicked" << endl;
			mineClicked = true;

		}
		else {
			if (number == 0) {
				//cout << "made it here" << endl;
				for (int i = 0; i < 8; i++) {
					if (adjacentTiles[i] != nullptr && !(adjacentTiles[i]->_hasMine)) {
						adjacentTiles.at(i)->Reveal();
						//cout << "counter at: " << tile << endl;
					}
				}
			}
		}
	}
	

}

void Tile::placeFlag() {
	_hasFlag = !_hasFlag;
	
}
void Tile::placeNumAdj() {
	
	//cout << "Made it here!" << endl;
	//string imgName = "number_" + number;
	number = 0;
	for (unsigned int i = 0; i < 8; i++) {
		if (adjacentTiles.at(i) != nullptr && adjacentTiles.at(i)->_hasMine) {
			number++;
		}
	}
	if (number > 0) {
		_hasAdj = true;
		if (number == 1) {
			numAdj.setTexture(TextureManager::GetTexture("number_1"));
		}
		else if (number == 2) {
			numAdj.setTexture(TextureManager::GetTexture("number_2"));
		}
		else if (number == 3) {
			numAdj.setTexture(TextureManager::GetTexture("number_3"));

		}
		else if (number == 4) {
			numAdj.setTexture(TextureManager::GetTexture("number_4"));

		}
		else if (number == 5) {
			numAdj.setTexture(TextureManager::GetTexture("number_5"));

		}
		else if (number == 6) {
			numAdj.setTexture(TextureManager::GetTexture("number_6"));

		}
		else if (number == 7) {
			numAdj.setTexture(TextureManager::GetTexture("number_7"));

		}
		else if (number == 8) {
			numAdj.setTexture(TextureManager::GetTexture("number_8"));
		}
	}
	else {
		_hasAdj = false;
	}
}
void Tile::placeMine() {
	if(!_hasMine)
		_hasMine = true;
}
void Tile::DebugReveal() {
	cout << "Revealed Tile at (" << this->GetTilePosX() << " , " << this->GetTilePosY() << ")" << endl;
	
	_revealed = !_revealed;
	//_hidden = !_hidden;
	
	//_hasMine = !_hasMine;
	

	if (_hasMine)
		cout << "Has Mine!" << endl;
	else
		cout << "No Mine!" << endl;

	// if tile hasMine = gameover

}
