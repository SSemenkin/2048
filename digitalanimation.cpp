#include "digitalanimation.h"

DigitalAnimation::DigitalAnimation(int value, QWidget *parent) : QWidget(parent), m_value(value)
{

}

void DigitalAnimation::start()
{
   QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);


   animation->setDuration  ( animationDuration);
   animation->setStartValue( this->geometry());
   animation->setKeyValueAt(0.5, this->geometry().adjusted(0, this->height(), 0, this->height()) );
   animation->setEasingCurve(QEasingCurve::InOutCubic);
   animation->setEndValue  ( this->geometry());
   animation->start();


   QObject::connect(animation, &QPropertyAnimation::finished ,[=] () {
       delete this;
   });

}

void DigitalAnimation::paintEvent(QPaintEvent *)
{
    if(m_value == 0)
        return;
    QPainter p(this);
    p.setBrush(Qt::transparent);
    p.setPen(QColor("#808080"));
    QString text;
    m_value >=0 ? text = QString("+%1").arg(m_value) : text = QString("%1").arg(m_value);
    p.drawText(this->rect(), Qt::AlignCenter, text);
}
