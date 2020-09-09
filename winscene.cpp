#include "winscene.h"
#include "ui_winscene.h"

WinScene::WinScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinScene)
{
    ui->setupUi(this);
    connect(ui->titleButton,SIGNAL(clicked()),this,SIGNAL(toTitle()));
}

WinScene::~WinScene()
{
    delete ui;
}

void WinScene::on_titleButton_clicked()
{

}

void WinScene::setResult(int score, int secs){
    ui->scoreLabel->setText(QString("得分:%1").arg(score));
    ui->timeLabel->setText(QString("用时%1分%2秒").arg(secs/60).arg(secs%60));
}
