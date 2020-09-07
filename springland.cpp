#include"springland.h"
#include<QPainter>
#include"character.h"
SpringLand::SpringLand(int x,int y,QObject* parent):
    Land(100,100,x,y,parent){
    setData(detailType,springLand);
}

SpringLand::~SpringLand(){

}


QRectF SpringLand::boundingRect() const{
    return QRectF(-m_width/2,-m_height/2,m_width,m_height);
}

QPainterPath SpringLand::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void SpringLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(boundingRect());
    painter->restore();
}

void SpringLand::advance(int phase){
    if(!phase)
        return;
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType||collision->data(entityType)==enemyType){
            Character* entity=static_cast<Character*>(collision);
            if(y()-m_height/2-entity->get_height()*1/2>=entity->y())
            {

                entity->go_up();

            }
        }
    }
}
