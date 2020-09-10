#include"gamecontroller.h"
#include<QEvent>
#include<QKeyEvent>
#include"constant.h"
#include<QDebug>

GameController::GameController(QObject* parent):QObject(parent)
    ,m_gamescene(new GameScene(this))
    ,m_silver(new Silver(this))
  ,m_exusiai(new Exusiai(this))
  ,m_sheep(new Sheep(this))
  ,m_score(1000)
{
    m_gamescene->view()->installEventFilter(this);
    m_player=m_silver;
    set_character();
    m_start_time=QTime::currentTime();
    connect(m_gamescene,&GameScene::toWinScene,this,&GameController::winGame);
    connect(m_gamescene,&GameScene::achieveCheckPoint,this,&GameController::achieveCheckPoint);
    connect(this,&GameController::changeScore,m_gamescene,&GameScene::changeScore);
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
void GameController::set_character(){
    m_score=1000;
    m_characters.clear();
    m_gamescene->scene()->addItem(m_player);
    m_gamescene->scene()->addItem(m_exusiai);
    m_gamescene->scene()->addItem(m_sheep);
    m_exusiai->setVisible(false);
    m_exusiai->setEnabled(false);
    m_exusiai->setAdvanceEnanbled(false);
    m_sheep->setVisible(false);
    m_sheep->setEnabled(false);
    m_sheep->setAdvanceEnanbled(false);
    m_characters.push_back(m_silver);
    m_characters.push_back(m_exusiai);
    m_characters.push_back(m_sheep);
    connect(m_exusiai,&Entity::addEntity,m_gamescene,&GameScene::addEntity);
    connect(m_sheep,&Entity::addEntity,m_gamescene,&GameScene::addEntity);
    connect(m_silver,&Entity::deathSignal,this,&GameController::resetPlayer);
    connect(m_exusiai,&Entity::deathSignal,this,&GameController::resetPlayer);
    connect(m_sheep,&Entity::deathSignal,this,&GameController::resetPlayer);
}
GameController::GameController(QString mapName,QObject*parent):
    QObject(parent),m_gamescene(new GameScene(mapName,this)),m_silver(new Silver(this)),
m_exusiai(new Exusiai(this)),m_sheep(new Sheep(this)){
    m_gamescene->view()->installEventFilter(this);
    //m_player=m_exusiai;
    //qDebug()<<"1";
    m_player=m_silver;
    qDebug()<<"set character";
    set_character();
    m_start_time=QTime::currentTime();
    connect(m_gamescene,&GameScene::toWinScene,this,&GameController::winGame);
    connect(m_gamescene,&GameScene::achieveCheckPoint,this,&GameController::achieveCheckPoint);
    connect(this,&GameController::changeScore,m_gamescene,&GameScene::changeScore);
}
void GameController::reset(QString filename){
    //qDebug()<<"reset start";
    m_gamescene->reset(filename);

    m_silver=new Silver(this);
    m_exusiai=new Exusiai(this);
    m_sheep=new Sheep(this);
    m_player=m_silver;
    qDebug()<<"set character";
    set_character();
    m_start_time=QTime::currentTime();
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
    case Qt::Key_K:
        m_player->skill();
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

    //qDebug()<<m_silver->get_hp()<<m_exusiai->get_hp()<<m_sheep->get_hp();
    if(dx>now_rect.width()*3/4){

        m_gamescene->changeSceneRect(dx-now_rect.width()*1/3,0);
    }
    //qDebug()<<m_score;
    if(m_score<0)
        emit toLoseScene(m_start_time.secsTo(QTime::currentTime()));

}

void GameController::nextCharacter(){
    m_player->setVisible(false);
    m_player->setEnabled(false);
    m_player->setAdvanceEnanbled(false);
    QPointF now_pos=m_player->pos();
    int next_num=(m_player->data(detailType).toInt()+1)%3;
    m_player=m_characters[next_num];

    while (!m_player->check_alive()) {
        next_num++;
        m_player=m_characters[next_num%3];
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
    int next_num=(m_player->data(detailType).toInt()+2)%3;
    m_player=m_characters[next_num];
    while (!m_player->check_alive()) {
        next_num+=2;
        m_player=m_characters[next_num%3];
    }
    m_player->setPos(now_pos);
    m_player->setVisible(true);
    m_player->setEnabled(true);
    m_player->setAdvanceEnanbled(true);
    m_player->set_speed(0);
    m_player->get_animemanager()->changeMode(relaxMode);
}
void GameController::resetPlayer(Entity* deadone){
   // qDebug()<<"reset";
    if(!m_exusiai->check_alive() && !m_silver->check_alive()&&!m_sheep->check_alive())
    {
        //三人同时死亡，扣除100分
        m_score-=100;
        m_exusiai->set_hp(m_exusiai->get_maxhp()/2);
        m_silver->set_hp(m_silver->get_maxhp()/2);
        m_sheep->set_hp(m_sheep->get_maxhp()/2);
        CheckPoint* point=m_gamescene->get_last_point();
        if(point)
        {
            m_exusiai->setPos(point->pos());
            m_silver->setPos(point->pos());
            m_sheep->setPos(point->pos());
            QRect now_rect=m_gamescene->get_scene_rect();
            m_gamescene->changeSceneRectNow(point->pos().x()-now_rect.x()-800,0);
        }
        else{
            m_exusiai->setPos(400,0);
            m_silver->setPos(400,0);
            m_sheep->setPos(400,0);
            QRect now_rect=m_gamescene->get_scene_rect();
            m_gamescene->changeSceneRectNow(-now_rect.x(),0);
        }
        m_player->setEnabled(true);
        m_player->setAdvanceEnanbled(true);
    }
    else{
        m_score-=50;//死亡单个角色扣50分
        emit changeScore(m_score);
        nextCharacter();
    }

}

void GameController::achieveCheckPoint(){
    for(auto character:m_characters){
        if(!character->check_alive()){
            character->set_hp(character->get_maxhp()/2);
            qDebug()<<"die";
        }
        else{
            m_score+=25;//有一个活着就加25
            emit changeScore(m_score);
        }
    }
}

void GameController::winGame(){
    emit toWinScene(m_score,m_start_time.secsTo(QTime::currentTime()));
}
