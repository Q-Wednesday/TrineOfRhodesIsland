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
    ,m_selectscene(new SelectMapScene)
    ,m_editorscene(nullptr)
    ,m_controller(nullptr)
{
    m_timer=new QTimer;
    m_timer->start(1000/33);
    ui->setupUi(this);
    setMinimumSize(1600,900);
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
    connect(m_selectscene,&SelectMapScene::openMap,this,&MainWindow::toMyScene);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toEditorScene(){

    if(m_editorscene==nullptr){
        m_editorscene=new EditorScene;
        //editor
        connect(m_timer,&QTimer::timeout,m_editorscene->get_scene(),&GameScene::advance);
        connect(m_editorscene,&EditorScene::toTitle,this,&MainWindow::toTitle);
        connect(m_editorscene,&EditorScene::startPlay,this,&MainWindow::toMyScene);
        connect(m_editorscene->get_scene(),&GameScene::toTitle,this,&MainWindow::toTitle);
    }
    else{
        m_editorscene->reset();
    }
    takeCentralWidget();
    setCentralWidget(m_editorscene);

    //delete m_controller;


}

void MainWindow::toMyScene(QString filename){
    if(m_controller==nullptr)
    {
        m_controller=new GameController(filename,this);
        GameScene* gamescene=m_controller->get_scene();
        connect(m_timer,&QTimer::timeout,gamescene->scene(),&QGraphicsScene::advance);
        connect(m_timer,&QTimer::timeout,m_controller,&GameController::advance);
        connect(m_timer,&QTimer::timeout,gamescene,&GameScene::advance);
        connect(gamescene,&GameScene::toTitle,this,&MainWindow::toTitle);
        takeCentralWidget();
        setCentralWidget(gamescene->view());
    }

    else{
        m_controller->reset(filename);
        GameScene* gamescene=m_controller->get_scene();
        takeCentralWidget();
        setCentralWidget(gamescene->view());
    }



    // delete m_editorscene;


    //connect(scene,&QGraphicsScene::changed,view,&QGraphicsView::updateScene);

}
void MainWindow::toSelectScene(){
    m_selectscene->reset();

    takeCentralWidget();
    setCentralWidget(m_selectscene);

}

void MainWindow::toTitle(){

//出大问题


    takeCentralWidget();
    setCentralWidget(m_title);


}

