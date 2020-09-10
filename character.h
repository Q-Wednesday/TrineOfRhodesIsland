#ifndef CHARACTER_H
#define CHARACTER_H
#include"entity.h"
#include"constant.h"
#include<QVector>
#include"animationmanager.h"
#include<QSoundEffect>
class Character:public Entity{
public:
    Character(QObject* parent=nullptr);
    ~Character();
    void fall();//坠落，纵向的移动
    bool can_move();//是否可以移动
    void move(moveDirection d);//改变移动状态，由controller调用
    void move();//进行横向的移动
    virtual void attack()=0;
    void jump();//跳
    bool check_alive();//是否活着
    AnimationManager* get_animemanager();
    bool get_orientation();
    int get_height();
    virtual void skill();//特殊技能
    void add_skill_point(int p);
    void go_up();
protected:


    AnimationManager* m_animemanager;
    bool m_jumping;//是否正在悬空
    bool m_doublejump;//是否已经二段跳
    bool m_leftblocked;//左边被阻挡
    bool m_rightblocked;//是否右侧被阻挡
    bool m_attacking;//是否正在攻击
    bool m_indeadzone;//是否在死亡空间中
    int m_height;//身高，用于重新放至在地上的位置
    int m_attack;//攻击力
    bool m_orientation;//面对的方向，0左，1右
    int m_skillpoint;

    QSoundEffect m_attack_sound;
    QSoundEffect m_jump_sound;
    QSoundEffect m_skill_sound;
};
#endif // CHARACTER_H
