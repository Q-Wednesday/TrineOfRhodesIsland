#include "selectmapscene.h"
#include "ui_selectmapscene.h"
#include<QDir>



#include"gamecontroller.h"
SelectMapScene::SelectMapScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMapScene),
    m_layout(new QVBoxLayout)

{
    ui->setupUi(this);


    //ui->scrollArea->setLayout(m_layout);
    ui->scrollArea->widget()->setLayout(m_layout);
}

SelectMapScene::~SelectMapScene()
{
    delete ui;
}

void SelectMapScene::reset(){

    for(auto i:m_buttons){
        delete  i;
    }
    for(auto i:m_labels){
        delete i;
    }
    delete m_mapper;
    QDir dir;
    if(!dir.exists(dir.currentPath()+"/maps")){
        dir.mkpath(dir.currentPath()+"/maps");
    }
    dir.cd("maps");
    QFileInfoList filelist=dir.entryInfoList();

    m_mapper=new QSignalMapper(this);

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

        QPushButton* button=new QPushButton(filename);
        m_buttons.push_back(button);
        connect(button,SIGNAL(clicked()),m_mapper,SLOT(map()));
        m_mapper->setMapping(button,"maps/"+filename);
        m_layout->addWidget(button);
    }

    connect(m_mapper,SIGNAL(mapped(QString)),this,SIGNAL(openMap(QString)));
}
