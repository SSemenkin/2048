#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include <QDebug>
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

    void keyPressEvent(QKeyEvent *event) override;

private Q_SLOTS:
    void moveLeft ();
    void moveRight();
    void moveUp();
    void moveDown();
    void updateScore(int value);
    void restartGame(int size = 4);
    bool isGameOver();
    void checkForGameOver();
    void updateBestScoreIsNeeded (int value);
    void on_action4x4_triggered();
    void on_action5x5_triggered();
    void on_action6x6_triggered();
    void on_action7x7_triggered();
    void on_action8x8_triggered();

private:
    Ui::MainWindow *ui;

    void initiateGame();
    void generateRandom();
    int size = 4;

    Cell2048** m_container;

    ScoreLogo *bestScore, *currentScore;
    NewGameButton *button;
    QSettings *settings;

};
#endif // MAINWINDOW_H
