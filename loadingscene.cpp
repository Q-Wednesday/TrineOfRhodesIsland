#include "loadingscene.h"
#include "ui_loadingscene.h"

LoadingScene::LoadingScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingScene),
    m_tick(0),
    m_enabled(false)
{
    ui->setupUi(this);
}

LoadingScene::~LoadingScene()
{
    delete ui;
}

void LoadingScene::reset_tick(){
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
}
