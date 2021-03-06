#ifndef CELL2048_H
#define CELL2048_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QMap>
#include <QPropertyAnimation>


class Cell2048 : public QWidget
{
    Q_OBJECT
public:
    enum Direction {
        Left, Right, Up, Down, LeftNorth, RightHorth, LeftSouth, RightSouth
    };

    explicit Cell2048(QWidget *parent = nullptr);
    QString text () const { return m_text; }
    void setText(const QString &text) {m_text = text; update (); }
    bool paintType () const { return paintDigits;}
    void changePaintType () {
        paintDigits  = !paintDigits;
        update();
    };
    void animate(Direction direction) ;
    bool isAnimatedAvaliable() const { return isAnimated;}




protected:
    void paintEvent(QPaintEvent *event) override ;
    void resizeEvent(QResizeEvent *event) override;
signals:

private:

    QColor backgroundFromValue(const int &value) ;
    QPixmap mapFromValue() ;
    QColor foregroundColor;

    QString m_text;
    bool paintDigits;
    bool isAnimated;

    const int animationDuration = 100;


};

#endif // CELL2048_H
