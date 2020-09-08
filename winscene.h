#ifndef WINSCENE_H
#define WINSCENE_H

#include <QWidget>

namespace Ui {
class WinScene;
}

class WinScene : public QWidget
{
    Q_OBJECT

public:
    explicit WinScene(QWidget *parent = nullptr);
    ~WinScene();
signals:
    void toTitle();
private slots:
    void on_titleButton_clicked();

private:
    Ui::WinScene *ui;
};

#endif // WINSCENE_H
