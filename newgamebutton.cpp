#include "newgamebutton.h"

NewGameButton::NewGameButton(QWidget *parent) : QWidget(parent)
{

}

void NewGameButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setFont (QFont("Comic Sans Pro", 14));
    painter.setPen (Qt::blue);
    painter.drawText (this->rect (), Qt::AlignCenter, "NEW GAME");
}
