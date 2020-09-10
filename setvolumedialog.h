#ifndef SETVOLUMEDIALOG_H
#define SETVOLUMEDIALOG_H

#include <QDialog>
#include<QSlider>
namespace Ui {
class SetVolumeDialog;
}

class SetVolumeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetVolumeDialog(QWidget *parent = nullptr);
    ~SetVolumeDialog();
    QSlider* get_slider();
private:
    Ui::SetVolumeDialog *ui;
};

#endif // SETVOLUMEDIALOG_H
