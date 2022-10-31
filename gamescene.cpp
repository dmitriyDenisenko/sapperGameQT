#include "gamescene.h"

#include <item.h>

extern int a[8][8];
extern int gameOverFlag;
item *allItems[64];
int GameScene:: index = 0;

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
    initImage();
    ptimer = new QTimer;
    connect(ptimer, SIGNAL(timeout()), this, SLOT(Update));
    ptimer->start(1);
}

void GameScene::initImage()
{
    for(int i=0; i<64; i++)
    {
        allItems[i] = new item(":/source_pic/pink cube");//загрузка из соурсов изображения
        allItems[i]->setPos(allItems[i]->boundingRect().width()*(i%8), allItems[i]->boundingRect().height()*(i/8));//8x8 растановка объектов
        this->addItem(allItems[i]);
        a[i/8][i%8] = 0;

    }
    for(int j=0; j<8; j++)
    {
        index = qrand()%64;
        if(allItems[index]->flag == 1)
            j--;
        allItems[index]->flag = 1;
        a[index/8][index%8] = 1;
    }
}

void GameScene::Update()
{
    if(gameOverFlag == 1)
    {
        for(index=0; index<64; index++)
        {
            if(a[index/8][index%8] == 1)
            {
                allItems[index] = new item(":/source_pic/bomb");
                allItems[index]->setPos(allItems[index]->boundingRect().width()*(index%8), allItems[index]->boundingRect().height()*(index/8));
                this->addItem(allItems[index]);
            }
        }
        ptimer->stop();
    }
}
