
#ifndef __CarrotFantasy__CARROT_
#define __CarrotFantasy__CARROT__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include"Scene1.h"
USING_NS_CC;
class Carrot : public cocos2d::Sprite
{
public:

	int Hp=10;
	ProgressTimer* BloodBar;
	
	static Sprite* createSprite();

	virtual bool init();

	CREATE_FUNC(Carrot);

	void updateHp(float dt);  //更新血量

	bool SetHp(int damage);   //设置血量
};
#endif /* defined(__CarrotFantasy__Carrot__) */