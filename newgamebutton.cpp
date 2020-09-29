#include "newgamebutton.h"

NewGameButton::NewGameButton(QWidget *parent) : QWidget(parent)
{

}

void NewGameButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setBrush (QColor("#EEE4DA"));
    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width ()-1,this->height ()/2), this->width ()/20, this->height ()/20);

    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), this->width ()/20, this->height ()/20);

    isHover ? painter.setPen (QColor("#776E62")) : painter.setPen (QColor("#F9F6F2"));

    painter.drawText (QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), Qt::AlignCenter, "New Game");
}

void NewGameButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button () == Qt::MouseButton::LeftButton) {
        if(QMessageBox :: question ( this, "", "Start new game?") == QMessageBox::StandardButton::Yes) {
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
