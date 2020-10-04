#include "undobutton.h"

UndoButton::UndoButton(QWidget *parent) : QWidget(parent),
  label("Undo"), pixmap (":/icons/back.png")
{

}

void UndoButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QRect (0, this->height()/2 - this->height()/4, this->width()/2, this->height()/2), pixmap);
    painter.drawText( QRect (this->width()/2, this->height()/2 - this->height()/4, this->width()/2, this->height()/2),
                      Qt::AlignCenter, label);
}

void UndoButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button () == Qt::MouseButton::LeftButton
            && event->pos().rx() >= 0 && event->pos().rx() < width()
            && event->pos().ry() >= this->height()/2 - this->height()/4 && event->pos().ry() < this->height()/2 + this->height()/4) {
        emit undo(m_data);
    }
}
