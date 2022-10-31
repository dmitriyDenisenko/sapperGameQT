#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QString>



class GameButton : public QPushButton
{
public:
    explicit GameButton(const QString &text);
    ~GameButton();
    void setId(int id);
private:
    int id = 0;
};

#endif // GAMEBUTTON_H

