#ifndef EXUSIAI_H
#define EXUSIAI_H
#include"player.h"
class Exusiai:public Player{
public:
    Exusiai(QObject*parent=nullptr);
    ~Exusiai();
    void skill() override;
public slots:
    void shoot();
    void skillshot();
};

#endif // EXUSIAI_H
