#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include <QWidget>

namespace Ui {
class LoadingScene;
}

class LoadingScene : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingScene(QWidget *parent = nullptr);
    ~LoadingScene();
    void reset_tick();

signals:
    void loadingFinish();
public   slots:
    void advance();

private:
    Ui::LoadingScene *ui;
    int m_tick;
    bool m_enabled;
    QPixmap* m_bg1;
    QPixmap* m_bg2;

};

#endif // LOADINGSCENE_H
