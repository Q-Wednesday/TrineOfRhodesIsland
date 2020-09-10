#include"gamescene.h"
#include"mapreader.h"
#include<QDebug>
#include<QMouseEvent>
#include<QEvent>
#include<QTime>

GameScene::GameScene(QObject* parent):QObject(parent),m_scene(new QGraphicsScene(this))
  ,m_view(new QGraphicsView())
  ,m_sceneRect(QRect(0,0,1920,1080))
  ,m_can_edit(false)
  ,m_movex(0)
  ,m_movey(0)
  ,m_movespeed(8)
  ,m_moving(false)
  ,m_lastpoint(nullptr)
{
    setUpBg();
    m_view->setScene(m_scene);
    m_view->setSceneRect(m_sceneRect);
    //关闭滚动条
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_view->installEventFilter(this);
    m_view->setFocus();

    //m_view->setTransform(QTransform().scale(1.25,1.25));
    setUpUI();
    qDebug()<<"loading finished";
    emit loadingFinished();

}
void GameScene::resetScene(){

    m_scene->clear();

    m_sceneRect=QRect(0,0,1920,1080);
    m_movex=0;
    m_movey=0;
    m_moving=false;
    m_lastpoint=nullptr;

}
void GameScene::reset(){

    resetScene();
    setUpBg();
    setUpUI();
    emit loadingFinished();
}
void GameScene::setUpBg(){
    m_left_bg=new QLabel;
    m_right_bg=new QLabel;
    m_left_bg->setGeometry(0,0,1920,1080);
    m_right_bg->setGeometry(1920,0,1920,1080);

    m_left_bg->setPixmap(QPixmap(":/images/bg").transformed(QTransform().scale(1.5,1.5)));
    m_right_bg->setPixmap(QPixmap(":/images/bg").transformed(QTransform().rotate(180,Qt::YAxis)
                                                             .scale(1.5,1.5)));
    m_scene->addWidget(m_left_bg);
    m_scene->addWidget(m_right_bg);
}
void GameScene::reset(QString filename){

    resetScene();
    setUpBg();
    for(Entity* entity:MapReader::readMap(filename)){
        //qDebug()<<"add"<<entity->data(entityType);
        m_scene->addItem(entity);
        entity->setParent(this);
        connect(entity,SIGNAL(deathSignal(Entity*)),this,SLOT(deleteDeadOne(Entity*)));
        if(entity->data(entityType)==checkPoint){
            CheckPoint* checkpoint=static_cast<CheckPoint*>(entity);
            //qDebug()<<"add checkpoint";
            connect(checkpoint,&CheckPoint::achieve,this,&GameScene::autoSave);
            connect(checkpoint,&CheckPoint::achievefinal,this,&GameScene::toWinScene);
        }
        if(entity->data(detailType)==hintLand){
            HintLand* hintland=static_cast<HintLand*>(entity);
            connect(hintland,&HintLand::showHint,this,&GameScene::showHint);
        }
        connect(entity,&Entity::addEntity,this,&GameScene::addEntity);
        for(auto child:entity->childItems()){
            if(child->data(entityType)==airWall)
                child->setVisible(false);
        }
    }

    setUpUI();
    //qDebug()<<"场景重置成功";
    emit loadingFinished();
}
void GameScene::loadMap(QString filename){
    resetScene();
    setUpBg();
    //movingland需要特化修改
    for(Entity* entity:MapReader::readMap(filename)){


        m_scene->addItem(entity);
        //entity->setParent(this);
        entity->set_can_drag();
        connect(entity,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
        if(entity->data(entityType)==landType&& entity
                ->data(detailType)==movingLand){
            MovingLand* movingland=static_cast<MovingLand*>(entity);
            movingland->add_mark_point();
            m_scene->addItem(movingland->get_point()[0]);
            m_scene->addItem(movingland->get_point()[1]);
        }
    }
    setUpUI();
    //qDebug()<<"加载完毕";
    emit loadingFinished();
}
void GameScene::setUpUI(){
    m_deadzone=new DeadZone(3000,300,960,1300,this);
    m_scene->addItem(m_deadzone);
    m_titlebutton=new QPushButton("返回标题");
    m_titlebutton->setGeometry(1500,100,100,30);
    m_hintlabel=new QLabel();
    m_hintlabel->setGeometry(600,0,600,300);
    m_hintlabel->setWordWrap(true);
    QPalette pa;

    pa.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    m_hintlabel->setPalette(pa);
    m_hintlabel->setStyleSheet("color:white;font-size:20px;");

    m_score_label=new QLabel("得分:1000");
    m_score_label->setGeometry(400,100,200,100);
    m_score_label->setPalette(pa);
    m_score_label->setStyleSheet("color:white;font-size:20px;");
    m_scene->addWidget(m_titlebutton);
    m_scene->addWidget(m_hintlabel);
    m_scene->addWidget(m_score_label);
    connect(m_titlebutton,SIGNAL(clicked()),this,SIGNAL(toTitle()));

}
GameScene::~GameScene(){

    delete  m_view;
    qDebug()<<"删除gamescene";
}

QGraphicsView* GameScene::view(){
    return m_view;

}

QGraphicsScene* GameScene::scene(){
    return m_scene;
}
GameScene::GameScene(QString filename,QObject* parent):GameScene(parent){

    reset(filename);
    qDebug()<<"gamescene加载完成";
}

void GameScene::saveScene(QString filename){
    if(filename.right(5)!=".json")
        filename+=".json";
    MapReader::writeMap(filename,m_scene->items());
    m_titlebutton->setVisible(false);
    m_view->grab(QRect(0,0,1600,900)).save("maps/"+filename.left(filename.size()-4)+"jpg");
    m_titlebutton->setVisible(true);
}
void GameScene::changeScore(int score){
    m_score_label->setText(QString("得分:%1").arg(score));
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
    m_sceneRect.setRect(m_sceneRect.x()+dx,m_sceneRect.y()+dy,1920,1080);
    QRectF nowRect=m_titlebutton->geometry();
    m_titlebutton->setGeometry(nowRect.x()+dx,nowRect.y()+dy,nowRect.width(),nowRect.height());
    QPointF nowPoint=m_deadzone->pos();
    m_deadzone->setPos(nowPoint.x()+dx,nowPoint.y()+dy);
    nowRect=m_hintlabel->geometry();
    m_hintlabel->setGeometry(nowRect.x()+dx,nowRect.y()+dy,nowRect.width(),nowRect.height());
    nowRect=m_score_label->geometry();
    m_score_label->setGeometry(nowRect.x()+dx,nowRect.y()+dy,nowRect.width(),nowRect.height());
    nowRect=m_left_bg->geometry();
    if(nowRect.x()+1920<=m_sceneRect.x()){
        m_left_bg->setGeometry(nowRect.x()+3840,0,1920,1080);
    }
    else if(nowRect.x()-1920>=m_sceneRect.x()){
        m_left_bg->setGeometry(nowRect.x()-3840,0,1920,1080);
    }
    nowRect=m_right_bg->geometry();
    if(nowRect.x()+1920<m_sceneRect.x()){
        m_right_bg->setGeometry(nowRect.x()+3840,0,1920,1080);
    }
    else if(nowRect.x()-1920>m_sceneRect.x()){
        m_right_bg->setGeometry(nowRect.x()-3840,0,1920,1080);
    }
    m_view->setSceneRect(m_sceneRect);
}

void GameScene::addWorm1(){
    Worm1* worm1=new Worm1(m_sceneRect.x()+m_sceneRect.width()/2,
                           m_sceneRect.y()+m_sceneRect.height()/2,this);
    worm1->set_can_drag();
    m_scene->addItem(worm1);
    connect(worm1,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addWorm2(){
    Worm2*worm2=new Worm2(m_sceneRect.x()+m_sceneRect.width()/2,
                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    worm2->set_can_drag();
    m_scene->addItem(worm2);
    connect(worm2,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addWorm3(){
    Worm3* worm3=new Worm3(m_sceneRect.x()+m_sceneRect.width()/2,
                           m_sceneRect.y()+m_sceneRect.height()/2,this);
    worm3->set_can_drag();
    m_scene->addItem(worm3);
    connect(worm3,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addNormalLand(int width,int height){
    NormalLand* normalland=new NormalLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    //qDebug()<<normalland->pos()<<m_sceneRect.x()<<m_sceneRect.y()<<m_sceneRect.width()<<m_sceneRect.height();
    normalland->set_can_drag();
    m_scene->addItem(normalland);
    connect(normalland,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addSpikeLand(int width,int height,int attack){
    SpikeLand* spikeland=new SpikeLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                       m_sceneRect.y()+m_sceneRect.height()/2,attack,this);
    spikeland->set_can_drag();
    m_scene->addItem(spikeland);
    connect(spikeland,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
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
                                          m_sceneRect.y()+m_sceneRect.height()/2,false,this);
    checkpoint->set_can_drag();
    m_scene->addItem(checkpoint);
    connect(checkpoint,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addDestination(){
    CheckPoint* checkpoint=new CheckPoint(m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,true,this);
    checkpoint->set_can_drag();
    m_scene->addItem(checkpoint);
    connect(checkpoint,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addGenerator(int type,int T){
    EnemyGenerator* generator=new EnemyGenerator(m_sceneRect.x()+m_sceneRect.width()/2,
                                                 m_sceneRect.y()+m_sceneRect.height()/2,
                                                 (EnemyType)type,T,this);
    generator->set_can_drag();
    m_scene->addItem(generator);
    connect(generator,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addHidenTrap(int T){
    HidenTrap* hidentrap=new HidenTrap(m_sceneRect.x()+m_sceneRect.width()/2,
                                       m_sceneRect.y()+m_sceneRect.height()/2,
                                       T,this);
    hidentrap->set_can_drag();
    m_scene->addItem(hidentrap);
    connect(hidentrap,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addMovingLand(int width,int height,int T){
    MovingLand* movingland=new MovingLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,T,this);
    movingland->set_can_drag();
    m_scene->addItem(movingland);
    m_scene->addItem(movingland->get_point()[0]);
    m_scene->addItem(movingland->get_point()[1]);
    connect(movingland,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addMushroom(){
    Mushroom* mushroom=new Mushroom(m_sceneRect.x()+m_sceneRect.width()/2,
                                    m_sceneRect.y()+m_sceneRect.height()/2,this);
    mushroom->set_can_drag();
    m_scene->addItem(mushroom);
    connect(mushroom,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addFlower(){
    Flower* aflower=new Flower(m_sceneRect.x()+m_sceneRect.width()/2,
                               m_sceneRect.y()+m_sceneRect.height()/2,this);
    aflower->set_can_drag();
    m_scene->addItem(aflower);
    connect(aflower,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::autoSave(Entity*checkpoint){
    m_lastpoint=static_cast<CheckPoint*>(checkpoint);
    if(!m_lastpoint->is_checked()){
        //没有check过，奖励
        m_lastpoint->set_checked();
        emit achieveCheckPoint();
    }
}

CheckPoint* GameScene::get_last_point(){
    return  m_lastpoint;
}

void GameScene::addSpringLand(){
    SpringLand* springland=new SpringLand(m_sceneRect.x()+m_sceneRect.width()/2,
                                          m_sceneRect.y()+m_sceneRect.height()/2,this);
    springland->set_can_drag();
    m_scene->addItem(springland);
    connect(springland,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::addFragileLand(int width,int height){
    FragileLand* fragileland=new FragileLand(width,height,m_sceneRect.x()+m_sceneRect.width()/2,
                                             m_sceneRect.y()+m_sceneRect.height()/2,this);
    fragileland->set_can_drag();
    m_scene->addItem(fragileland);
    connect(fragileland,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}

void GameScene::addHintLand(QString hint){
    HintLand* hintLand=new HintLand(100,100,m_sceneRect.x()+m_sceneRect.width()/2,
                                    m_sceneRect.y()+m_sceneRect.height()/2,hint,this);
    hintLand->set_can_drag();
    m_scene->addItem(hintLand);
    connect(hintLand,&Entity::deathSignal,this,&GameScene::deleteDeadOne);
}
void GameScene::showHint(QString hint){
    m_hintlabel->setText(hint);
}
