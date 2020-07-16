#include "GameScene.h"
#include"GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameScene::create();
	
	layer->setPysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
	
	
}
bool GameScene::init() {
	CCLOG("GAme SCeneeeeeeeeee");
	Sprite* sprite = Sprite::create("background.png");
	this->addChild(sprite);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(5);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::spawnPipe), 2);//frequency pipe

	bird = new Bird(this);//bird
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	};
	keyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		bird->fly();
		
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	
	auto label = Label::createWithTTF( "0","fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label);


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact &contact) {
		PhysicsBody* a = contact.getShapeA()->getBody();
		PhysicsBody* b = contact.getShapeB()->getBody();
		if ((1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask()) || (1 == b->getCollisionBitmask() && 5 == a->getCollisionBitmask()))
		{
			CCLOG("SCORE: %i", score);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
			Director::getInstance()->replaceScene(GameOverScene::createScene(score));
		}
		else if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (1 == b->getCollisionBitmask() && 3 == a->getCollisionBitmask()))
		{
			CCLOG("Point scored");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("point.mp3");
			score++;
			__String* tempScore = __String::createWithFormat("%d", score);
			label->setString(tempScore->getCString());
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	
	
	
	return true;
}

void GameScene::spawnPipe(float dt) {
	pipe.spawnPipe(this);
}