#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gamescenemedium.h"
#include "gamescene.h"

#include <vector>
#include <QMainWindow>


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
signals:
    void showMainWindow();
public slots:
    void Update();
    void updateCount();
private slots:
    void on_pushButtonrestart_clicked();
    void on_pushButtonexit_clicked();
private:
    Ui::GameWindow *ui;
    GameScene *sc;
    QTimer *timeFailorWin;
    QTime t;
    QTimer *currentTime;
};

#endif // GAMEWINDOW_H
