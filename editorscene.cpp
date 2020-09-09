#include "editorscene.h"
#include "ui_editorscene.h"

#include<QDebug>
EditorScene::EditorScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorScene),
    m_gamescene(new GameScene),
    m_editortab(new EditorTab(this))
{
    ui->setupUi(this);

    setCentralWidget(m_gamescene->view());
    m_dock=new QDockWidget("部件栏");
    m_dock->setWidget(m_editortab);
    m_dock->setAllowedAreas(Qt::RightDockWidgetArea);
    m_dock->setGeometry(0,0,280,1000);
    addDockWidget(Qt::RightDockWidgetArea,m_dock);

    //action连接
    connect(ui->showTab,SIGNAL(triggered()),this,SLOT(showTab()));
    connect(ui->startPlay,SIGNAL(triggered()),this,SLOT(toPlay()));
    connect(ui->toTitle,SIGNAL(triggered()),this,SIGNAL(toTitle()));
    //
    connect(m_editortab,&EditorTab::addNormalLand,m_gamescene,&GameScene::addNormalLand);    
    connect(m_editortab,&EditorTab::moveScene,m_gamescene,&GameScene::changeSceneRect);
    connect(m_editortab,&EditorTab::saveMap,m_gamescene,&GameScene::saveScene);
    connect(m_editortab,&EditorTab::addWorm1,m_gamescene,&GameScene::addWorm1);
    connect(m_editortab,&EditorTab::addSpikeLand,m_gamescene,&GameScene::addSpikeLand);
    connect(m_editortab,&EditorTab::addCheckPoint,m_gamescene,&GameScene::addCheckPoint);
    connect(m_editortab,&EditorTab::addWorm2,m_gamescene,&GameScene::addWorm2);
    connect(m_editortab,&EditorTab::addWorm3,m_gamescene,&GameScene::addWorm3);
    connect(m_editortab,&EditorTab::addGenerator,m_gamescene,&GameScene::addGenerator);
    connect(m_editortab,&EditorTab::addMovingLand,m_gamescene,&GameScene::addMovingLand);
    connect(m_editortab,&EditorTab::addMushroom,m_gamescene,&GameScene::addMushroom);
    connect(m_editortab,&EditorTab::addSpringLand,m_gamescene,&GameScene::addSpringLand);
    connect(m_editortab,&EditorTab::addFragileLand,m_gamescene,&GameScene::addFragileLand);
    connect(m_editortab,&EditorTab::addFlower,m_gamescene,&GameScene::addFlower);
    connect(m_editortab,&EditorTab::addDestination,m_gamescene,&GameScene::addDestination);
    connect(m_editortab,&EditorTab::addHintLand,m_gamescene,&GameScene::addHintLand);
}
void EditorScene::loadMap(QString filename){
    m_gamescene->loadMap(filename);
    //m_gamescene->reset(filename);
}
void EditorScene::reset(){
     m_gamescene->reset();

}
EditorScene::~EditorScene()
{
    qDebug()<<"delete editor";
    delete ui;
}

void EditorScene::showTab(){
    qDebug()<<"show";
    m_dock->show();
}


GameScene* EditorScene::get_scene(){
    return  m_gamescene;
}

void EditorScene::toPlay(){
    m_gamescene->saveScene("temp");
    emit startPlay("maps/temp.json");
}
