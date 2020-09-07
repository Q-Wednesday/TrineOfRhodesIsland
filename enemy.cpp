#include"enemy.h"
Enemy::Enemy(QObject*parent):Character(parent),
m_canattack(false){
    setData(entityType,enemyType);

}

Enemy::~Enemy(){

}

void Enemy::advance(int phase){
    if(!phase)
        return;
    m_animemanager->advance();
    fall();
    auto_move();

    update(boundingRect());
    if(!check_alive()){
        emit deathSignal(this);
    }

}
