#include "selectmapscene.h"
#include "ui_selectmapscene.h"
#include<QDir>
#include<QDebug>


#include"gamecontroller.h"
SelectMapScene::SelectMapScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMapScene),
    m_layout(new QVBoxLayout),
    m_mapper(new QSignalMapper(this)),
    m_mapper_edit(new QSignalMapper(this))

{
    ui->setupUi(this);


    //ui->scrollArea->setLayout(m_layout);
    ui->scrollArea->widget()->setLayout(m_layout);
    connect(m_mapper,SIGNAL(mapped(QString)),this,SIGNAL(openMap(QString)));
    connect(m_mapper_edit,SIGNAL(mapped(QString)),this,SIGNAL(editMap(QString)));
}

SelectMapScene::~SelectMapScene()
{
    qDebug()<<"删除select map scene";
    delete ui;
}

void SelectMapScene::reset(){
    qDebug()<<"start reset select scene";

    for(auto i:m_buttons){
        m_mapper->removeMappings(i);
        delete  i;
    }
    m_buttons.clear();
    qDebug()<<0;
    for(auto i:m_editbuttons){
        m_mapper_edit->removeMappings(i);
        delete i;
    }
    m_editbuttons.clear();
    for(auto i:m_labels){
        delete i;
    }

    m_labels.clear();

    QDir dir;
    if(!dir.exists(dir.currentPath()+"/maps")){
        dir.mkpath(dir.currentPath()+"/maps");
    }
    dir.cd("maps");
    QFileInfoList filelist=dir.entryInfoList();


  qDebug()<<"1";
    for(auto file:filelist){
        QString filename=file.fileName();
        if(filename.right(4)!="json")
            continue;
        QLabel* label=new QLabel(this);
        label->setGeometry(0,0,320,180);
        QPixmap bgImage("maps/"+filename.left(filename.size()-4)+"jpg");
        label->setPixmap(bgImage.scaled(label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        m_labels.push_back(label);
        m_layout->addWidget(label);

        QPushButton* button=new QPushButton(filename.left(filename.size()-4));
        button->setCursor(Qt::PointingHandCursor);
        m_buttons.push_back(button);
        connect(button,SIGNAL(clicked()),m_mapper,SLOT(map()));
        m_mapper->setMapping(button,"maps/"+filename);
        m_layout->addWidget(button);

        QPushButton* button_edit=new QPushButton("编辑");
        button_edit->setCursor(Qt::PointingHandCursor);
        m_editbuttons.push_back(button_edit);
        connect(button_edit,SIGNAL(clicked()),m_mapper_edit,SLOT(map()));
        m_mapper_edit->setMapping(button_edit,"maps/"+filename);
        m_layout->addWidget(button_edit);
    }
    qDebug()<<"2";


}
