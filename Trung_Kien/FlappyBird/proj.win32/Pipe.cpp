#include "Pipe.h"
USING_NS_CC;
Pipe::Pipe() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void Pipe::spawnPipe(Scene *scene) {
    //CCLOG("SPAWN PIPE");

    auto topPipe = Sprite::create("Pipe.png");
    auto bottomPipe = Sprite::create("Pipe.png");

    auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
    auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

    auto random = CCRANDOM_0_1();

    if (random < 0.35)
    {
        random = 0.35;
    }
    else if (random > 0.65)
    {
        random = 0.65;
    }

    auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height / 2);//tọa độ y của toppipe

    topPipeBody->setDynamic(false);//dynamic => gravity
    bottomPipeBody->setDynamic(false);

    topPipeBody->setCollisionBitmask(5);
    topPipeBody->setContactTestBitmask(true);

    bottomPipeBody->setCollisionBitmask(5);
    bottomPipeBody->setContactTestBitmask(true);


    topPipe->setPhysicsBody(topPipeBody);
    bottomPipe->setPhysicsBody(bottomPipeBody);

    

    topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));//width= phía sau bên phải của màn hình, vừa đủ để người chơi ko nhìn thấy pipe spawn
    bottomPipe->setPosition(topPipe->getPositionX(), topPipePosition - 40 - topPipe->getContentSize().height);

    auto topPipeAction = MoveTo::create(4 , Point(0, topPipePosition));//speed pipe
    auto bottomPipeAction = MoveTo::create(4 , Point(0, topPipePosition - 40 - topPipe->getContentSize().height));

    topPipe->runAction(topPipeAction);
    bottomPipe->runAction(bottomPipeAction);

    scene->addChild(topPipe);
    scene->addChild(bottomPipe);
    //scoring
    auto pointNode = Node::create();
    auto pointBody = PhysicsBody::createBox(Size(1, 40));

    pointBody->setDynamic(false);
    pointBody->setCollisionBitmask(3);
    pointBody->setContactTestBitmask(true);

    pointNode->setPhysicsBody(pointBody);
    pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - (40 / 2)));

    scene->addChild(pointNode);

    auto pointNodeAction = MoveTo::create(4, Point(0, topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - (40 / 2)));

    pointNode->runAction(pointNodeAction);
    

    //del
    if (topPipe->getPosition().x <= 0) {
        scene->removeChild(topPipe);
        scene->removeChild(bottomPipe);
        scene->removeChild(pointNode);
    }
}
