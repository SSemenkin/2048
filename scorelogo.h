#ifndef SCORELOGO_H
#define SCORELOGO_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include "digitalanimation.h"

class ScoreLogo : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreLogo(QString title,QWidget *parent = nullptr);
    void setValue(int value);
    int value () const {return m_value;}
signals:

protected:
    void paintEvent(QPaintEvent *event) override ;

private:
    QString m_title;
    int m_value;
};

#endif // SCORELOGO_H
