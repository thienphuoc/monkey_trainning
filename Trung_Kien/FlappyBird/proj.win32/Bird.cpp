#include"Bird.h"
#include "SimpleAudioEngine.h"

Bird::Bird(Scene *scene) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	bird = Sprite::create("Ball.png");
	bird->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	PhysicsBody *birdBody = PhysicsBody::createCircle(bird->getContentSize().width / 2);
	birdBody->setDynamic(false);
	birdBody->setCollisionBitmask(1);
	birdBody->setContactTestBitmask(true);
	bird->setPhysicsBody(birdBody);
	scene->addChild(bird,100);
	bird->runAction(RepeatForever::create(MoveBy::create(0.25/2, Vec2(0,-10))));//với mọi độ cao thì tốc độ ko thay đổi

	
}
void Bird::fly() {
	//MoveBy *f = MoveBy::create(0.25, Vec2(0, 20));
	MoveTo* f = MoveTo::create(0.123, Vec2(visibleSize.width / 2 + origin.x, bird->getPosition().y+20));
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("wing.mp3"); Lag
	bird->runAction(f);
}