#include "setvolumedialog.h"
#include "ui_setvolumedialog.h"

SetVolumeDialog::SetVolumeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetVolumeDialog)
{
    ui->setupUi(this);
}

SetVolumeDialog::~SetVolumeDialog()
{
    delete ui;
}

QSlider* SetVolumeDialog::get_slider(){
    return ui->horizontalSlider;
}
