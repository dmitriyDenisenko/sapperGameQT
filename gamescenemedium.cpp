#include "gamescenemedium.h"

#include <item.h>

extern int a[8][8];
extern int gameOverFlag;
item *allItems[64];
int GameSceneMedium:: index = 0;

GameSceneMedium::GameSceneMedium(QObject *parent) :
    QGraphicsScene(parent)
{
    initImage();
    ptimer = new QTimer;
    connect(ptimer, SIGNAL(timeout()), this, SLOT(Update));
    ptimer->start(1);
}

void GameSceneMedium::initImage()
{
    for(int i=0; i<64; i++)
    {
        allItems[i] = new item(":/source_pic/f3");//загрузка из соурсов изображения
        allItems[i]->setPos(allItems[i]->boundingRect().width()*(i%8), allItems[i]->boundingRect().height()*(i/8));//8x8 растановка объектов
        this->addItem(allItems[i]);//Добавление обьектов в сцену
        a[i/8][i%8] = 0;//Значению, стоящему за каждым элементом, присваивается значение 0

    }
    for(int j=0; j<8; j++)//Случайным образом возьмите восемь молний и присвоите им значение 1
    {
        index = qrand()%64;//Возьмите восемь случайных чисел в пределах 64
        if(allItems[index]->flag == 1)//Если это повторится, примите его снова
            j--;
        allItems[index]->flag = 1;//Флаг переменной элемента элемента установлен в 1
        a[index/8][index%8] = 1;//Значение, стоящее за квадратом 8x8, присваивается 1
    }
}

void GameSceneMedium::Update()//Вызов для отображения всех мин в конце игры
{
    if(gameOverFlag == 1)
    {
        for(index=0; index<64; index++)
        {
            if(a[index/8][index%8] == 1)
            {
                allItems[index] = new item(":/source_pic/l1");//地雷
                allItems[index]->setPos(allItems[index]->boundingRect().width()*(index%8), allItems[index]->boundingRect().height()*(index/8));
                this->addItem(allItems[index]);
            }
        }
        ptimer->stop();
    }
}
