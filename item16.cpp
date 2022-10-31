#include "item16.h"
#include <unistd.h>
#include <QGraphicsSceneMouseEvent>

int gameOverFlag = 0;
int a[16][16];
int flagNumb; //Найдите количество леев (вставьте флажок)
extern int Click;
extern item *allItems[256];

item16::item16QString path)
{
    this->setPixmap(QPixmap(path));
    isFlagOrWhiteBlock = 0;//0 указывает на состояние, которое еще не был нажат щелчок
    spreadFlag = 0;
    flag = 0;
}

void item::setNum(int y, int x)
{
    boomNum = 0;
    if((y-1 >= 0) && (x-1 >= 0) && (a[y-1][x-1] == 1))//Вокруг есть восемь квадратов, один за другим, чтобы определить, сколько мин находится в общей сложности.
        boomNum++;
    if((y-1 >= 0) && a[y-1][x] == 1)
        boomNum++;
    if((y-1 >= 0) && (x+1 <= 7) && (a[y-1][x+1] == 1))
        boomNum++;
    if((x-1 >= 0) && (a[y][x-1] == 1))
        boomNum++;
    if((x+1 <= 7) && (a[y][x+1] == 1))
        boomNum++;
    if((x-1 >= 0) && (y+1 <= 7) && (a[y+1][x-1] == 1))
        boomNum++;
    if((y+1 <= 7) && (a[y+1][x] == 1))
        boomNum++;
    if((y+1 <= 7) && (x+1 <= 7) && (a[y+1][x+1] == 1))
        boomNum++;
    switch(boomNum)//Отображение номеров в текущем блоке на основе количества окружающих шахт
    {
        case 1: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/11")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 2: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/22")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 3: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/33")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 4: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/44")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 5: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/55")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 6: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/66")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 7: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/77")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 8: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/88")); allItems[8*y+x]->isFlagOrWhiteBlock += 2; break;
        case 0: allItems[8*y+x]->setPixmap(QPixmap(":/source_pic/f2"));//Это означает, что вокруг нет грома, и блоки в разных местах внизу распределяются по-разному.
        if(y < 7 && y > 0 && x < 7 && x > 0 && allItems[8*y+x]->spreadFlag == 0)//Квадрат, который принадлежит к середине
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if(y == 0 && (x != 0) && (x != 7) && allItems[8*y+x]->spreadFlag == 0)//Квадрат сверху не содержит обеих сторон
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y, x-1);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if((x == 0) && (y != 0) && (y != 7) && allItems[8*y+x]->spreadFlag == 0)//Квадрат слева не содержит обеих сторон
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if((y == 7) && (x != 0) && (x != 7) && allItems[8*y+x]->spreadFlag == 0)//Квадрат слева не содержит обеих сторон. Квадрат ниже не содержит обеих сторон.
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y, x+1);
        }
        if((x == 7) && (y != 0) && (y != 7) && allItems[8*y+x]->spreadFlag == 0)//Квадрат справа не содержит обеих сторон
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y+1, x);
        }
        if((x == 0) && (y == 0) && allItems[8*y+x]->spreadFlag == 0)//левый верхний угол
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y, x+1);
            setNum(y+1, x);
        }
        if((x == 7) && (y == 7) && allItems[8*y+x]->spreadFlag == 0)//Нижний правый угол
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
         }
        if((y == 7) && (x == 0) && allItems[8*y+x]->spreadFlag == 0)//Нижний левый угол
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x+1);
        }
        if((x == 7)&&(y == 0) && allItems[8*y+x]->spreadFlag == 0)//Верхний правый угол
        {
            allItems[8*y+x]->spreadFlag = 1;
            setNum(y+1, x);
            setNum(y, x-1);
        }
        allItems[8*y+x]->isFlagOrWhiteBlock += 2;

       break;
   }
}

void item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && flag == 0 && isFlagOrWhiteBlock == 0)//Поле не нажато, щелкните левой кнопкой мыши, и оно не отображается.
    {
        m_x = this->pos().x();
        m_y = this->pos().y();//Получить координаты этого блока
        setNum(m_y/48, m_x/48);//Используйте [0,0]- >[7,7], чтобы определить количество окружающих раскатов грома и отобразить его, или если грома вообще нет

    }else if(event->button() == Qt::LeftButton && flag == 1 && isFlagOrWhiteBlock == 0)//Поле не нажато, щелчок левой кнопкой мыши - это гром
    {
        this->setPixmap(QPixmap(":/source_pic/l1"));//Установите значок грома
        gameOverFlag = 1;//Игра окончена

    }else if(event->button() == Qt::RightButton && flag == 1)//Щелкните правой кнопкой мыши на квадрате, который является громом
    {
        if(isFlagOrWhiteBlock == 0)//Квадрат еще не был нажат
        {
            this->setPixmap(QPixmap(":/source_pic/q1"));//Вставить флаг
            isFlagOrWhiteBlock++;//Указывает, что этот блок был вставлен во флаг
            flagNumb++;//Добавьте единицу к количеству найденных леев

        }else if(isFlagOrWhiteBlock == 1)//Если этот фрагмент был вставлен во флаг,
        {
            this->setPixmap(QPixmap(":/source_pic/f3"));//Если этот фрагмент был вставлен во флаг,
            isFlagOrWhiteBlock--;//Прежде чем состояние вернется к точке
            flagNumb--;//Количество найденных ударов грома минус один
        }

    }else if(event->button() == Qt::RightButton && flag == 0)//Щелкните правой кнопкой мыши на поле, которое не отображается.
    {
        if(isFlagOrWhiteBlock == 0)//Если вы не нажали, будет вставлен флаг, указывающий на то, что этот блок был вставлен.
        {
            this->setPixmap(QPixmap(":/source_pic/q1"));
            isFlagOrWhiteBlock++;
            flagNumb--;//Вставьте неправильный флаг-1
        }else if(isFlagOrWhiteBlock == 1)//Если флаг был вставлен, отмените вставку флага
        {
           this->setPixmap(QPixmap(":/source_pic/f3"));
           isFlagOrWhiteBlock--;
           flagNumb++;//Отмена неправильного флага +1
        }
    }
    /*
    else if(event->button() == Qt::MidButton && flag == 1 && IsflagOrwhiteblock == 0)
    {
        this->setPixmap(QPixmap(":/source_pic/q1"));
        flagNum++;
    }
    */
    Click++;//点击的次数加一
}
