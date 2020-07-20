#include "AI.h"
#include "proj.win32/Definition.h"

#include<iostream>
using namespace std;

AI::AI(int playerPiece)
{
	this->playerPiece = playerPiece;

	if (O_PIECE == playerPiece)
	{
		aiPieces = X_PIECE;
	}
	else
	{
		aiPieces = O_PIECE;
	}


	checkMathVector.push_back({ 0, 0, 0, 1, 0, 2 });
	checkMathVector.push_back({ 0, 0, 1, 0, 2, 0 });
	checkMathVector.push_back({ 0, 0, 1, 1, 2, 2 });
	checkMathVector.push_back({ 2, 0, 1, 0, 0, 0 });
	checkMathVector.push_back({ 2, 0, 2, 1, 2, 2 });
	checkMathVector.push_back({ 2, 0, 1, 1, 0, 2 });
	checkMathVector.push_back({ 0, 2, 0, 1, 0, 0 });
	checkMathVector.push_back({ 0, 2, 1, 2, 2, 2 });
	checkMathVector.push_back({ 0, 2, 1, 1, 2, 0 });
	checkMathVector.push_back({ 2, 2, 1, 2, 0, 2 });
	checkMathVector.push_back({ 2, 2, 2, 1, 2, 0 });
	checkMathVector.push_back({ 2, 2, 1, 1, 0, 0 });
	checkMathVector.push_back({ 0, 1, 1, 1, 2, 1 });
	checkMathVector.push_back({ 1, 2, 1, 1, 1, 0 });
	checkMathVector.push_back({ 2, 1, 1, 1, 0, 1 });
	checkMathVector.push_back({ 1, 0, 1, 1, 1, 2 });
	checkMathVector.push_back({ 2, 0, 0, 0, 1, 0 });
	checkMathVector.push_back({ 2, 2, 0, 0, 1, 1 });
	checkMathVector.push_back({ 0, 2, 2, 0, 1, 1 });
	checkMathVector.push_back({ 0, 1, 2, 1, 1, 1 });
	checkMathVector.push_back({ 2, 1, 1, 1, 1, 0 });
	checkMathVector.push_back({ 0, 2, 0, 0, 0, 1 });
	checkMathVector.push_back({ 2, 2, 2, 0, 2, 1 });
	checkMathVector.push_back({ 0, 2, 2, 2, 1, 2 });
}

void AI::PlacePiece(int (*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3], int* gameState)
{
	try
	{
		//Kiem tra may co the win
		for (int i = 0; i < checkMathVector.size(); i++)
		{
			checkSection(checkMathVector[i][0], checkMathVector[i][1], checkMathVector[i][2], checkMathVector[i][3], checkMathVector[i][4], checkMathVector[i][5], AI_PIECE, gridArray, gridPieces);
		}
		//Kiem tra nguoi co the win
		for (int i = 0; i < checkMathVector.size(); i++)
		{
			checkSection(checkMathVector[i][0], checkMathVector[i][1], checkMathVector[i][2], checkMathVector[i][3], checkMathVector[i][4], checkMathVector[i][5], PLAYER_PIECE	, gridArray, gridPieces);
		}

		checkIfPieceIsEmpty(1, 1, gridArray, gridPieces);

		checkIfPieceIsEmpty(1, 1, gridArray, gridPieces);
		checkIfPieceIsEmpty(0, 0, gridArray, gridPieces);
		checkIfPieceIsEmpty(0, 1, gridArray, gridPieces);
		checkIfPieceIsEmpty(0, 2, gridArray, gridPieces);
		checkIfPieceIsEmpty(1, 2, gridArray, gridPieces);
		checkIfPieceIsEmpty(2, 2, gridArray, gridPieces);
		checkIfPieceIsEmpty(2, 1, gridArray, gridPieces);
		checkIfPieceIsEmpty(1, 0, gridArray, gridPieces);
		checkIfPieceIsEmpty(2, 0, gridArray, gridPieces);
	}
	catch(int error)
	{

	}
	*gameState = STATE_PLAYING;
}

void AI::checkSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3])
{
	if ((*gridArray)[x1][y1] == pieceToCheck && (*gridArray)[x2][y2] == pieceToCheck)
	{
		if (EMPTY_PIECE == (*gridArray)[X][Y])
		{
			(*gridArray)[X][Y] = AI_PIECE;
			gridPieces[X][Y]->setTexture(O_FILEPATH);
			gridPieces[X][Y]->setVisible(true);
			gridPieces[X][Y]->runAction(cocos2d::FadeIn::create(PIECE_FADE_IN_TIME));
			throw - 1;
		}
	}
}

void AI::checkIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3])
{
	if (EMPTY_PIECE == *(gridArray)[X][Y])
	{
		(*gridArray)[X][Y] = AI_PIECE;
		gridPieces[X][Y]->setTexture(O_FILEPATH);
		gridPieces[X][Y]->setVisible(true);
		gridPieces[X][Y]->runAction(cocos2d::FadeIn::create(PIECE_FADE_IN_TIME));
		throw - 2;
	}
}