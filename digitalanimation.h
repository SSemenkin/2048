#ifndef DIGITALANIMATION_H
#define DIGITALANIMATION_H

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>


class DigitalAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalAnimation(int value,QWidget *parent = nullptr);
    void start ();

protected:
    void paintEvent(QPaintEvent *) override ;
signals:

private:
    int m_value;

    const int animationDuration = 1000;
};

#endif // DIGITALANIMATION_H
