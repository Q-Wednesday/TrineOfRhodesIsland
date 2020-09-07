#include"gamescene.h"
#include"mapreader.h"
#include<QDebug>
#include<QMouseEvent>
#include<QEvent>
#include<QTime>

GameScene::GameScene(QObject* parent):QObject(parent),m_scene(new QGraphicsScene(this))
  ,m_view(new QGraphicsView())
  ,m_sceneRect(QRect(0,0,1600,900))
  ,m_can_edit(false)
  ,m_movex(0)
  ,m_movey(0)
  ,m_movespeed(8)
  ,m_moving(false)
  ,m_lastpoint(nullptr)
{
    m_view->setScene(m_scene);
    m_view->setSceneRect(m_sceneRect);
    //关闭滚动条
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_view->installEventFilter(this);
    m_view->setFocus();
    setUpUI();
    m_deadzone=new DeadZone(1600,300,800,1040,this);
    m_scene->addItem(m_deadzone);



}
void GameScene::reset(){

    m_scene->clear();

    m_sceneRect=QRect(0,0,1600,900);
    m_movex=0;
    m_movey=0;
    m_moving=false;
    m_lastpoint=nullptr;
    setUpUI();
}
void GameScene::reset(QString filename){
    reset();
    for(Entity* entity:MapReader::readMap(filename)){
       // qDebug()<<"add"<<entity->data(entityType);
        m_scene->addItem(entity);
        entity->setParent(this);
        connect(entity,SIGNAL(deathSignal(Entity*)),this,SLOT(deleteDeadOne(Entity*)));
        if(entity->data(entityType)==checkPoint){
            CheckPoint* checkpoint=static_cast<CheckPoint*>(entity);
            //qDebug()<<"add checkpoint";
            connect(checkpoint,&CheckPoint::achieve,this,&GameScene::autoSave);
        }
        connect(entity,&Entity::addEntity,this,&GameScene::addEntity);
    }
    m_deadzone=new DeadZone(1600,300,800,1040,this);
    m_scene->addItem(m_deadzone);
    qDebug()<<"场景重置成功";
}

void GameScene::setUpUI(){
    m_titlebutton=new QPushButton("返回标题");
    m_titlebutton->setGeometry(1500,100,100,30);
    m_scene->addWidget(m_titlebutton);
    connect(m_titlebutton,SIGNAL(clicked()),this,SIGNAL(toTitle()));

}
GameScene::~GameScene(){

    delete  m_view;
}

QGraphicsView* GameScene::view(){
    return m_view;

}

QGraphicsScene* GameScene::scene(){
    return m_scene;
}
GameScene::GameScene(QString filename,QObject* parent):GameScene(parent){

    for(Entity* entity:MapReader::readMap(filename)){
        m_scene->addItem(entity);
        entity->setParent(this);
        connect(entity,SIGNAL(deathSignal(Entity*)),this,SLOT(deleteDeadOne(Entity*)));
        if(entity->data(entityType)==checkPoint){
            CheckPoint* checkpoint=static_cast<CheckPoint*>(entity);
            qDebug()<<"add checkpoint";
            connect(checkpoint,&CheckPoint::achieve,this,&GameScene::autoSave);
        }
        connect(entity,&Entity::addEntity,this,&GameScene::addEntity);
        for(auto child:entity->childItems()){
            child->setVisible(false);
        }
    }
}

void GameScene::saveScene(QString filename){
    if(filename.right(5)!=".json")
        filename+=".json";
    MapReader::writeMap(filename,m_scene->items());
    m_titlebutton->setVisible(false);
    m_view->grab(QRect(0,0,1600,900)).save("maps/"+filename.left(filename.size()-4)+"jpg");
    m_titlebutton->setVisible(true);
}




bool GameScene::eventFilter(QObject *watched, QEvent *event){
    if(event->type()==QEvent::MouseButtonPress){
        QMouseEvent* mouse_event=static_cast<QMouseEvent*>(event);
        //qDebug()<<mouse_event->x()<<mouse_event->y();
        return false;
    }
    return false;
}

void GameScene::changeSceneRect(int dx,int dy){
    //m_sceneRect.setX(m_sceneRect.x()+dx);
    //m_sceneRect.setY(m_sceneRect.y()+dy);
    if(m_moving)
        return;
    m_movex+=dx;
    m_movey+=dy;
    m_moving=true;
}
void GameScene::changeSceneRectNow(int dx, int dy){
    m_moving=false;
    m_movex=0;
    m_movey=0;
    changeSceneRect(dx,dy);
}
QRect GameScene::get_scene_rect()const{
    return m_sceneRect;
}

