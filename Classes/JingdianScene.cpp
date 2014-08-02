#include "JingdianScene.h"

USING_NS_CC;

Scene* JingdianScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = JingdianScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool JingdianScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	srand(time(NULL));
    
	visibleSize = Director::getInstance()->getVisibleSize();

	gameLayer = Node::create();
	addChild(gameLayer);

	endLayer = LayerColor::create(Color4B::RED);
	endLayer->retain();

	timerLabel = Label::create();
	timerLabel->setColor(Color3B::BLUE);
	timerLabel->setSystemFontSize(50);
	timerLabel->setString("0.000\"");
	timerLabel->setPosition(visibleSize.width/2, visibleSize.height-30);
	addChild(timerLabel);

	//addStartLine();
	
	//addEndLine();

	startGame();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		log("onTouch");
		auto bs = Block::getBlocks();
		Block *b;

		for(auto it = bs->begin(); it != bs->end(); it++)
		{
			b = *it;

			if(b->getLineIndex()==1&&b->getBoundingBox().containsPoint(t->getLocation()))
			{
				if(b->getColor()==Color3B::BLACK)
				{
					b->setColor(Color3B::GRAY);
					this->moveDown();
					this->startTimer();

				}
				else if(b->getColor()==Color3B::GREEN)
				{
					this->moveDown();
					this->stopTimer();
				}
				else
				{
					endGame();
				}
				break;
			}
		}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//��ʼ��Ϸ
void JingdianScene::startGame()
{
	linesCount = 0;
	showEnd = false;
	timeRunning = false;
	this->removeChild(endLayer);
 
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

//��ӿ�ʼ�Ļ�ɫ��
void JingdianScene::addStartLine()
{
	//auto b = new Block();
	//b->createWithArgs(Color3B::YELLOW, Size(visibleSize.width,visibleSize.height/4), "", 10, Color4B::BLACK);
	auto b = Block::createWithArgs(Color3B::GREEN, Size(visibleSize.width,visibleSize.height/4), "", 10, Color4B::BLACK);
	gameLayer->addChild(b);
	b->setLineIndex(0);
}

//��ӽ�������ɫ����ռ����Ļ
void JingdianScene::addEndLine()
{
	auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "Game Over", 30, Color4B::BLACK);
	gameLayer->addChild(b);
	b->setLineIndex(4);
}


void JingdianScene::endGame()
{
	Block::clearBlocks();
	addChild(endLayer,1);
	 
	CCLog("Game over");
}




//�����ͨ�ĺڰ׿���
void JingdianScene::addNormalLine(int lineIndex)
{
	linesCount++;

	Block *b;
	int blackIndex = rand()%4;
	for(int i=0; i<4; i++)
	{
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width/4-1,visibleSize.height/4-1), "", 20, Color4B::BLACK);
		b->setPosition(i*visibleSize.width/4, lineIndex*visibleSize.height/4);
		b->setLineIndex(lineIndex);
		gameLayer->addChild(b);
	}
}

//��������
void JingdianScene::moveDown()
{
	if(linesCount<10)
	{
		addNormalLine(4);
	}
	else if(!showEnd)
	{
		addEndLine();
		showEnd = true;
	}

	auto bs = Block::getBlocks();
	for(auto it=bs->begin(); it!=bs->end(); it++)
	{
		(*it)->moveDowm();
	}
}

void JingdianScene::update(float dt)
{
	long offset = clock()-startTime;

	timerLabel->setString(StringUtils::format("%g",((double)offset)/1000));
	
}

//��ʼ��ʱ
void JingdianScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timeRunning = true;
	}
}

//������ʱ
void JingdianScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
		Director::getInstance()->popScene();
	}
}

void JingdianScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
