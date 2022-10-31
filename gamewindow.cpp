#include "gamebutton.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <gamescene.h>
#include <QPushButton>
#include <QMessageBox>

extern int gameOverFlag;
extern int flagNumb;
int Click = 0;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    timeFailorWin = new QTimer;
    currentTime = new QTimer;
    connect(timeFailorWin, SIGNAL(timeout()), this, SLOT(Update()));
    connect(currentTime, SIGNAL(timeout()), this, SLOT(updateCount()));
    currentTime->start(1);
    t.setHMS(0, 0, 0);
    sc = new GameScene;
    ui->graphicsView_8x8_2->setScene(sc);
    timeFailorWin->start(500);

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::Update()
{
    if(gameOverFlag == 1)
    {
        Click = 0;
        t.setHMS(0, 0, 0);
        ui->lcdNumber_2->display("00:00");
        sc->Update();
        QMessageBox::information(this, "info", "you failed!");
        gameOverFlag--;
        timeFailorWin->stop();
        gameOverFlag--;

    }else if(flagNumb == 8)
    {
        Click = 0;
        QMessageBox::information(this, "info", "you win!");
        flagNumb = 0;
        timeFailorWin->stop();
        flagNumb = 0;
    }
}

void GameWindow::updateCount()
{
    if(Click > 0)
    {
        currentTime->start(1);
        t = t.addMSecs(1.5);
        QString stime = t.toString("mm:ss");
        ui->lcdNumber_2->display(stime);
    }
}

void GameWindow::on_pushButtonrestart_clicked()
{
    delete sc;
    sc = new GameScene;
    ui->graphicsView_8x8_2->setScene(sc);
    flagNumb = 0;
    timeFailorWin->start(500);
    Click = 0;
    t.setHMS(0, 0, 0);
    ui->lcdNumber_2->display("00:00");
}

void GameWindow::on_pushButtonexit_clicked()
{
    this->close();
    GameWindow::on_pushButtonrestart_clicked();
    emit showMainWindow();
}





