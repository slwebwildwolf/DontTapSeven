#include "JingdianScene.h"
#include "Utility.h"
#include "ConstValue.h"

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
//开始游戏
void JingdianScene::startGame()
{
	moshi = "jingdian";
	lineMax = Chan_LineMax;
	BaseScene::startGame();
	setScoreLabel("0.000");
	
}

void JingdianScene::update(float dt)
{
	gameTime = clock()-startTime;
	setScoreLabel(StringUtils::format("%g",((double)gameTime)/1000));	
}

//开始计时
void JingdianScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timeRunning = true;
	}
}

//结束计时
void JingdianScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
	}
}

//结束游戏
void JingdianScene::endGame(bool bWin)
{
	stopTimer();
	long bestTime = LoadIntegerFromXML(moshi.c_str(),0);
	if (bWin)
	{		
		if (gameTime< bestTime || bestTime == 0)
		{
			bestTime = gameTime;
			SaveIntegerToXML(moshi.c_str(),bestTime);
		}
		addChild(createEndLayer(Color4B::GREEN,moshi,scoreLabel->getString(),StringUtils::format("%g",((double)bestTime)/1000)),2);
	} 
	else
	{
		addChild(createEndLayer(Color4B::RED,moshi,"",StringUtils::format("%g",((double)bestTime)/1000)),2);
	}
	
}

void JingdianScene::playRight( Block* b )
{
	BaseScene::playRight(b);
	b->setColor(Color3B::GRAY);
	this->moveDown();
	this->startTimer();

	log("%d  %d",scoreLine ,lineMax);
	if (scoreLine == lineMax)
	{
		endGame(true);
	}
}

void JingdianScene::playError( Block* b )
{
	BaseScene::playError(b);
	this->stopTimer();
	auto *blink = Sequence::create(
		Repeat::create( 
		Sequence::create(
		TintTo::create(0.1, 255,255, 255),
		TintTo::create(0.1, 255,0, 0),
		NULL), 				 
		5),
		CallFunc::create(CC_CALLBACK_0(JingdianScene::endGame,this,false)),
		NULL
		);
	b->runAction(blink);
}

 