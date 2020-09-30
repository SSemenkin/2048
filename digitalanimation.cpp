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
   animation->start(QAbstractAnimation::DeleteWhenStopped);
   QTimer *timer = new QTimer(this);
   timer->start(animationDuration);
   QObject::connect(timer, &QTimer::timeout ,[=] () {
       timer->stop();
       timer->deleteLater();
       this->hide();
       delete this;
   });

}

void DigitalAnimation::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::transparent);
    p.setPen(QColor("#808080"));
    p.drawText(this->rect(), Qt::AlignCenter, QString("+%1").arg(m_value));
}
