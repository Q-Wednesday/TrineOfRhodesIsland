#include"springland.h"
#include<QPainter>
#include"character.h"
SpringLand::SpringLand(int x,int y,QObject* parent):
    Land(100,100,x,y,parent){
    setData(detailType,springLand);
    m_texture=QPixmap(":/texture/springland");
}

SpringLand::~SpringLand(){

}




void SpringLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
   painter->drawPixmap(boundingRect(),m_texture,QRect(0,0,100,100));
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
