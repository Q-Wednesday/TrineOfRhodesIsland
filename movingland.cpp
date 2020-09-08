#include"movingland.h"
#include"constant.h"
#include<QPainter>
#include<QDebug>
#include<QEvent>
#include<QGraphicsSceneMouseEvent>
#include<QCursor>
#include<QApplication>
void MarkPoint::set_can_drag(bool on){
     m_candrag=on;
}
void MarkPoint::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;

    setCursor(Qt::ClosedHandCursor);
}
void MarkPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }


    setPos(event->scenePos());
}
void MarkPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;
    setCursor(Qt::OpenHandCursor);
}
MovingLand::MovingLand(int width,int height,int x,int y,int T,QObject*parent):
    Land(width,height,x,y,parent),m_T(T*33),m_start(new MarkPoint),m_end(new MarkPoint)
{
    setData(detailType,movingLand);
    QPainterPath shape;
    shape.addEllipse(-10,-10,20,20);
    m_start->setShape(shape);
    m_end->setShape(shape);
    m_start->set_can_drag();
    m_end->set_can_drag();
    m_start->setPos(x-width/2-100,y);
    m_end->setPos(x+width/2+100,y);
    m_texture=QPixmap(":/texture/movingland");
}

MovingLand::MovingLand(int width,int height,int T,QPointF start,QPointF end,QObject*parent):
    Land(width,height,start.x(),start.y(),parent),m_T(T*33),m_startpoint(start)
  ,m_endpoint(end){
    m_speedx=(end.x()-start.x())/m_T;
    m_speedy=(end.y()-start.y())/m_T;
    m_texture=QPixmap(":/texture/movingland");
}
MovingLand::~MovingLand(){

}
void MovingLand::advance(int phase){
    if(!phase)
        return;
    qreal distance=qSqrt(qPow(x()-m_startpoint.x(),2)+qPow(y()-m_startpoint.y(),2));
    if(distance<=20){
        m_speedx=(m_endpoint.x()-m_startpoint.x())/m_T;
        m_speedy=(m_endpoint.y()-m_startpoint.y())/m_T;
    }
    distance=qSqrt(qPow(x()-m_endpoint.x(),2)+qPow(y()-m_endpoint.y(),2));
    if(distance<=20){
        m_speedx=(m_startpoint.x()-m_endpoint.x())/m_T;
        m_speedy=(m_startpoint.y()-m_endpoint.y())/m_T;
    }
    //qDebug()<<m_speedx<<m_startpoint.x()<<m_endpoint.x()<<m_T;
    setX(x()+m_speedx);
    setY(y()+m_speedy);

}

QRectF MovingLand::boundingRect() const{
    return QRectF(-m_width/2,-m_height/2,m_width,m_height);
}

QPainterPath MovingLand::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void MovingLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setBrush(m_texture);
    painter->drawRect(boundingRect());
    painter->restore();
}

QVector<QPointF> MovingLand::get_path(){
    QVector<QPointF> vector;
    vector.push_back(m_start->pos());
    vector.push_back(m_end->pos());
    return vector;
}

int MovingLand::get_T(){
    return m_T/33;
}
QVector<AirWall*> MovingLand::get_point(){
    return  QVector<AirWall*>{m_start,m_end};
}
