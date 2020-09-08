#include"hintland.h"
#include<QPainter>
#include"constant.h"
#include"character.h"
HintLand::HintLand(int width,int height,int x,int y,QString hint,QObject*parent):
    Land(width,height,x,y,parent),m_hint(hint),m_showing(false){
    setData(detailType,hintLand);
}

HintLand::~HintLand(){

}


QRectF HintLand::boundingRect() const{
    return QRectF(-m_width/2,-m_height/2,m_width,m_height);
}
QPainterPath HintLand::shape() const{
    QPainterPath path;
    path.addRect(QRectF(-m_width/2,-m_height/2,m_width,m_height));
    return path;
}

void HintLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();

    painter->setBrush(QBrush(Qt::yellow));

    painter->drawRect(-m_width/2,-m_height/2,m_width,m_height);

    painter->restore();
}

void HintLand::advance(int phase){
    bool character_on=false;//是否有人在地板上

    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            Character* entity=static_cast<Character*>(collision);
            if(y()-m_height/2-entity->get_height()*1/2>=entity->y())
            {

                character_on=true;

            }
        }
    }
    if(character_on&& !m_showing)
    {
        emit showHint(m_hint);
        m_showing=true;
    }
    if(!character_on && m_showing)
    {
        emit showHint("");
        m_showing=false;
    }

}

QString HintLand::get_hint(){
    return m_hint;
}
