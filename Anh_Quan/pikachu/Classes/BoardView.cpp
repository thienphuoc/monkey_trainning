/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "BoardView.h"

Layer *BoardView::CreateBoardView(Board *board) {
    auto boardView = BoardView::create();
    CCLOG("BoardView created");
    boardView->board = board;
    boardView->ShowBoard();
    return boardView;
}

void BoardView::ShowBoard() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    squareSize  = visibleSize.width/(board->getNColumns() + 2);
    width = squareSize*board->getNColumns();
    height = squareSize*board->getNRows();
    setContentSize({width, height});
    
    pokemons.resize(board->getNRows());
    for (int i = 0; i < board->getNRows(); ++i) {
        pokemons[i].resize(board->getNColumns());
        for (int j = 0; j < board->getNColumns(); ++j) {
            pokemons[i][j] = addPokemon(i, j, board->getPokemon(i, j));
            addChild(pokemons[i][j]);
        }
    }
}

Sprite* BoardView::addPokemon(int x, int y, int type) {
    auto pokemon = Sprite::create("Resources/pokemons/" + std::to_string(type) + ".png");
    pokemon->setScaleX(squareSize / pokemon->getContentSize().width);
    pokemon->setScaleY(squareSize / pokemon->getContentSize().height);
    Vec2 position = positionOf(x, y);
    //CCLOG("%f %f", position.x,  position.y);
    pokemon->setPosition(position);
    
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
        removeChoosePokemonEffect();
        if (board->selectPokemon(p.first, p.second)) {
            connectPokemons(board->_x, board->_y, p.first, p.second);
            board->_x = board->_y = -1;
        }
        else {
            createChoosePokemonEffect(pokemons[p.first][p.second]);
            board->_x = p.first;
            board->_y = p.second;
        }
        return true;
    }
    return false;
}

Vec2 BoardView::positionOf(int row, int column) {
    return Vec2(column*squareSize + squareSize / 2, height - row*squareSize - squareSize / 2);
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
    if (pokemons[row][column] == nullptr) {
        return false;
    }
    board->removePokemon(row, column);
    //pokemonCount = pokemonCount - 1;
    //pokemons[row][column] = nullptr;
    pokemons[row][column]->removeFromParent();
    if(board->pokemonCount == 0) {
        Director::getInstance()->replaceScene(HelloWorld::createScene());
    }
    return true;
}

void BoardView::connectPokemons(int x, int y, int _x, int _y) {
    auto connectEffect = getConnectEffect(x, y, _x, _y);
    
    auto pokemonFade1 = TargetedAction::create(pokemons[x][y], FadeOut::create(0.5));
    auto pokemonFade2 = TargetedAction::create(pokemons[_x][_y], FadeOut::create(0.5));
    auto effectSpawn = Spawn::create(pokemonFade1, pokemonFade2, nullptr);
    
    auto removePokemon1 = CallFunc::create(CC_CALLBACK_0(BoardView::removePokemon, this, x, y));
    auto removePokemon2 = CallFunc::create(CC_CALLBACK_0(BoardView::removePokemon, this, _x, _y));
    auto removePokemonSpawn = Spawn::create(removePokemon1, removePokemon2, nullptr);
    
    auto sequence = Sequence::create(connectEffect, effectSpawn, removePokemonSpawn, nullptr);
    this->runAction(sequence);
}

FiniteTimeAction* BoardView::getConnectEffect(int x, int y, int _x, int _y) {
    auto path = board->findPath(x, y, _x, _y);
    std::vector<Vec2> _path;
    for (auto p : path) {
        _path.push_back(positionOf(p.first, p.second));
    }
    
    auto emitter = ParticleSystemQuad::create("Resources/path.plist");
    this->addChild(emitter);
    float duration = 0.3f;
    emitter->setDuration(duration);
    emitter->setPosition(_path[0]);
    Vector<FiniteTimeAction*> actions;
    for (int i = 1; i < _path.size(); ++i) {
        actions.pushBack((FiniteTimeAction*)MoveTo::create(duration / (_path.size() - 1), _path[i]));
    }
    return TargetedAction::create(emitter, Sequence::create(actions));
}

void BoardView::createChoosePokemonEffect(Node* pokemon) {
    auto emitter = ParticleSystemQuad::create("Resources/fireworks.plist");
    auto square = pokemon->getBoundingBox();
    emitter->setPosition(square.getMinX(), square.getMinY());
    
    auto moveUp = MoveBy::create(0.2, Vec2(0, squareSize));
    auto moveRight = MoveBy::create(0.2, Vec2(squareSize, 0));
    auto moveDown = MoveBy::create(0.2, Vec2(0, -squareSize));
    auto moveLeft = MoveBy::create(0.2, Vec2(-squareSize, 0));
    auto sequence = RepeatForever::create(Sequence::create(moveUp, moveRight, moveDown, moveLeft, nullptr));
    emitter->runAction(sequence);
    
    this->addChild(emitter, 2);
    emitter->setName("choosePokemon");
    AudioManager::playSelectPokemonSoundEffect();
}

void BoardView::removeChoosePokemonEffect() {
    if (this->getChildByName("choosePokemon") != nullptr)
    this->removeChildByName("choosePokemon");
    AudioManager::playRemovePokemonSoundEffect();

}
