#include "editortab.h"
#include "ui_editortab.h"

EditorTab::EditorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorTab)
{
    ui->setupUi(this);
}

EditorTab::~EditorTab()
{
    delete ui;
}

void EditorTab::on_normalLandButton_clicked()
{
    emit addNormalLand(ui->widthInput->value(),ui->heightInput->value());
}


void EditorTab::on_moveToRight_clicked()
{
    emit moveScene(300,0);
}


void EditorTab::on_saveButton_clicked()
{
    emit saveMap(ui->mapName->text());
}





void EditorTab::on_spikeLandButton_clicked()
{
     emit addSpikeLand(ui->widthInput->value(),ui->heightInput->value(),ui->attackInput->value());
}

void EditorTab::on_worm1Button_clicked()
{
    emit addWorm1();
}


void EditorTab::on_moveToLeft_clicked()
{
     emit moveScene(-300,0);
}

void EditorTab::on_checkPointButton_clicked()
{
    emit addCheckPoint();
}

void EditorTab::on_worm2Button_clicked()
{
    emit addWorm2();
}

void EditorTab::on_worm1GeneratorButton_clicked()
{
    emit addGenerator(0,ui->tInput->value());
}

void EditorTab::on_worm2GeneratorButton_clicked()
{
    emit addGenerator(1,ui->tInput->value());
}

void EditorTab::on_movingLandButton_clicked()
{
    emit addMovingLand(ui->widthInput->value(),ui->heightInput->value(),ui->tInput->value());
}

void EditorTab::on_mushroomButton_clicked()
{
    emit addMushroom();
}

void EditorTab::on_springLandButton_clicked()
{
    emit addSpringLand();
}

void EditorTab::on_fragileButton_clicked()
{
    emit addFragileLand(ui->widthInput->value(),ui->heightInput->value());
}

void EditorTab::on_worm3Button_clicked()
{
    emit addWorm3();
}

void EditorTab::on_flowerButton_clicked()
{
    emit addFlower();
}

void EditorTab::on_finalPointButton_clicked()
{
    emit addDestination();
}

void EditorTab::on_hintLandButton_clicked()
{
    emit addHintLand(ui->hintEdit->toPlainText());
}
