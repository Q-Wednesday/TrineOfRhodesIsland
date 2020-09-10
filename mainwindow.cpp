#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QGraphicsView>
#include<QGraphicsScene>

#include"gamecontroller.h"
#include"gamescene.h"
#include"editortab.h"
#include<QDockWidget>
#include<QDebug>
#include<QScreen>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_title(new TitleScene)
    ,m_selectscene(nullptr)
    ,m_editorscene(nullptr)
    ,m_controller(nullptr)
    ,m_winscene(new WinScene)
    ,m_loadingscene(new LoadingScene)
    ,m_player(new QMediaPlayer(this))
    ,m_bgm_list(new QMediaPlaylist(this))
    ,m_next_scene(nullptr)
    ,m_losescene(new LoseScene)
    ,m_adventurescene(new AdventureScene)
{
    QScreen* screen=QGuiApplication::primaryScreen();
    QRect screensize=screen->availableGeometry();
    if(screensize.width()<=1920)
        showFullScreen();
    else{
        setFixedSize(1920,1080);
    }
    m_timer=new QTimer;
    m_timer->start(1000/33);
    ui->setupUi(this);
    //setMinimumSize(1600,900);

    setWindowTitle("TrineOfRhodesIsland-三位一体:罗德岛");
    setCentralWidget(m_title);
    connect(m_title,&TitleScene::toDesign,this,&MainWindow::toEditorScene);
    connect(m_title,&TitleScene::toSelect,this,&MainWindow::toSelectScene);
    connect(m_title,&TitleScene::toAdventure,this,&MainWindow::toAdventureScene);
    connect(m_winscene,&WinScene::toTitle,this,&MainWindow::toTitle);
    connect(m_losescene,&LoseScene::toTitle,this,&MainWindow::toTitle);
    connect(m_loadingscene,&LoadingScene::loadingFinish,this,&MainWindow::toNextScene);
    connect(m_timer,&QTimer::timeout,m_loadingscene,&LoadingScene::advance);
    connect(m_adventurescene,&AdventureScene::toLevel,this,&MainWindow::toMyScene);
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/main"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/fight"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/edit"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/win"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/lose"));

    m_bgm_list->setCurrentIndex(0);
    m_player->setPlaylist(m_bgm_list);
    m_bgm_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    m_player->play();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toEditorScene(){
    //m_loadingscene->reset_tick();
    //takeCentralWidget();
    //setCentralWidget(m_loadingscene);

    m_bgm_list->setCurrentIndex(2);
    if(m_editorscene==nullptr){
        m_editorscene=new EditorScene;
        //editor
        //qDebug()<<"开始链结";
        connect(m_timer,&QTimer::timeout,m_editorscene->get_scene(),&GameScene::advance);
        connect(m_editorscene,&EditorScene::toTitle,this,&MainWindow::toTitle);
        connect(m_editorscene,&EditorScene::startPlay,this,&MainWindow::toMyScene);
        connect(m_editorscene->get_scene(),&GameScene::toTitle,this,&MainWindow::toTitle);
        //connect(m_editorscene->get_scene(),&GameScene::loadingFinished,this,&MainWindow::toNextScene);
        //qDebug()<<"连接完成";
        //m_editorscene->reset();
    }
    else{
        m_editorscene->reset();
    }
    //m_next_scene=m_editorscene;
    takeCentralWidget();
    setCentralWidget(m_editorscene);
    //m_loadingscene->setVisible(false);
    //takeCentralWidget();
    //setCentralWidget(m_editorscene);
    //delete m_controller;


}
void MainWindow::toReEditScene(QString filename){
    m_loadingscene->reset_tick();
    takeCentralWidget();
    setCentralWidget(m_loadingscene);

    m_bgm_list->setCurrentIndex(2);
    m_player->play();
    qDebug()<<"re edit";
    if(m_editorscene==nullptr){
        m_editorscene=new EditorScene;
        //editor
        connect(m_timer,&QTimer::timeout,m_editorscene->get_scene(),&GameScene::advance);
        connect(m_editorscene,&EditorScene::toTitle,this,&MainWindow::toTitle);
        connect(m_editorscene,&EditorScene::startPlay,this,&MainWindow::toMyScene);
        connect(m_editorscene->get_scene(),&GameScene::toTitle,this,&MainWindow::toTitle);
        connect(m_editorscene->get_scene(),&GameScene::loadingFinished,this,&MainWindow::toNextScene);
    }

    m_editorscene->loadMap(filename);
    m_next_scene=m_editorscene;


   // qDebug()<<"成功进入 reedit";
}
void MainWindow::pause(){
    GameScene* gamescene=m_controller->get_scene();
    disconnect(m_timer,&QTimer::timeout,gamescene->scene(),&QGraphicsScene::advance);
    disconnect(m_timer,&QTimer::timeout,m_controller,&GameController::advance);
    disconnect(m_timer,&QTimer::timeout,gamescene,&GameScene::advance);
}
void MainWindow::resume(){
     GameScene* gamescene=m_controller->get_scene();
     connect(m_timer,&QTimer::timeout,gamescene->scene(),&QGraphicsScene::advance);
     connect(m_timer,&QTimer::timeout,m_controller,&GameController::advance);
     connect(m_timer,&QTimer::timeout,gamescene,&GameScene::advance);
}
void MainWindow::toMyScene(QString filename){
    m_loadingscene->reset_tick();
    takeCentralWidget();
    setCentralWidget(m_loadingscene);

    m_bgm_list->setCurrentIndex(1);
    m_player->play();
    GameScene* gamescene;
    if(m_controller==nullptr)
    {
        m_controller=new GameController(filename,this);
        qDebug()<<"成功创建管理器";
        gamescene=m_controller->get_scene();
        /*
        connect(m_timer,&QTimer::timeout,gamescene->scene(),&QGraphicsScene::advance);
        connect(m_timer,&QTimer::timeout,m_controller,&GameController::advance);
        connect(m_timer,&QTimer::timeout,gamescene,&GameScene::advance);
        */
        resume();
        connect(gamescene,&GameScene::toTitle,this,&MainWindow::toTitle);
        connect(m_controller,&GameController::toWinScene,this,&MainWindow::toWinScene);
        connect(m_controller,&GameController::toLoseScene,this,&MainWindow::toLoseScene);
        //connect(gamescene,&GameScene::loadingFinished,this,&MainWindow::toNextScene);
        m_next_scene=gamescene->view();
    }

    else{
        resume();
        m_controller->reset(filename);
        gamescene=m_controller->get_scene();
        m_next_scene=gamescene->view();
    }
    //m_loadingscene->setVisible(false);


    // delete m_editorscene;


    //connect(scene,&QGraphicsScene::changed,view,&QGraphicsView::updateScene);

}
void MainWindow::toSelectScene(){

    qDebug()<<"select scene";
    if(m_selectscene==nullptr){
        qDebug()<<"no select";
        m_selectscene=new SelectMapScene(this);
        qDebug()<<"new select";
        connect(m_selectscene,&SelectMapScene::openMap,this,&MainWindow::toMyScene);
        connect(m_selectscene,SIGNAL(editMap(QString)),this,SLOT(toReEditScene(QString)));
        connect(m_selectscene,&SelectMapScene::toTitle,this,&MainWindow::toTitle);

    }
    qDebug()<<"reset select scene";
    m_selectscene->reset();
    qDebug()<<"reset";
    takeCentralWidget();
    setCentralWidget(m_selectscene);




}

void MainWindow::toTitle(){
    if(m_controller)
        pause();
    m_bgm_list->setCurrentIndex(0);
    m_player->play();
    takeCentralWidget();
    setCentralWidget(m_title);


}

void MainWindow::toWinScene(int score,int secs){
    pause();
    m_bgm_list->setCurrentIndex(3);
    m_player->play();
    m_winscene->setResult(score,secs);
    takeCentralWidget();
    setCentralWidget(m_winscene);
}

void MainWindow::toNextScene(){
    qDebug()<<"to next";
    if(m_next_scene)
    {
         qDebug()<<"next";
        takeCentralWidget();
        setCentralWidget(m_next_scene);
    }
}

void MainWindow::toLoseScene(int secs){
    pause();
    m_bgm_list->setCurrentIndex(4);
    m_player->play();
    m_losescene->setTime(secs);
    takeCentralWidget();
    setCentralWidget(m_losescene);


}


void MainWindow::toAdventureScene(){
    takeCentralWidget();
    setCentralWidget(m_adventurescene);
}
