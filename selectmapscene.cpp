#include "selectmapscene.h"
#include "ui_selectmapscene.h"
#include<QDir>
#include<QVBoxLayout>
#include<QPushButton>
#include<QSignalMapper>
#include"gamecontroller.h"
SelectMapScene::SelectMapScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMapScene)
{
    ui->setupUi(this);
    QDir dir;
    if(!dir.exists(dir.currentPath()+"/maps")){
        dir.mkpath(dir.currentPath()+"/maps");
    }
    dir.cd("maps");
    QFileInfoList filelist=dir.entryInfoList();
    QVBoxLayout *layout=new QVBoxLayout;
    QSignalMapper*m=new QSignalMapper(this);
    for(auto file:filelist){
        QString filename=file.fileName();
        if(filename.right(4)!="json")
            continue;
        QPushButton* button=new QPushButton(filename);
        connect(button,SIGNAL(clicked()),m,SLOT(map()));
        m->setMapping(button,"maps/"+filename);
        layout->addWidget(button);
    }
    ui->scrollArea->setLayout(layout);
    connect(m,SIGNAL(mapped(QString)),this,SIGNAL(openMap(QString)));
}

SelectMapScene::~SelectMapScene()
{
    delete ui;
}

