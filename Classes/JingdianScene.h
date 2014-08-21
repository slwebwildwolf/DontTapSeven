#ifndef __JINGDIAN_SCENE_H__
#define __JINGDIAN_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
#include "BaseScene.h"

USING_NS_CC;

class JingdianScene : public BaseScene
{
private:	

public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(JingdianScene);

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

#endif // __JINGDIAN_SCENE_H__
