#include "JiejiScene.h"
#include "ConstValue.h"

USING_NS_CC;

Scene* JiejiScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = JiejiScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//开始游戏
void JiejiScene::startGame()
{
	lineMax = JieJi_LineMax;
	moshi = "jieji";
	BaseScene::startGame();	
	setScoreLabel(StringUtils::format("%d",scoreLine));	
}

void JiejiScene::update(float dt)
{
	if(timeRunning)
	{ 
		setScoreLabel(StringUtils::format("%d",scoreLine));	
		moveSpeed += JieJi_Add * dt;
	}
}

//开始计时
void JiejiScene::startTimer()
{
	if(!timeRunning)
	{		
		timeRunning = true;
		moveSpeed = JieJi_Speed;
		autoDown(moveSpeed);
		scheduleUpdate();
	}
}

//结束计时
void JiejiScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
	}
}

void JiejiScene::endGame(bool bWin)
{
	stopTimer();
	int bestScore = LoadIntegerFromXML(moshi.c_str(),0);
	if (scoreLine> bestScore || bestScore == 0)
	{
		bestScore = scoreLine;
		SaveIntegerToXML(moshi.c_str(),bestScore);
	}
	addChild(createEndLayer(Color4B::GREEN,moshi,scoreLabel->getString(),StringUtils::format("%d",bestScore)),2);
}