#include "item.h"
#include <unistd.h>
#include <QGraphicsSceneMouseEvent>
#include <qmessagebox.h>
#include <qmessagebox.h>
#include <QMessageLogger>
#include <QMessageLogger>
#include <qlogging.h>

int gameOverFlag = 0;
int a[8][8];
int flagNumb;
extern int Click;
extern item *allItems[64];

item::item(QString path)
{
    this->setPixmap(QPixmap(path));
    isFlagOrWhiteBlock = 0;
    spreadFlag = 0;
    flag = 0;
}

void item::setNum(int y, int x)
{
    calculateBombs(x,y);

    switch(boomNum)
    {
        case 1: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/1"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 2: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/2"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 3: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/3"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 4: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/4"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 5: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/5"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 6: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/6"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 7: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/7"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 8: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/8"));
            allItems[8*y+x]->isFlagOrWhiteBlock += 2;
            break;
        case 0: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/white cube")); // f2
            findWhiteCubes(x,y);
            break;
   }
}

void item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && flag == 0 && isFlagOrWhiteBlock == 0)
    {
        m_x = this->pos().x();
        m_y = this->pos().y();
        setNum(m_y/50, m_x/50);

    }else if(event->button() == Qt::LeftButton && flag == 1 && isFlagOrWhiteBlock == 0)
    {
        this->setPixmap(QPixmap(":/source_pic/bomb"));
        gameOverFlag = 1;

    }else if(event->button() == Qt::RightButton && flag == 1)
    {
        if(isFlagOrWhiteBlock == 0)
        {
            this->setPixmap(QPixmap(":/source_pic/flag"));
            isFlagOrWhiteBlock++;
            flagNumb++;

        }else if(isFlagOrWhiteBlock == 1)
        {
            this->setPixmap(QPixmap(":/source_pic/pink cube"));
            isFlagOrWhiteBlock--;
            flagNumb--;
        }

    }else if(event->button() == Qt::RightButton && flag == 0)
    {
        if(isFlagOrWhiteBlock == 0)
        {
            this->setPixmap(QPixmap(":/source_pic/flag"));
            isFlagOrWhiteBlock++;
            flagNumb--;
        }else if(isFlagOrWhiteBlock == 1)
        {
           this->setPixmap(QPixmap(":/source_pic/pink cube"));
           isFlagOrWhiteBlock--;
           flagNumb++;
        }
    }
    Click++;
}

void item::calculateBombs(int x, int y){
    boomNum = 0;
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
}

/*To understand the applicants,
 * the bottom line is that you need to consider all
 * cases of finding a cube in a grid. Each item considers
 * the area of a square in space.
 * It is better to draw a simpler matrix and draw
 */

void item::findWhiteCubes(int x, int y){ //recursion on displaying all white cubes
    if(y < 7 && y > 0 && x < 7 && x > 0 && allItems[8*y+x]->spreadFlag == 0) //the matrix [1][1] to [6][6]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y-1, x);
        setNum(y, x-1);
        setNum(y+1, x);
        setNum(y, x+1);
    }
    if(y == 0 && (x != 0) && (x != 7) && allItems[8*y+x]->spreadFlag == 0) // matrix [0][1] to [0][6]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y, x-1);
        setNum(y+1, x);
        setNum(y, x+1);
    }
    if((x == 0) && (y != 0) && (y != 7) && allItems[8*y+x]->spreadFlag == 0) // matrix [1][0] to [1][6]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y-1, x);
        setNum(y+1, x);
        setNum(y, x+1);
    }
    if((y == 7) && (x != 0) && (x != 7) && allItems[8*y+x]->spreadFlag == 0) //matrix [7][1] to [7][6]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y-1, x);
        setNum(y, x-1);
        setNum(y, x+1);
    }
    if((x == 7) && (y != 0) && (y != 7) && allItems[8*y+x]->spreadFlag == 0) //matrix [1][7] to [2][7]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y-1, x);
        setNum(y, x-1);
        setNum(y+1, x);
    }
    if((x == 0) && (y == 0) && allItems[8*y+x]->spreadFlag == 0) //[0][0]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y, x+1);
        setNum(y+1, x);
    }
    if((x == 7) && (y == 7) && allItems[8*y+x]->spreadFlag == 0) //[7][7]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y-1, x);
        setNum(y, x-1);
     }
    if((y == 7) && (x == 0) && allItems[8*y+x]->spreadFlag == 0) //[7][0]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y-1, x);
        setNum(y, x+1);
    }
    if((x == 7)&&(y == 0) && allItems[8*y+x]->spreadFlag == 0) //[7][0]
    {
        allItems[8*y+x]->spreadFlag = 1;
        setNum(y+1, x);
        setNum(y, x-1);
    }
    allItems[8*y+x]->isFlagOrWhiteBlock += 2;
}
