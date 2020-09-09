#include "losescene.h"
#include "ui_losescene.h"

LoseScene::LoseScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoseScene)
{
    ui->setupUi(this);
}

LoseScene::~LoseScene()
{
    delete ui;
}

void LoseScene::on_pushButton_clicked()
{
    emit toTitle();
}

void LoseScene::setTime(int secs){
    ui->timeLabel->setText(QString("生存时间:%1").arg(secs));
}
