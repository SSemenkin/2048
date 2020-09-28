#include "scorelogo.h"

ScoreLogo::ScoreLogo(QString title,QWidget *parent) : QWidget(parent), m_title (title), m_value(0)
{

}

void ScoreLogo::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setFont (QFont("Goudy stout", 10));
    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (), this->height ()/2), this->width ()/10, this->height ()/10);
    painter.drawText ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (), this->height ()/2), Qt::AlignCenter, m_title.arg ( m_value));
}
