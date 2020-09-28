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
    void restartGame();
    bool isGameOver();
    void checkForGameOver();
    void updateBestScoreIsNeeded (int value);

private:
    Ui::MainWindow *ui;

    void initiateGame();
    void generateRandom();
    const int size = 4;

    Cell2048** m_container;

    ScoreLogo *bestScore, *currentScore;
    NewGameButton *button;
    QSettings *settings;

};
#endif // MAINWINDOW_H
