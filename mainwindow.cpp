#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
int level = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window = new GameWindow(this);
    connect(window, &GameWindow::showMainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    if(level == 0){
        window->show();
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    if(level == 0){
        ui->easy->setStyleSheet("text-decoration: none");
        ui->medium->setStyleSheet("text-decoration: underline");
    } else if(level == 1){
        ui->medium->setStyleSheet("text-decoration: none");
        ui->hard->setStyleSheet("text-decoration: underline");
    } else{
        ui->hard->setStyleSheet("text-decoration: none");
        ui->easy->setStyleSheet("text-decoration: underline");
    }
    level++;
    level = level % 3;
}


void MainWindow::on_pushButton_clicked()
{
    if(level == 0){
        ui->easy->setStyleSheet("text-decoration: none");
        ui->hard->setStyleSheet("text-decoration: underline");
        level = 2;
    } else if(level == 1){
        ui->medium->setStyleSheet("text-decoration: none");
        ui->easy->setStyleSheet("text-decoration: underline");
        level = 0;
    } else {
        ui->hard->setStyleSheet("text-decoration: none");
        ui->medium->setStyleSheet("text-decoration: underline");
        level = 1;
    }
}

