#include"spikeland.h"
#include<QPainter>
#include"constant.h"
#include"character.h"
SpikeLand::SpikeLand(QObject* parent):Land(parent),m_tick(0)
,
m_attack(1){
    setData(detailType,spikeLand);
    m_texture=QPixmap(":/texture/normal");
}

SpikeLand::~SpikeLand(){

}

SpikeLand::SpikeLand(int width,int height,int x,int y,int attack,QObject*parent):Land(width,height,x,y,parent)
,m_tick(0),m_attack(attack){
    setData(detailType,spikeLand);
    m_texture=QPixmap(":/texture/normal");
;}

QRectF SpikeLand::boundingRect() const{
    return QRectF(-m_width/2,-m_height/2,m_width,m_height);
}

QPainterPath SpikeLand::shape() const{
    QPainterPath path;
    path.addRect(QRectF(-m_width/2,-m_height/2,m_width,m_height));
    return path;
}


void SpikeLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::yellow));
    painter->drawRect(-m_width/2,-m_height/2+20,m_width,m_height-20);

    //painter->setBrush(QBrush(QImage(":/texture/spike")));

   // painter->drawRect(-m_width/2,-m_height/2-20,m_width,0);
    painter->drawTiledPixmap(-m_width/2,-m_height/2,m_width,20,QPixmap(":/texture/spike"));

    painter->restore();
}
void SpikeLand::advance(int phase){
    if(!phase)
        return;
    if(m_tick==0){
        for(auto collision:collidingItems()){
            if(collision->data(entityType)==characterType||collision->data(entityType)==enemyType){
                Character* entity=static_cast<Character*>(collision);
                if(y()-m_height/2-entity->get_height()*1/2>=entity->y())
                {


                    entity->set_hp(entity->get_hp()-m_attack);
                }
            }
        }
    }
    m_tick=(m_tick+1)%15;
}
int SpikeLand::get_attack(){
    return m_attack;
}
