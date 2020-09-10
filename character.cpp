#include"character.h"
#include<QDebug>
Character::Character(QObject*parent):Entity(parent)
,m_jumping(true)
,m_doublejump(false)
,m_leftblocked(false)
,m_rightblocked(false)
,m_height(120)
,m_attacking(false)
,m_indeadzone(false)
,m_orientation(true)
{

}

Character::~Character(){
    delete m_animemanager;
}

void Character::fall(){
    //先标记为false,碰到了再标记true
    m_leftblocked=false;
    m_rightblocked=false;
    m_jumping=true;
    m_indeadzone=false;
    //然后检测是否左右被阻挡，是否站在地上
    for(auto collision:collidingItems()){

        if(collision->data(entityType)==landType){

            int height=collision->boundingRect().height();
            //在一定范围内把角色从砖块下面抬上来
            if(y()<collision->y()-height/2-m_height*1/2){               
                //碰撞则Y轴速度为0
                m_speedy=0;

                setY(collision->y()-height/2-m_height);

                m_jumping=false;
                m_doublejump=false;

                //根据当前状态对动画播放进行调整
                if( m_speedx==0){
                    m_animemanager->changeMode(relaxMode);
                }
                else if(m_speedx!=0){

                    m_animemanager->changeMode(moveMode);
                }
                continue;
            }
            else if(x()<collision->x()){
                m_rightblocked=true;

            }
            else if(x()>collision->x()){
                m_leftblocked=true;
            }
        }
        else if(collision->data(entityType)==deadZone){
            m_indeadzone=true;
        }
    }
    //跳跃中则播放跳跃动画
    if(m_jumping){
       m_animemanager->changeMode(jumpMode);
    }
    //对y轴的速度进行计算，最高为10

    if(m_ay<g)
        m_ay+=1;

    m_speedy+=m_ay;

    if(m_speedy>=10)
        m_speedy=10;


    setY(y()+m_speedy);

}

bool Character::can_move(){
    //检测能否移动
    if(m_speedx>0&& m_rightblocked)
        return false;
    else if(m_speedx<0&&m_leftblocked)
        return false;

    return true;

}

void Character::move(){
    //根据当前速度和朝向进行移动
    if(!can_move())
        return;
    if(m_speedx>0){
        m_orientation=true;
       setTransform(QTransform().rotate(0,Qt::YAxis));
    }
    else if(m_speedx<0){
        m_orientation=false;
        setTransform(QTransform().rotate(180,Qt::YAxis));
    }
    else{
            if(!m_jumping)

                m_animemanager->changeMode(relaxMode);

    }
    setX(x()+m_speedx);
}

bool Character::check_alive(){
    //检测是否存活。
    if(m_indeadzone)
    {
        m_hp=0;
        m_indeadzone=false;
    }
    if(m_hp<=0)
        return false;
    return true;
}

AnimationManager* Character::get_animemanager(){
    return m_animemanager;
}

bool Character::get_orientation(){
    return m_orientation;
}

int Character::get_height(){
    return m_height;
}



void Character::go_up(){
    m_ay=-10;
    m_speedy=-10;
}
