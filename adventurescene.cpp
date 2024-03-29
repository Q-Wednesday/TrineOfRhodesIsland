#include "adventurescene.h"
#include "ui_adventurescene.h"

AdventureScene::AdventureScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdventureScene)
{
    ui->setupUi(this);
}

AdventureScene::~AdventureScene()
{
    delete ui;
}

void AdventureScene::on_level1Button_clicked()
{
    emit toLevel(":/maps/level1");
}

void AdventureScene::on_level2Button_clicked()
{
    emit toLevel(":/maps/level2");
}

void AdventureScene::on_titleButton_clicked()
{
    emit toTitle();
}
