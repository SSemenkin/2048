#include "newgamebutton.h"

NewGameButton::NewGameButton(QWidget *parent) : QWidget(parent)
{

}

void NewGameButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::HighQualityAntialiasing);
    painter.setBrush (QColor(198, 127, 47));
    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), this->width ()/20, this->height ()/20);
    painter.setFont (QFont("Comic Sans Pro", 14));

    if (isHover) {
        painter.setBrush (QColor( 198, 169, 47));
        painter.setPen (Qt::blue);
        painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), this->width ()/20, this->height ()/20);
    }
    painter.drawText (QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), Qt::AlignCenter, "Новая игра");
}

void NewGameButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button () == Qt::MouseButton::LeftButton) {
        if(QMessageBox :: question ( this, "", "Вы уверенны что хотите начать новую игру?") == QMessageBox::StandardButton::Yes) {
            emit initiateNewGame ();
        }
    }
}

void NewGameButton::enterEvent(QEvent *event)
{
    isHover = true;
    update();
    QWidget::enterEvent (event);
}

void NewGameButton::leaveEvent(QEvent *event)
{
    isHover = false;
    update ();
    QWidget::leaveEvent (event);
}
