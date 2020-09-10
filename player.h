#ifndef PLAYER_H
#define PLAYER_H
#include"character.h"
#include"constant.h"
class Player:public Character{
public:
    Player(QObject* parent=nullptr);
    ~Player();
    void move(moveDirection d);//改变移动状态，由controller调用，玩家输入触发

    virtual void skill()=0;//特殊技能
    void add_skill_point(int p);

    void jump();//跳跃动作，由controller调用

    void advance(int phase);

    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void attack() override;

protected:

    int m_skillpoint;
    QSoundEffect m_jump_sound;
};

#endif // PLAYER_H
