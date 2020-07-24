#include "BoardView.h"
#include "GameScene.h"
#include <algorithm>
#include <vector>
#include "proj.win32/Audio.h"
#include "GameOverScene.h"
using namespace std;

Layer* BoardView::createBoardView(Board* board)
{
	auto boardView = BoardView::create();
	boardView->board = board;
	boardView->ShowBoard();
	return boardView;
}

void BoardView::ShowBoard()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	squareSize = visibleSize.width / (board->getColums() + 2);
	witdh = squareSize * board->getColums();
	height = squareSize * board->getRows();
	CCLOG("%f nhan  %f", witdh, height);

	setContentSize({ witdh, height });

	pokemons.resize(board->getRows());

	for (int x = 0; x < board->getRows(); x++)
	{
		pokemons[x].resize(board->getColums());
		for (int y = 0; y < board->getColums(); y++)
		{
			pokemons[x][y] = addPokemon(x, y, board->getPokemon(x, y));
			//this->addChild(pokemons[x][y]);
			addChild(pokemons[x][y]);
		}
	}
}

Sprite* BoardView::addPokemon(int row, int column, int type)
{
	auto pokemon = Sprite::create("pokemons/" + to_string(type) + ".png");
	pokemon->setScaleX(squareSize / pokemon->getContentSize().width);
	pokemon->setScaleY(squareSize / pokemon->getContentSize().height);
	Vec2 position = positionOf(row, column);
	pokemon->setPosition(position);

	//Event Listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(BoardView::onTouchPokemon, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, pokemon);

	return pokemon;
}

bool BoardView::onTouchPokemon(Touch* touch, Event* event)
{
	auto touchLocation = touch->getLocation() - this->getPosition();
	auto taget = event->getCurrentTarget();
	if (taget->getBoundingBox().containsPoint(touchLocation))
	{
		auto p = findRowAndColunOfSprite(taget);
		removeChoosePokemonEffect();
		if (board->selectPokemon(p.first, p.second))
		{
			connectPokemons(board->_x, board->_y, p.first, p.second);
			//removePokemon(board->_x, board->_y);
			//removePokemon(p.first, p.second);
			board->_x = board->_y = -1;
			//board->_y = -1;
			CCLOG("CURRENTLY SELECTED: row = %d , column = %d", -1, -1);
		}
		else
		{
			createChoosePokemonEffect(pokemons[p.first][p.second]);
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

pair<int, int> BoardView::findRowAndColunOfSprite(Node* node)
{
	for (int x = 0; x < board->getRows(); x++)
	{
		for (int y = 0; y < board->getColums(); y++)
		{
			if (pokemons[x][y] == node)
			{
				return{ x, y };
			}
		}
	}

	return { -1, -1 };
}

bool BoardView::removePokemon(int row, int column)
{
	Audio::playRemovePokemonSoundEffeect();
	if (pokemons[row][column] == nullptr)
	{
		return false;
	}
	board->removePokemon(row, column);
	//pokemons[row][column] == nullptr;

	pokemons[row][column]->removeFromParent();
	dem = dem + 1;
	if (dem == 64)
	{
		this->scheduleOnce(schedule_selector(BoardView::GoToGameOver), 0.25);
		//GoToMainMenuSceneBoardView(0.1);
		//getDem();
		//gameScene.GetDemCountRemovePokemon();
		
	}
	CCLOG("%d la so pokemon bi xoa", dem);
	
	return true;
}

void BoardView::connectPokemons(int x, int y, int _x, int _y)
{
	auto connectEffect = getConnectEffect(x, y, _x, _y);

	auto pokemonFade_1 = TargetedAction::create(pokemons[x][y], FadeOut::create(0.5));
	auto PokemonFade_2 = TargetedAction::create(pokemons[_x][_y], FadeOut::create(0.5));
	auto effectSpawn = Spawn::create(pokemonFade_1, PokemonFade_2, nullptr);

	auto removePokemon_1 = CallFunc::create(CC_CALLBACK_0(BoardView::removePokemon, this, x, y));
	auto removePokemon_2 = CallFunc::create(CC_CALLBACK_0(BoardView::removePokemon, this, _x, _y));
	auto removePokemonSpawn = Spawn::create(removePokemon_1, removePokemon_2, nullptr);

	this->runAction(Sequence::create(connectEffect, effectSpawn, removePokemonSpawn, nullptr));
}

FiniteTimeAction* BoardView::getConnectEffect(int x, int y, int _x, int _y)
{
	auto path = board->findPath(x, y, _x, _y);
	vector<Vec2> _path;
	for (auto p : path)
	{
		_path.push_back(positionOf(p.first, p.second));
	}

	auto emitter = ParticleSystemQuad::create("path.plist");
	this->addChild(emitter);
	float duration = 0.3f;
	emitter->setDuration(duration);
	emitter->setPosition(_path[0]);
	Vector<FiniteTimeAction*> action;

	for (int i = 1; i < _path.size(); i++)
	{
		action.pushBack((FiniteTimeAction*)MoveTo::create(duration / (_path.size() - 1), _path[i]));
	}

	auto action_Taget = TargetedAction::create(emitter, Sequence::create(action));

	return action_Taget;
}


void BoardView::createChoosePokemonEffect(Node* pokemon)
{
	auto emitter = ParticleSystemQuad::create("fireworks.plist");
	auto square = pokemon->getBoundingBox();
	emitter->setPosition(square.getMinX(), square.getMinY());

	auto moveUp = MoveBy::create(0.2, Vec2(0, squareSize));
	auto moveRight = MoveBy::create(0.2, Vec2(squareSize, 0));
	auto moveDown = MoveBy::create(0.2, Vec2(0, -squareSize));
	auto moveLeft = MoveBy::create(0.2, Vec2(-squareSize, 0));

	auto sequence = Sequence::create(moveUp, moveRight, moveDown, moveLeft, nullptr);
	auto repeat_sequence = RepeatForever::create(sequence);

	emitter->runAction(repeat_sequence);

	this->addChild(emitter, 2);
	emitter->setName("choosePokemon");

	Audio::playSelectPokemonSoundEffect();
}

void BoardView::createRemovePokemonEffect(Node* pokemon)
{
	auto emitter = ParticleSystemQuad::create("bubbles.plist");
	emitter->setPosition(pokemon->getPosition());
	emitter->setDuration(0.5);
	this->addChild(emitter, 2);
	Audio::playRemovePokemonSoundEffeect();
}

void BoardView::removeChoosePokemonEffect()
{
	if (this->getChildByName("choosePokemon") != nullptr)
	{
		this->removeChildByName("choosePokemon");
	}
}

void BoardView::GoToGameOver(float dt)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}

int BoardView::getDem()
{
	return dem;
}