#pragma once
#include <cocos2d.h>
#include "Board.h""

USING_NS_CC;

class BoardView : public Layer
{
	Board* board;

	float squareSize, width, height;

	std::vector<std::vector<Sprite*>> pokemons;

public:

	static Layer* createBoardView(Board* board);

	void showBoard();

	Sprite* addPokemon(int row, int column, int type);

	bool onTouchPokemon(Touch* touch, Event* event);

	Vec2 positionOf(int row, int column);

	std::pair<int, int> findRowAndColumnOfSprite(Node* node);

	bool removePokemon(int row, int column);

	FiniteTimeAction* getConnectEffect(int x, int y, int _x, int _y);

	void connectPokemons(int x, int y, int _x, int _y);
	void createChoosePokemonEffect(Node* pokemon);
	void removeChoosePokemonEffect();
	CREATE_FUNC(BoardView);
};