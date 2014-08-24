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
	lineMax = JingDian_LineMax;
	BaseScene::startGame();
	setScoreLabel("0.000");
}

void JingdianScene::update(float dt)
{
	gameTime = gameTime + dt;
	setScoreLabel(StringUtils::format("%-.3f",gameTime));	
}

//开始计时
void JingdianScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		gameTime = 0;
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
		addChild(createEndLayer(Color4B::GREEN,moshi,scoreLabel->getString(),StringUtils::format("%f",gameTime)),2);
	} 
	else
	{
		addChild(createEndLayer(Color4B::RED,moshi,"",StringUtils::format("%g",((double)bestTime)/1000)),2);
	}
}