void GameScene::advance(){
    moveScene();

}

void GameScene::moveScene(){
    int dx=0,dy=0;
    if(m_movex>m_movespeed){
        m_movex-=m_movespeed;
        dx=m_movespeed;
    }
    else if(m_movex<-m_movespeed){
        m_movex+=m_movespeed;
        dx=-m_movespeed;
    }
    if(m_movey>m_movespeed){
        m_movey-=m_movespeed;
        dy=m_movespeed;
    }
    else if(m_movey<-m_movespeed){
        m_movey+=m_movespeed;
        dy=-m_movespeed;
    }
    if(!dx && !dy){
        m_moving=false;
    }
    m_sceneRect.setRect(m_sceneRect.x()+dx,m_sceneRect.y()+dy,1600,900);
    QRectF nowRect=m_titlebutton->geometry();
    m_titlebutton->setGeometry(nowRect.x()+dx,nowRect.y()+dy,nowRect.width(),nowRect.height());
    QPointF nowPoint=m_deadzone->pos();
    m_deadzone->setPos(nowPoint.x()+dx,nowPoint.y()+dy);
    m_view->setSceneRect(m_sceneRect);
}

void GameScene::addWorm1(){
    Worm1* worm1=new Worm1(m_sceneRect.x()+m_sceneRect.width()/2,
                           m_sceneRect.y()+m_sceneRect.height()/2,this);
    worm1->set_can_drag();
    m_scene->addItem(worm1);
}
void GameScene::addWorm2(){
    Worm2*worm2=new Worm2(m_sceneRect.x()+m_sceneRect.width()/2,
                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    worm2->set_can_drag();
    m_scene->addItem(worm2);
}
void GameScene::addNormalLand(int width,int height){
    NormalLand* normalland=new NormalLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    //qDebug()<<normalland->pos()<<m_sceneRect.x()<<m_sceneRect.y()<<m_sceneRect.width()<<m_sceneRect.height();
    normalland->set_can_drag();
    m_scene->addItem(normalland);
}
void GameScene::addSpikeLand(int width,int height,int attack){
    SpikeLand* spikeland=new SpikeLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                       m_sceneRect.y()+m_sceneRect.height()/2,attack,this);
    spikeland->set_can_drag();
    m_scene->addItem(spikeland);
}
void GameScene::deleteDeadOne(Entity* dead){
    m_scene->removeItem(dead);
    //delete  dead;

 }

void GameScene::addEntity(Entity* entity){
    m_scene->addItem(entity);
    connect(entity,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
    connect(entity,&Entity::addEntity,this,&GameScene::addEntity);
}


void GameScene::addCheckPoint(){
    CheckPoint* checkpoint=new CheckPoint(m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    checkpoint->set_can_drag();
    m_scene->addItem(checkpoint);
}
void GameScene::addGenerator(int type,int T){
    EnemyGenerator* generator=new EnemyGenerator(m_sceneRect.x()+m_sceneRect.width()/2,
                                                 m_sceneRect.y()+m_sceneRect.height()/2,
                                                 (EnemyType)type,T,this);
    generator->set_can_drag();
    m_scene->addItem(generator);

}

void GameScene::addMovingLand(int width,int height,int T){
    MovingLand* movingland=new MovingLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,T,this);
    movingland->set_can_drag();
    m_scene->addItem(movingland);
    m_scene->addItem(movingland->get_point()[0]);
    m_scene->addItem(movingland->get_point()[1]);
}
void GameScene::addMushroom(){
    Mushroom* mushroom=new Mushroom(m_sceneRect.x()+m_sceneRect.width()/2,
                                    m_sceneRect.y()+m_sceneRect.height()/2,this);
    mushroom->set_can_drag();
    m_scene->addItem(mushroom);
}
void GameScene::autoSave(Entity*checkpoint){
    m_lastpoint=static_cast<CheckPoint*>(checkpoint);
}

CheckPoint* GameScene::get_last_point(){
    return  m_lastpoint;
}

void GameScene::addSpringLand(){
    SpringLand* springland=new SpringLand(m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    springland->set_can_drag();
    m_scene->addItem(springland);
}
void GameScene::addFragileLand(int width,int height){
    FragileLand* fragileland=new FragileLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                             m_sceneRect.y()+m_sceneRect.height()/2,this);
    fragileland->set_can_drag();
    m_scene->addItem(fragileland);
}
