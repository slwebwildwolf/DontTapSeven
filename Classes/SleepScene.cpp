#include "SleepScene.h"
#include "Utility.h"

USING_NS_CC;

Scene* SleepScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SleepScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SleepScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();

	srand(time(NULL));
    lineMax = 11;
	scoreLine = 0;
	gameLayer = Node::create();
	addChild(gameLayer);	

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
			int currentLine = b->getLineCount();
			if(b->getLineIndex()==1&&b->getBoundingBox().containsPoint(t->getLocation()))
			{
				++scoreLine;
				if((b->getColor()==Color3B::BLACK && !Utility::checkSeven(currentLine)) ||
					(b->getColor()==Color3B::WHITE && Utility::checkSeven(currentLine)))
				{
					
					b->setColor(Color3B::GRAY);
					this->moveDown();
					this->startTimer();
					
					log("%d  %d",scoreLine ,lineMax);
					if (scoreLine == lineMax)
					{
						endGame(true);
					}
				}
				else if(b->getColor()==Color3B::GREEN)
				{
					this->moveDown();
					this->stopTimer();
				}
				else
				{
					this->stopTimer();
					auto *blink = Sequence::create(
						 Repeat::create( 
							 Sequence::create(
								 TintTo::create(0.1, 255,255, 255),
								 TintTo::create(0.1, 255,0, 0),
								 NULL), 				 
							5),
						CallFunc::create(CC_CALLBACK_0(SleepScene::endGame,this,false)),
						NULL
						);
					b->runAction(blink);
				}
				break;
			}
		}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//开始游戏
void SleepScene::startGame()
{
	BaseScene::startGame();
	log("SleepScene startgame");	
	scoreLine =0;
}


void SleepScene::update(float dt)
{
	gameTime = clock()-startTime;

	timerLabel->setString(StringUtils::format("%g",((double)gameTime)/1000));
	
}

//开始计时
void SleepScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timeRunning = true;
	}
}

//结束计时
void SleepScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
	}
}






void SleepScene::endGame(bool bWin)
{
	stopTimer();
	long bestTime = LoadIntegerFromXML("Sleep",0);
	if (bWin)
	{		
		if (gameTime< bestTime || bestTime == 0)
		{
			bestTime = gameTime;
			SaveIntegerToXML("Sleep",bestTime);
		}
		addChild(createEndLayer(Color4B::GREEN,"sleepmoshi",timerLabel->getString(),StringUtils::format("%g",((double)bestTime)/1000)),2);
	} 
	else
	{
		addChild(createEndLayer(Color4B::RED,"sleepmoshi","",StringUtils::format("%g",((double)bestTime)/1000)),2);
	}
	
}

 