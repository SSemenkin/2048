#ifndef NEWGAMEBUTTON_H
#define NEWGAMEBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>

class NewGameButton : public QWidget
{
    Q_OBJECT
public:
    explicit NewGameButton(QWidget *parent = nullptr);

signals:
    void initiateNewGame();

protected:
    void paintEvent(QPaintEvent *) override;
private:


};

#endif // NEWGAMEBUTTON_H
