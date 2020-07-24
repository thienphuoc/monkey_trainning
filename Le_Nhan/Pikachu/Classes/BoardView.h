#pragma once

#include "cocos2d.h"
#include "Board.h"
#include "GameScene.h"
using namespace std;

USING_NS_CC;

class BoardView : public Layer
{
	
	Board* board;
	//GameScene* gameScene;

	float squareSize, witdh, height;

	vector<vector<Sprite*>> pokemons;

public:
	unsigned int dem = 0;
	
	static Layer* createBoardView(Board* board);
	void ShowBoard();
	Sprite* addPokemon(int row, int colum, int type);

	Vec2 positionOf(int row, int column);
	pair<int, int> findRowAndColunOfSprite(Node* node);

	bool removePokemon(int row, int column);
	bool onTouchPokemon(Touch* touch, Event* event);
	void connectPokemons(int x, int y, int _x, int _y);
		
	FiniteTimeAction* getConnectEffect(int x, int y, int _x, int _y);
	
	void createChoosePokemonEffect(Node* pokemon);
	void createRemovePokemonEffect(Node* pokemon);

	void removeChoosePokemonEffect();

	void GoToGameOver(float dt);
	//void GoToMainMenuSceneBoardView(Ref* sender);

	int getDem();


	CREATE_FUNC(BoardView);


};