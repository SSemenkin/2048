#include "scorelogo.h"

ScoreLogo::ScoreLogo(QString title,QWidget *parent) : QWidget(parent), m_title (title), m_value(0)
{
    auto m_font = this->font();
    m_font.setPointSize(m_font.pointSize() * 2);
    this->setFont(m_font);
}

void ScoreLogo::setValue(int value)
{
    DigitalAnimation *animation = new DigitalAnimation(abs(m_value - value),this);
    animation->show();
    m_value = value;
    update ();
    animation->start();
}

void ScoreLogo::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setBrush(QColor("#F2B179"));
    painter.setPen(QColor("#808080"));
    painter.setRenderHint (QPainter::Antialiasing);
    painter.drawRoundedRect ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (), this->height ()/2), this->width ()/10, this->height ()/10);
    painter.drawText ( QRect( 0, this->height ()/2 - this->height ()/4, this->width (), this->height ()/2), Qt::AlignCenter, m_title.arg ( m_value));
}
