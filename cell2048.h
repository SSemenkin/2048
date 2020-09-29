#ifndef CELL2048_H
#define CELL2048_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMap>

class Cell2048 : public QWidget
{
    Q_OBJECT
public:

    explicit Cell2048(QWidget *parent = nullptr);

    QString text () const { return m_text; }
    void setText(const QString &text) {m_text = text; update (); }
    void changePaintType () {
        paintDigits  = !paintDigits;
        update();
    };




protected:
    void paintEvent(QPaintEvent *event) override ;
signals:

private:
    QColor backgroundFromValue(const int &value) ;
    QPixmap mapFromValue() ;
    QColor foregroundColor;

    QString m_text;
    bool paintDigits;
};

#endif // CELL2048_H
