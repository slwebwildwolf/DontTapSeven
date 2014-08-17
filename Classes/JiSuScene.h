#ifndef __JISU_SCENE_H__
#define __JISU_SCENE_H__


#include "cocos2d.h"
#include "Block.h"
#include "BaseScene.h"

USING_NS_CC;

class JiSuScene : public BaseScene
{
private:
	double scoreSpeed;
public:

	static cocos2d::Scene* createScene();
	CREATE_FUNC(JiSuScene);

	//开始游戏
	void startGame();
	//结束游戏
	void endGame(bool bWin);
	//开始计时
	void startTimer();
	//结束计时
	void stopTimer();

	void logic(float);
	virtual void update(float dt);
	//
	virtual void playRight(Block* b) override;
	virtual void playError(Block* b) override;

};

#endif // __JISU_SCENE_H__
