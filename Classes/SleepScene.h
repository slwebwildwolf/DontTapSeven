#ifndef __SLEEP_SCENE_H__
#define __SLEEP_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
#include "BaseScene.h"

USING_NS_CC;

class SleepScene : public BaseScene
{
private:

	Label *timerLabel;
	long startTime;
	long gameTime;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(SleepScene);

	//
	


	//开始
	void startGame();

	//结束
	void endGame(bool bWin);



	//开始计时
	void startTimer();

	//结束计时
	void stopTimer();



	virtual void update(float dt);



	
};

#endif // __SLEEP_SCENE_H__
