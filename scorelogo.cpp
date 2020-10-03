#include "scorelogo.h"

ScoreLogo::ScoreLogo(QString title,QWidget *parent) : QWidget(parent), m_title (title), m_value(0)
{

}

void ScoreLogo::setValue(int value)
{
    DigitalAnimation *animation;
    if (value == 0 && m_value > 0) {
        animation = new DigitalAnimation((0 - m_value),this);
    } else {
        animation = new DigitalAnimation(abs(m_value - value),this);
    }

    animation->setGeometry (this->rect ().adjusted (0, -this->rect ().height (), 0, -this->rect ().height ()));

    animation->show();
    m_value = value;
    update ();
    animation->start();
}

void ScoreLogo::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setBrush(QColor("#BBADA0"));
    painter.setPen(QColor("#EEE4DA"));
    painter.setRenderHint (QPainter::Antialiasing);
    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (), this->height ()/2), this->width ()/10, this->height ()/10);
    painter.drawText ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (), this->height ()/2), Qt::AlignCenter, m_title.arg ( m_value));
}
