#include "gamescene.h"

#include <item.h>

extern int gameOverFlag;
int GameScene:: index = 0;

GameScene::GameScene(QObject *parent, int row, int column, int bomb) :
    QGraphicsScene(parent)
{
    this->row = row;
    this->column = column;
    this->bomb = bomb;
    allItems = new item[row * column];
    initMatrix();
    initImage();
    ptimer = new QTimer;
    connect(ptimer, SIGNAL(timeout()), this, SLOT(Update));
    ptimer->start(1);

}

void GameScene::initMatrix(){
    a = new int*[row];
    for(int i = 0; i < row;i++){
        a[i] = new int[column];
    }
}


void GameScene::initImage()
{
    for(int i=0; i<64; i++)
    {
        allItems[i].setPos(allItems[i].boundingRect().width()*(i%8), allItems[i].boundingRect().height()*(i/8));//8x8 растановка объектов
        this->addItem(&allItems[i]);
        a[i/8][i%8] = 0;
        connect(&allItems[i], &item::setNum, this, &GameScene::setNum);
    }
    for(int j=0; j<8; j++)
    {
        index = qrand()%64;
        if(allItems[index].flag == 1)
            j--;
        allItems[index].flag = 1;
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
                allItems[index].setPixmap(QPixmap(":/source_pic/bomb"));
                allItems[index].setPos(allItems[index].boundingRect().width()*(index%8), allItems[index].boundingRect().height()*(index/8));
            }
        }
        ptimer->stop();
    }
}
//--------------------------------------------------
void GameScene::setNum(int y, int x)
{
    int boomNum = calculateBombs(x,y);

    switch(boomNum)
    {
        case 1: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/1"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 2: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/2"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 3: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/3"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 4: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/4"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 5: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/5"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 6: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/6"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 7: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/7"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 8: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/8"));
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
        case 0: allItems[8*y+x].setPixmap(QPixmap(":/source_pic/white cube")); // f2
            findWhiteCubes(x,y);
            allItems[8*y+x].setIsFlagOrWhiteBlock(allItems[8*y+x].getIsFlagOrWhiteBlock() + 2);
            break;
   }
}

int GameScene::calculateBombs(int x, int y){
    int boomNum = 0;
    if((y - 1 >= 0) && (x - 1 >= 0) && (a[y - 1][x - 1] == 1)) //[0][0]
        boomNum++;
    if((y - 1 >= 0) && a[y - 1][x] == 1) //[0][1]
        boomNum++;
    if((y - 1 >= 0) && (x + 1 <= 7) && (a[y - 1][x + 1] == 1)) //[0][2]
        boomNum++;
    if((x - 1 >= 0) && (a[y][x - 1] == 1)) //[1][0]
        boomNum++;
    if((x + 1 <= 7) && (a[y][x + 1] == 1)) //[1][2]
        boomNum++;
    if((x - 1 >= 0) && (y + 1 <= 7) && (a[y+1][x-1] == 1)) //[2][0]
        boomNum++;
    if((y + 1 <= 7) && (a[y + 1][x] == 1)) //[2][1]
        boomNum++;
    if((y + 1 <= 7) && (x + 1 <= 7) && (a[y+1][x+1] == 1)) //[2][2]
        boomNum++;
    return boomNum;
}

void GameScene::findWhiteCubes(int x, int y){ //recursion on displaying all white cubes
    if(y < 7 && y > 0 && x < 7 && x > 0 && allItems[8*y+x].getSpreadFlag()== 0) //the matrix [1][1] to [6][6]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y-1, x);
        setNum(y, x-1);
        setNum(y+1, x);
        setNum(y, x+1);
    }
    if(y == 0 && (x != 0) && (x != 7) && allItems[8*y+x].getSpreadFlag() == 0) // matrix [0][1] to [0][6]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y, x-1);
        setNum(y+1, x);
        setNum(y, x+1);
    }
    if((x == 0) && (y != 0) && (y != 7) && allItems[8*y+x].getSpreadFlag() == 0) // matrix [1][0] to [1][6]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y-1, x);
        setNum(y+1, x);
        setNum(y, x+1);
    }
    if((y == 7) && (x != 0) && (x != 7) && allItems[8*y+x].getSpreadFlag() == 0) //matrix [7][1] to [7][6]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y-1, x);
        setNum(y, x-1);
        setNum(y, x+1);
    }
    if((x == 7) && (y != 0) && (y != 7) && allItems[8*y+x].getSpreadFlag() == 0) //matrix [1][7] to [2][7]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y-1, x);
        setNum(y, x-1);
        setNum(y+1, x);
    }
    if((x == 0) && (y == 0) && allItems[8*y+x].getSpreadFlag() == 0) //[0][0]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y, x+1);
        setNum(y+1, x);
    }
    if((x == 7) && (y == 7) && allItems[8*y+x].getSpreadFlag() == 0) //[7][7]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y-1, x);
        setNum(y, x-1);
     }
    if((y == 7) && (x == 0) && allItems[8*y+x].getSpreadFlag() == 0) //[7][0]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y-1, x);
        setNum(y, x+1);
    }
    if((x == 7)&&(y == 0) && allItems[8*y+x].getSpreadFlag() == 0) //[7][0]
    {
        allItems[8*y+x].setSpreadFlag(1);
        setNum(y+1, x);
        setNum(y, x-1);
    }
}
