#ifndef ENEMY_H
#define ENEMY_H
#include"character.h"
class Enemy:public Character{
public:
    Enemy(QObject*parent=nullptr);
    ~Enemy();
    virtual void auto_move()=0;
    void advance(int phase) override;


protected:
    bool m_canattack;
    Entity* m_target;
};

#endif // ENEMY_H
