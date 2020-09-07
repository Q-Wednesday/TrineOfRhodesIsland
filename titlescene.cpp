#include "titlescene.h"
#include "ui_titlescene.h"

TitleScene::TitleScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleScene)
{
    ui->setupUi(this);
    setWindowTitle("TrineOfRhodesIsland");
}

TitleScene::~TitleScene()
{
    delete ui;
}

void TitleScene::on_designButton_clicked()
{
    emit toDesign();
}

void TitleScene::on_playMyButton_clicked()
{
    emit toSelect();
}
