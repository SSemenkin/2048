#include "newgamebutton.h"

NewGameButton::NewGameButton(QWidget *parent) : QWidget(parent)
{
    auto m_font = this->font();
    m_font.setPointSize(m_font.pointSize() * 2);
    this->setFont(m_font);
}

void NewGameButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing);

    painter.setBrush (QColor("#EEE4DA"));
    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width ()-1,this->height ()/2), this->width ()/20, this->height ()/20);

    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), this->width ()/20, this->height ()/20);

    painter.setPen (QColor("#776E62"));


    painter.drawText (QRect( 0, this->height ()/2 - this->height ()/4, this->width (),this->height ()/2), Qt::AlignCenter, "New Game");
}

void NewGameButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button () == Qt::MouseButton::LeftButton
            && event->pos().rx() >= 0 && event->pos().rx() < width() && event->pos().ry() >= 0 && event->pos().ry() < this->height()) {
        if(QMessageBox :: question ( this, "", "Start new game?") == QMessageBox::StandardButton::Yes) {
            emit initiateNewGame ();
        }
    }
}

void NewGameButton::enterEvent(QEvent *)
{
    isHover = true;
}

void NewGameButton::leaveEvent(QEvent *)
{
    isHover = false;
}
