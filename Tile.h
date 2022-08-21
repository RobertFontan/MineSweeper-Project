#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Tile
{
	sf::Sprite hidden;

	sf::Sprite revealed;
	sf::Sprite mine;
	sf::Sprite numAdj;
	sf::Sprite flagIcon;

	int number;
	bool _hasMine;
	bool _hasFlag;
	bool _revealed;
	bool _hidden;
	bool _hasAdj;
	int x;
	int y;

	bool mineClicked;

	
	vector <Tile*> adjacentTiles;

	Tile(int x, int y);

	int GetTilePosX();
	int GetTilePosY();

	sf::Sprite GetTile();
	sf::Sprite GetFlag();
	sf::Sprite GetNumAdj();
	sf::Sprite GetMine();




	void placeNumAdj();
	void placeMine();
	void Reveal();
	void placeFlag();
	void DebugReveal();
	void RevealMine();



};

