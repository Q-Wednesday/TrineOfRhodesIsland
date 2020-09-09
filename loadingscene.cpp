#include "loadingscene.h"
#include "ui_loadingscene.h"
#include"QPainter"
#include<QDebug>
LoadingScene::LoadingScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingScene),
    m_tick(0),
    m_enabled(false)

{
    ui->setupUi(this);
    m_bg1=new QPixmap(":/images/loading1");
    m_bg2=new QPixmap(":/images/loading2");



    ui->imageLabel->setGeometry(0,0,1920,1080);
    ui->imageLabel->setPixmap(*m_bg1);
}

LoadingScene::~LoadingScene()
{
    delete m_bg1;
    delete m_bg2;

    delete ui;
}

void LoadingScene::reset_tick(){
    ui->imageLabel->setPixmap(*m_bg1);
    ui->progressBar->reset();
    m_enabled=true;
    m_tick=0;
}

void LoadingScene::advance(){
    if(!m_enabled)
        return;
    m_tick++;
    if(m_tick>=165){
        m_enabled=false;
        emit loadingFinish();
    }
    ui->progressBar->setValue(m_tick*100/165);
    if(m_tick>=100){
        ui->imageLabel->setPixmap(*m_bg2);
    }
}
