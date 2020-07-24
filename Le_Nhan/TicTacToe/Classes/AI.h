#pragma once
#include "cocos2d.h"
#include <vector>
#include <array>

using namespace std;


class AI
{
public:
	AI(int playerPiece);
	void PlacePiece(int ( *gridArray)[3][3], cocos2d::Sprite* gridSprite[3][3], int* gameState);

private:
	void checkSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3]);
	void checkIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3]);
	
	int aiPieces;
	int playerPiece;

	vector<array<int, 6>> checkMathVector;
};