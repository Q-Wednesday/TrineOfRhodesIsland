#include "titlescene.h"
#include "ui_titlescene.h"

TitleScene::TitleScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleScene),
    m_volumedialog(new SetVolumeDialog(this))
{
    ui->setupUi(this);
    setWindowTitle("TrineOfRhodesIsland");
    m_volumedialog->setVisible(false);
    m_volumedialog->setWindowTitle("音量");
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

void TitleScene::on_quitButton_clicked()
{
    QApplication::exit();
}

void TitleScene::on_adventureButton_clicked()
{
    emit toAdventure();
}

SetVolumeDialog* TitleScene::get_dialog(){
    return m_volumedialog;
}
void TitleScene::on_voiceButton_clicked()
{
    m_volumedialog->show();
}
