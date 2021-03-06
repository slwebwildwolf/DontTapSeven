#ifndef __JIEJI_SCENE_H__
#define __JIEJI_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
#include "BaseScene.h"

USING_NS_CC;

class JiejiScene : public BaseScene
{
private:
	
public:
	static cocos2d::Scene* createScene(); 
	CREATE_FUNC(JiejiScene);

	//开始游戏
	void startGame();
	//结束游戏
	void endGame(bool bWin);
	//开始计时
	void startTimer();
	//结束计时
	void stopTimer();

	virtual void update(float dt);
};

#endif // __JIEJI_SCENE_H__
