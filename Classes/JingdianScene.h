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

	//��ʼ
	void startGame();
	//����
	void endGame(bool bWin);
	//��ʼ��ʱ
	void startTimer();
	//������ʱ
	void stopTimer();

	virtual void update(float dt);
};

#endif // __JINGDIAN_SCENE_H__
