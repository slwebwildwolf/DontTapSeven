#include "ChanScene.h"
#include "ConstValue.h"

USING_NS_CC;

Scene* ChanScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChanScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//开始游戏
void ChanScene::startGame()
{
	moshi = "chan";
	lineMax = Chan_LineMax;
	gameTime = Chan_GameTime;
	setScoreLabel(StringUtils::format("%-.3f",gameTime));
	BaseScene::startGame();
}

void ChanScene::update(float dt)
{
	if (timeRunning)
	{	
		gameTime -= dt;
		if (gameTime<=0)
		{
			gameTime = 0.0000f;
			endGame(true);
		}
		setScoreLabel(StringUtils::format("%-.3f",gameTime));
	}
}

//开始计时
void ChanScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		timeRunning = true;
	}
}

//结束计时
void ChanScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
	}
}

//结束游戏
void ChanScene::endGame(bool bWin)
{
	stopTimer();
	int bestScore = LoadIntegerFromXML(moshi.c_str(),0);
	if (scoreLine> bestScore || bestScore == 0)
	{
		bestScore = scoreLine;
		SaveIntegerToXML(moshi.c_str(),bestScore);
	}
	addChild(createEndLayer(Color4B::GRAY,moshi,StringUtils::format("%d",scoreLine),StringUtils::format("%d",bestScore)),2);
}
