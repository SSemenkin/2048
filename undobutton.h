#ifndef UNDOBUTTON_H
#define UNDOBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class UndoButton : public QWidget
{
    Q_OBJECT
public:
    explicit UndoButton(QWidget *parent = nullptr);
    void setMatrix (QVector<QVector<int>> data) {m_data = data;}
    QVector<QVector<int>> data () const { return m_data;}

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void undo(QVector<QVector<int>>);

private:
    QString label;
    QPixmap pixmap;
    QVector < QVector <int>> m_data;

};

#endif // UNDOBUTTON_H
