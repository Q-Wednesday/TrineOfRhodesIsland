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
