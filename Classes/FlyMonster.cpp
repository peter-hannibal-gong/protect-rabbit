
#include "FlyMonster.h"
extern int type_monster;  //当前要生产的怪物类型
;

Sprite* FlyMonster::createSprite()
{

    return FlyMonster::create();
}

/*获取怪物的血量*/
int FlyMonster::getHp()
{
    return Hp;
}

/*获取价值*/
int FlyMonster::getValue()
{
    return value;
}

/*初始化*/
bool FlyMonster::init()
{
    if (!Sprite::init()) {
        return false;
    }

    //设置帧动画
    
    Vector<SpriteFrame*> frame;
    switch (type_monster) {
        case 0:
            frame.pushBack(SpriteFrame::create("/Monster/FlyMonster/Monster03.png", Rect(0, 0, 100, 80)));
            frame.pushBack(SpriteFrame::create("/Monster/FlyMonster/Monster04.png", Rect(0, 0, 100, 80)));
            break;
        case 1:
            frame.pushBack(SpriteFrame::create("/Monster/PinkMonster/Monster01.png", Rect(0, 0, 100, 80)));
            frame.pushBack(SpriteFrame::create("/Monster/PinkMonster/Monster02.png", Rect(0, 0, 100, 80)));
            break;
        case 2:
            frame.pushBack(SpriteFrame::create("/Monster/GreenMonster/Monster07.png", Rect(0, 0, 100, 80)));
            frame.pushBack(SpriteFrame::create("/Monster/GreenMonster/Monster08.png", Rect(0, 0, 100, 80)));
            break;
    }

    float animationdelay = 0.25f;
    auto animation = Animation::createWithSpriteFrames(frame, animationdelay);

    //表示无限循环
    int repeatTime = -1;
    auto animate = Animate::create(animation);
    auto repeatAnimation = RepeatForever::create(animate);

    //设置标签便于后续停止动作
    repeatAnimation->setTag(1);
    this->runAction(repeatAnimation);

    //this->stopActionByTag(1);  //停止动作


    //选择怪物类型
    switch (type_monster) {
        case 0:  //flymonster
            speed = 100;
            Origin_Hp=Hp = 50;
            ATK = 1;       
            value = 14;    
            survival = 1;
            break;
        case 1: //pinkmonster
            speed = 70;
            Origin_Hp = Hp = 100;
            ATK = 1;
            value = 14;
            survival = 1;
            break;
        case 2: //greenmonster
            speed = 50;
            Origin_Hp = Hp = 150;
            ATK = 1;
            value = 14;
            survival = 1;
            break;
    }

    Position Route[18];

    Init_Route(Route);  //初始化路径

    Move(Route, 18);


    //创建生命值血条
    auto HpBarBG = Sprite::create("/Monster/BloodBarBg.png");
    HpBarBG->setPosition(Vec2(getContentSize().width / 2 + 55, getContentSize().height / 2 + 90));
    HpBarBG->setScale(0.8);
    addChild(HpBarBG);

    BloodBar = ProgressTimer::create(Sprite::create("/Monster/BloodBar.png"));
    BloodBar->setType(ProgressTimer::Type::BAR);
    BloodBar->setMidpoint(Vec2(0, 0.5));
    BloodBar->setBarChangeRate(Vec2(1, 0));
    BloodBar->setScale(0.8);
    BloodBar->setPosition(Vec2(HpBarBG->getPosition()));

    addChild(BloodBar, 2);
    //设置血条初始值
    BloodBar->setPercentage(100.0f);

    schedule(CC_SCHEDULE_SELECTOR(FlyMonster::updateHp), 1.0f);

    return true;
}

/*初始化路径*/
void FlyMonster::Init_Route(Position p[])
{

    p[0].i = 1; p[0].j = 1;

    p[1].i = 2; p[1].j = 1;

    p[2].i = 3; p[2].j = 1;

    p[3].i = 4; p[3].j = 1;

    p[4].i = 4; p[4].j = 2;

    p[5].i = 4; p[5].j = 3;

    p[6].i = 4; p[6].j = 4;

    p[7].i = 3; p[7].j = 4;

    p[8].i = 3; p[8].j = 5;

    p[9].i = 3; p[9].j = 6;

    p[10].i = 3; p[10].j = 7;

    p[11].i = 4; p[11].j = 7;

    p[12].i = 4; p[12].j = 8;

    p[13].i = 4; p[13].j = 9;

    p[14].i = 4; p[14].j = 10;

    p[15].i = 3; p[15].j = 10;

    p[16].i = 2; p[16].j = 10;

    p[17].i = 1; p[17].j = 10;

}

/*移动*/
void FlyMonster::Move(Position p[], int num)
{

    //获取分辨率（窗口大小）
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //初始位置
    int x = p[0].j * 80 + 40;
    int y = (6 - p[0].i) * 80 + 40;
    this->setPosition(Vec2(origin.x + x+10, origin.y + y + 20));

    MoveBy* move[18];

    for (int i = 1; i < num; i++) {
        int x1 = p[i - 1].j * 80 + 40;
        int y1 = (6 - p[i - 1].i) * 80 + 40;

        int x2 = p[i].j * 80 + 40;
        int y2 = (6 - p[i].i) * 80 + 40;

        move[i] = MoveBy::create(40.0 / speed, Vec2(x2 - x1, y2 - y1));

    }
    //auto delay = DelayTime::create(delaytime);
    //auto move1 = MoveTo::create(3, Vec2(origin.x + x, origin.y + y));
     //移除事件
    auto remove_monster = CallFunc::create([=]() {
        this->removeFromParent();
        });

    //移动，到达终点后淡出
    auto sequence = Sequence::create( move[1], move[2], move[3], move[4], move[5], move[6],
        move[7], move[8], move[9], move[10], move[11], move[12], move[13], move[14], move[15],
        move[16], move[17], FadeOut::create(0.05), remove_monster, nullptr);

    this->runAction(sequence);


    //int i = 6 - (this->getPosition().y / 80);
    //int j = (this->getPosition().x / 80);

    //auto move1=MoveTo::create(40.0 / speed, Vec2(p[num - 1].j*80+40, (6-p[num - 1].i)*80+40));
    //this->runAction(move1);

}

/*实时更新血量值*/
void FlyMonster::updateHp(float dt)
{

    //Hp = Hp - 15;
    if (Hp <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(FlyMonster::update));
        this->setVisible(false);
        //removeFromParent();//让怪消失
    }
    BloodBar->setPercentage(float(Hp) / Origin_Hp  * 100);
}

/*扣血*/
void FlyMonster::takedamage(int damage)
{
    Hp -= damage;
}

/*获取存活状态*/
bool FlyMonster::getalive()
{
    return survival;

}


