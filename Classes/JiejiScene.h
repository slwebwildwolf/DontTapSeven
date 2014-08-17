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

	//��ʼ��Ϸ
	void startGame();
	//������Ϸ
	void endGame(bool bWin);
	//��ʼ��ʱ
	void startTimer();
	//������ʱ
	void stopTimer();

	void logic(float);
	virtual void update(float dt);
	//
	virtual void playRight(Block* b) override;
	virtual void playError(Block* b) override;

};

#endif // __JIEJI_SCENE_H__
