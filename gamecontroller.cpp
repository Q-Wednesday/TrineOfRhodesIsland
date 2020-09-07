#include"gamecontroller.h"
#include<QEvent>
#include<QKeyEvent>
#include"constant.h"
#include<QDebug>

GameController::GameController(QObject* parent):QObject(parent)
    ,m_gamescene(new GameScene(this))
    ,m_silver(new Silver(this))
  ,m_exusiai(new Exusiai(this))
{
    m_gamescene->view()->installEventFilter(this);
    m_player=m_silver;
    m_gamescene->scene()->addItem(m_player);
    m_gamescene->scene()->addItem(m_exusiai);
    m_exusiai->setVisible(false);
    m_exusiai->setEnabled(false);
    m_characters.push_back(m_silver);
    m_characters.push_back(m_exusiai);
    connect(m_exusiai,&Entity::addEntity,m_gamescene,&GameScene::addEntity);
    /*
    NormalLand* land=new NormalLand;
    m_gamescene->scene()->addItem(land);
    NormalLand*land2=new NormalLand(200,200,400,700);
    m_gamescene->scene()->addItem(land2);
    NormalLand*land3=new NormalLand(100,500,100,700);
    m_gamescene->scene()->addItem(land3);
    */
   // m_gamescene->saveScene("savetest.json");
}
GameController::GameController(QString mapName,QObject*parent):
    QObject(parent),m_gamescene(new GameScene(mapName,this)),m_silver(new Silver(this)),
m_exusiai(new Exusiai(this)){
    m_gamescene->view()->installEventFilter(this);
    //m_player=m_exusiai;
    m_player=m_silver;
    m_gamescene->scene()->addItem(m_silver);
    m_gamescene->scene()->addItem(m_exusiai);
    m_exusiai->setVisible(false);
    m_exusiai->setEnabled(false);
    //m_silver->setVisible(false);
   // m_silver->setEnabled(false);
    m_characters.push_back(m_silver);
    m_characters.push_back(m_exusiai);
    //能天使连接槽
    connect(m_exusiai,&Entity::addEntity,m_gamescene,&GameScene::addEntity);
    connect(m_silver,&Entity::deathSignal,this,&GameController::resetPlayer);
    connect(m_exusiai,&Entity::deathSignal,this,&GameController::resetPlayer);
}
void GameController::reset(QString filename){
    m_gamescene->reset(filename);
    m_silver=new Silver(this);
    m_exusiai=new Exusiai(this);
    m_player=m_silver;
    m_characters.clear();
    m_characters.push_back(m_silver);
    m_characters.push_back(m_exusiai);
    m_gamescene->scene()->addItem(m_silver);
    m_gamescene->scene()->addItem(m_exusiai);
    connect(m_exusiai,&Entity::addEntity,m_gamescene,&GameScene::addEntity);
    connect(m_silver,&Entity::deathSignal,this,&GameController::resetPlayer);
    connect(m_exusiai,&Entity::deathSignal,this,&GameController::resetPlayer);

    m_exusiai->setVisible(false);
    m_exusiai->setEnabled(false);

    //m_player->setPos(100,100);
}
GameController::~GameController(){
    qDebug()<<"delete controller";
}



bool GameController::eventFilter(QObject *watched, QEvent *event){

    if(event->type()==QEvent::KeyPress){
        QKeyEvent* key_event=static_cast<QKeyEvent*>(event);
        dealKeyPress(key_event);
        return true;
    }
    else if(event->type()==QEvent::KeyRelease){
        QKeyEvent* key_event=static_cast<QKeyEvent*>(event);
        dealKeyRelease(key_event);
        return true;
    }
    return false;
}

void GameController::dealKeyPress(QKeyEvent *event){

    switch (event->key()) {
    case Qt::Key_D:

    case Qt::Key_Right:

        m_player->move(moveRight);
        break;
    case Qt::Key_A:

    case Qt::Key_Left:
        m_player->move(moveLeft);
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        m_player->jump();
        break;
     case Qt::Key_J:
        m_player->attack();
        break;
    }
}


GameScene* GameController::get_scene(){
    return m_gamescene;
}

void GameController::dealKeyRelease(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_D:

    case Qt::Key_Right:

        m_player->move(cancelRight);
        break;
    case Qt::Key_A:

    case Qt::Key_Left:
        m_player->move(cancelLeft);
        break;
    case Qt::Key_E:
        nextCharacter();
        break;
    case Qt::Key_Q:
        preCharacter();
        break;
    }
}


void GameController::advance(){
    //是否移动视角
    QRect now_rect=m_gamescene->get_scene_rect();
    int dx=m_player->x()-now_rect.x();


    if(dx>now_rect.width()*3/4){

        m_gamescene->changeSceneRect(dx-now_rect.width()*1/3,0);
    }



}

void GameController::nextCharacter(){
    m_player->setVisible(false);
    m_player->setEnabled(false);
    m_player->setAdvanceEnanbled(false);
    QPointF now_pos=m_player->pos();
    int next_num=(m_player->data(detailType).toInt()+1)%2;
    m_player=m_characters[next_num];

    while (!m_player->check_alive()) {
        m_player=m_characters[(next_num+1)%2];
    }
    m_player->setPos(now_pos);
    m_player->setVisible(true);
    m_player->setEnabled(true);
    m_player->setAdvanceEnanbled(true);
    m_player->set_speed(0);
    m_player->get_animemanager()->changeMode(relaxMode);

}

void GameController::preCharacter(){
    m_player->setVisible(false);
    m_player->setEnabled(false);
    m_player->setAdvanceEnanbled(false);
    QPointF now_pos=m_player->pos();
    //之后要改
    int next_num=(m_player->data(detailType).toInt()+1)%2;
    m_player=m_characters[next_num];
    if(!m_player->check_alive())
        return preCharacter();
    m_player->setPos(now_pos);
    m_player->setVisible(true);
    m_player->setEnabled(true);
    m_player->setAdvanceEnanbled(true);
    m_player->set_speed(0);
    m_player->get_animemanager()->changeMode(relaxMode);
}
void GameController::resetPlayer(Entity* deadone){
   // qDebug()<<"reset";
    if(!m_exusiai->check_alive() && !m_silver->check_alive())
    {
        m_exusiai->set_hp(m_exusiai->get_maxhp()/2);
        m_silver->set_hp(m_silver->get_maxhp()/2);
        CheckPoint* point=m_gamescene->get_last_point();
        if(point)
        {
            m_exusiai->setPos(point->pos());
            m_silver->setPos(point->pos());
            QRect now_rect=m_gamescene->get_scene_rect();
            m_gamescene->changeSceneRectNow(point->pos().x()-now_rect.x()-800,0);
        }
        else{
            m_exusiai->setPos(100,100);
            m_silver->setPos(100,100);
            QRect now_rect=m_gamescene->get_scene_rect();
            m_gamescene->changeSceneRectNow(-now_rect.x(),0);
        }
        m_player->setEnabled(true);
        m_player->setAdvanceEnanbled(true);
    }
    else{

        nextCharacter();
    }

}
