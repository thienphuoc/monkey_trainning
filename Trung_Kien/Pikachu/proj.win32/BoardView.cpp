#include "BoardView.h"
#include "algorithm"

Layer* BoardView::createBoardView(Board* board)
{
	auto boardView = BoardView::create();
	boardView->board = board;
	boardView->showBoard();
	return boardView;
}

void BoardView::showBoard()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	squareSize = visibleSize.width / (board->getNColumns() + 2);
	width = squareSize * board->getNColumns();
	height = squareSize * board->getNRows();
	setContentSize({ width, height });

	pokemons.resize(board->getNRows());
	for (int i = 0; i < board->getNRows(); ++i) {
		pokemons[i].resize(board->getNColumns());
		for (int j = 0; j < board->getNColumns(); ++j) {
			pokemons[i][j] = addPokemon(i, j, board->getPokemon(i, j));
			addChild(pokemons[i][j]);
		}
	}
}

Sprite* BoardView::addPokemon(int row, int column, int type)
{
	auto pokemon = Sprite::create("pokemons/" + std::to_string(type) + ".png");
	pokemon->setScaleX(squareSize / pokemon->getContentSize().width);
	pokemon->setScaleY(squareSize / pokemon->getContentSize().height);
	Vec2 position = positionOf(row, column);
	pokemon->setPosition(position);

	//EventListener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(BoardView::onTouchPokemon, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, pokemon);

	return pokemon;
}

bool BoardView::onTouchPokemon(Touch* touch, Event* event) {
	auto touchLocation = touch->getLocation() - this->getPosition();
	auto target = event->getCurrentTarget();
	if (target->getBoundingBox().containsPoint(touchLocation)) {
		auto p = findRowAndColumnOfSprite(target);
		if (board->selectPokemon(p.first, p.second)) {
			removePokemon(board->_x, board->_y);
			removePokemon(p.first, p.second);
			board->_x = board->_y = -1;
			CCLOG("CURRENTLY SELECTED: row = %d , column = %d", -1, -1);
		}
		else {
			board->_x = p.first;
			board->_y = p.second;
			CCLOG("CURRENTLY SELECTED: row = %d , column = %d", p.first, p.second);
		}
		return true;
	}
	return false;
}

Vec2 BoardView::positionOf(int row, int column)
{
	return Vec2(column * squareSize + squareSize / 2, height - row * squareSize - squareSize / 2);
}

std::pair<int, int> BoardView::findRowAndColumnOfSprite(Node* node)
{
	for (int i = 0; i < board->getNRows(); ++i) {
		for (int j = 0; j < board->getNColumns(); ++j) {
			if (pokemons[i][j] == node) {
				return { i, j };
			}
		}
	}
	return { -1, -1 };
}

bool BoardView::removePokemon(int row, int column)
{
	if (pokemons[row][column] == nullptr) return false;
	board->removePokemon(row, column);
	removeChild(pokemons[row][column]);
	pokemons[row][column] = nullptr;
	return true;
}
