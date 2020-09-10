#ifndef SILVER_H
#define SILVER_H
#include"player.h"
//移动速度一般，攻击力较大，擅长近战攻击。技能是近战的群体攻击，攻击时攻击力翻倍，用于清理近处小怪
class Silver:public Player{
public:
    Silver(QObject* parent=nullptr);
    ~Silver();
    void skill() override;
public slots:
    void causeDamage();
    void skillDamage();
public:
    Entity* m_target;
};

#endif // SILVER_H
