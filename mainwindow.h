#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QPropertyAnimation>
#include <QTimer>

#include "cell2048.h"
#include "scorelogo.h"
#include "newgamebutton.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    enum Direction {
        LEFT,RIGHT,DOWN,UP
    };

    void keyPressEvent(QKeyEvent *event) override;

private Q_SLOTS:
    void moveLeft ();
    void moveRight();
    void moveUp();
    void moveDown();
    void updateScore(int value);
    void restartGame(int size = 4);
    bool isGameOver();
    void initiateGame();
    void generateRandom();
    void checkForGameOver();
    void updateBestScoreIsNeeded (int value);
    void animateCell (int row, int column, Direction);
    void on_action4x4_triggered();
    void on_action5x5_triggered();
    void on_action6x6_triggered();
    void on_action7x7_triggered();
    void on_action8x8_triggered();

    void on_actionChange_cell_Type_triggered();

private:
    Ui::MainWindow *ui;

    int size = 4;
    const int animationDuration = 25;

    Cell2048** m_container;

    ScoreLogo *bestScore, *currentScore;
    NewGameButton *button;
    QSettings *settings;

    int count = 0; // not sure about this

    QTimer keyEventTimer;
    bool animationEnabled;

};
#endif // MAINWINDOW_H
