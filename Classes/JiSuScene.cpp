#include "JiSuScene.h"
#include "ConstValue.h"

USING_NS_CC;

Scene* JiSuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = JiSuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void JiSuScene::startGame()
{
	lineMax = JiSu_LineMax;
	moshi = "jisu";
	BaseScene::startGame();	
	setScoreLabel(StringUtils::format("%g",moveSpeed));	
}

void JiSuScene::update(float dt)
{
	if(timeRunning)
	{ 
		setScoreLabel(StringUtils::format("%g",moveSpeed));
		autoDown(moveSpeed);
		moveSpeed += JiSu_Add;
	}
}

//开始计时
void JiSuScene::startTimer()
{
	if(!timeRunning)
	{
		startTime = clock();
		timeRunning = true;
		moveSpeed = JiSu_Speed;
		scheduleUpdate();		
	}
}

//结束计时
void JiSuScene::stopTimer()
{
	if(timeRunning)
	{
		timeRunning = false;
		unscheduleUpdate();		
	}
}

void JiSuScene::endGame(bool bWin)
{
	stopTimer();
	double bestScore = LoadDoubleToXML(moshi.c_str(),0);
	if (moveSpeed> bestScore || bestScore == 0)
	{
		bestScore = moveSpeed;
		SaveIntegerToXML(moshi.c_str(),bestScore);
	}
	addChild(createEndLayer(Color4B::GREEN,moshi,scoreLabel->getString(),StringUtils::format("%g",bestScore)),2);
}