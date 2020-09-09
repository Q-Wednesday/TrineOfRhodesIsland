#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QGraphicsView>
#include<QGraphicsScene>

#include"gamecontroller.h"
#include"gamescene.h"
#include"editortab.h"
#include<QDockWidget>
#include<QDebug>
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
{
    m_timer=new QTimer;
    m_timer->start(1000/33);
    ui->setupUi(this);
    setMinimumSize(1600,900);
    setGeometry(0,0,1920,1080);
/*
    GameController* controller=new GameController;
    GameScene* gamescene=controller->get_scene();

    setCentralWidget(gamescene->view());

    QTimer* timer=new QTimer;
    connect(timer,&QTimer::timeout,gamescene->scene(),&QGraphicsScene::advance);
    //connect(scene,&QGraphicsScene::changed,view,&QGraphicsView::updateScene);
    timer->start(1000/33);
*/
   // EditorScene* editorscene=new EditorScene;
   // setCentralWidget(editorscene);
    setWindowTitle("TrineOfRhodesIsland");
    setCentralWidget(m_title);
    connect(m_title,&TitleScene::toDesign,this,&MainWindow::toEditorScene);
    connect(m_title,&TitleScene::toSelect,this,&MainWindow::toSelectScene);
    connect(m_winscene,&WinScene::toTitle,this,&MainWindow::toTitle);
    connect(m_loadingscene,&LoadingScene::loadingFinish,this,&MainWindow::toNextScene);
    connect(m_timer,&QTimer::timeout,m_loadingscene,&LoadingScene::advance);
    //connect(m_selectscene,&SelectMapScene::openMap,this,&MainWindow::toMyScene);
   //connect(m_selectscene,SIGNAL(editMap(QString)),this,SLOT(toReEditScene(QString)));

    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/main"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/fight"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/edit"));
    m_bgm_list->addMedia(QUrl("qrc:/sound/bgm/win"));


    m_bgm_list->setCurrentIndex(0);
    m_player->setPlaylist(m_bgm_list);
    m_bgm_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    //m_player->setMedia(QUrl("qrc:/sound/bgm/main"));
    m_player->play();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toEditorScene(){
    m_loadingscene->reset_tick();
    takeCentralWidget();
    setCentralWidget(m_loadingscene);

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
    m_next_scene=m_editorscene;
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
        connect(m_timer,&QTimer::timeout,gamescene->scene(),&QGraphicsScene::advance);
        connect(m_timer,&QTimer::timeout,m_controller,&GameController::advance);
        connect(m_timer,&QTimer::timeout,gamescene,&GameScene::advance);
        connect(gamescene,&GameScene::toTitle,this,&MainWindow::toTitle);
        connect(gamescene,&GameScene::toWinScene,this,&MainWindow::toWinScene);
        connect(gamescene,&GameScene::toWinScene,this,&MainWindow::toWinScene);
        //connect(gamescene,&GameScene::loadingFinished,this,&MainWindow::toNextScene);
        m_next_scene=gamescene->view();
    }

    else{
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


    }
    qDebug()<<"reset select scene";
    m_selectscene->reset();
    qDebug()<<"reset";
    takeCentralWidget();
    setCentralWidget(m_selectscene);




}

void MainWindow::toTitle(){

    m_bgm_list->setCurrentIndex(1-m_bgm_list->currentIndex());
    m_player->play();
    takeCentralWidget();
    setCentralWidget(m_title);


}

void MainWindow::toWinScene(){
    m_bgm_list->setCurrentIndex(3);
    m_player->play();
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
