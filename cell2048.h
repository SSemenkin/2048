#ifndef CELL2048_H
#define CELL2048_H

#include <QWidget>
#include <QPainter>

class Cell2048 : public QWidget
{
    Q_OBJECT
public:
    explicit Cell2048(QWidget *parent = nullptr);

    QString text () const { return m_text; }
    void setText(const QString &text) {m_text = text; update (); }

protected:
    void paintEvent(QPaintEvent *event) override ;
signals:

private:
    QColor colorFromValue(const int &value) const;

    QString m_text;
};

#endif // CELL2048_H
