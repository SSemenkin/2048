#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), bestScore(new ScoreLogo("Лучший результат :\n %1", this)),
    currentScore (new ScoreLogo("Текущий результат :\n %1", this)), button( new NewGameButton(this)),
    settings (new QSettings( qApp->organizationName (), qApp->applicationName (), this))
{
    ui->setupUi(this);
    this->setWindowTitle (qApp->applicationName ());
    srand(time(NULL));
    ui->gridLayout->addWidget (currentScore, 0, 1);
    ui->gridLayout->addWidget (bestScore, 0, 2);
    ui->gridLayout->addWidget (button, 0, 3);
    initiateGame ();
    QObject::connect (button, &NewGameButton::initiateNewGame, this, &MainWindow::restartGame);
}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i = 0; i < size; i++) {
        delete[] m_container[i];
    }
    delete [] m_container;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << QString ("key Press Event ") << event;
    switch (event->key ()) {
    case Qt::Key_A:
    case Qt::Key_Left :
        moveLeft ();
        break;

    case Qt::Key_D:
    case Qt::Key_Right :
        moveRight ();
        break;

    case Qt::Key_W:
    case Qt::Key_Up:
        moveUp ();
        break;

    case Qt::Key_S:
    case Qt::Key_Down:
        moveDown ();
        break;
    }
}

void MainWindow::moveLeft()
{
    bool isRandomValueNeededToGenerate = false;
    // смещаем пока всё влево
    // заменяя пустоты на цифры справа
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size - 1; column ++) {
            if ( m_container[row][column].text ().isEmpty () && !m_container[row][column + 1].text ().isEmpty ()) {
                m_container[row][column].setText (m_container[row][column + 1].text());
                m_container[row][column+1].setText ("");
                column = 0;
                row = 0;
                isRandomValueNeededToGenerate = true;
            }
        }
    }
    // тут мы сложили одинаковые цифры
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size - 1 ;column ++) {
            if(m_container[row][column].text () == m_container[row][column + 1].text () && !m_container[row][column].text ().isEmpty ()) {
                m_container[row][column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row][column + 1].setText ("");
                isRandomValueNeededToGenerate = true;
            }
        }
    }
    // и еще раз сдвинули
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size-1; column ++) {
            if ( m_container[row][column].text ().isEmpty () && !m_container[row][column + 1].text ().isEmpty ()) {
                m_container[row][column].setText (m_container[row][column + 1].text());
                m_container[row][column + 1].setText ("");
                column = 0;
                row = 0;
                isRandomValueNeededToGenerate = true;
            }
        }
    }


    if(isRandomValueNeededToGenerate) generateRandom ();
}

void MainWindow::moveRight()
{
    bool isRandomValueNeededToGenerate = false;
    // смещаем пока всё вправо
    // заменяя пустоты на цифры слева
    for (int row = 0; row < size; row ++){
        for (int column = size - 1; column > 0; column -- ){
            if(m_container[row][column].text().isEmpty () && !m_container[row][column - 1].text ().isEmpty ()) {
                m_container[row][column].setText (m_container[row][column - 1].text ());
                m_container[row][column - 1].setText ("");

                column = size - 1;
                isRandomValueNeededToGenerate = true;
            }
        }
    }
    // тут мы сложили одинаковые цифры
    for (int row = 0; row < size; row++) {
        for (int column = size - 1; column > 0 ;column --) {
            if(m_container[row][column].text () == m_container[row][column - 1].text () && !m_container[row][column].text ().isEmpty ()) {
                m_container[row][column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row][column - 1].setText ("");
                isRandomValueNeededToGenerate = true;
            }
        }
    }
//    // и еще раз сдвинули
    for (int row = 0; row < size; row ++){
        for (int column = size - 1; column > 0; column -- ){
            if(m_container[row][column].text().isEmpty () && !m_container[row][column - 1].text ().isEmpty ()) {
                m_container[row][column].setText (m_container[row][column - 1].text ());
                m_container[row][column - 1].setText ("");

                column = size - 1;
                isRandomValueNeededToGenerate = true;
            }
        }
    }


    if(isRandomValueNeededToGenerate) generateRandom ();
}

void MainWindow::moveUp()
{
    bool isRandomValueNeededToGenerate = false;
    // смещаем пока всё влево
    // заменяя пустоты на цифры справа
    for (int column = 0; column < size; column ++) {
        for( int row = 0; row < size - 1; row ++) {
            if(m_container[row] [column].text ().isEmpty () && !m_container[row+1][column].text ().isEmpty ()) {
                m_container[row] [column].setText (m_container[row+1][column].text ());
                m_container[row+1][column].setText ("");

                row = 0;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    for (int column = 0; column < size; column ++) {
        for( int row = 0; row < size - 1; row ++) {
            if(m_container[row] [column].text () == m_container[row+1][column].text () && !m_container[row][column].text ().isEmpty ()) {
                m_container[row] [column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row+1][column].setText ("");
                row = 0;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    for (int column = 0; column < size; column ++) {
        for( int row = 0; row < size - 1; row ++) {
            if(m_container[row] [column].text ().isEmpty () && !m_container[row+1][column].text ().isEmpty ()) {
                m_container[row] [column].setText (m_container[row+1][column].text ());
                m_container[row+1][column].setText ("");

                row = 0;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    if(isRandomValueNeededToGenerate) generateRandom ();
}

void MainWindow::moveDown()
{
    bool isRandomValueNeededToGenerate = false;
    // смещаем пока всё влево
    // заменяя пустоты на цифры справа
    for (int column = 0; column < size; column ++) {
        for( int row = size -1 ; row > 0; row --) {
            if(m_container[row] [column].text ().isEmpty () && !m_container[row - 1][column].text ().isEmpty ()) {
                m_container[row] [column].setText (m_container[row - 1][column].text ());
                m_container[row - 1][column].setText ("");

                row = size - 1;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    for (int column = 0; column < size; column ++) {
        for( int row = size - 1; row > 0 ; row --) {
            if(m_container[row] [column].text () == m_container[row - 1][column].text () && !m_container[row][column].text ().isEmpty ()) {
                m_container[row] [column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row - 1][column].setText ("");

                row = size - 1;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    for (int column = 0; column < size; column ++) {
        for( int row = size -1 ; row > 0; row --) {
            if(m_container[row] [column].text ().isEmpty () && !m_container[row - 1][column].text ().isEmpty ()) {
                m_container[row] [column].setText (m_container[row - 1][column].text ());
                m_container[row - 1][column].setText ("");

                row = size - 1;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    if(isRandomValueNeededToGenerate) generateRandom ();
}

void MainWindow::updateScore(int value)
{
    int newValue = currentScore->value () + value;
    currentScore->setValue (newValue);

    if(bestScore->value () < newValue) bestScore->setValue (newValue);
}

void MainWindow::restartGame()
{
    // to do bestScore update if needed
    currentScore->setValue ( 0);

    for (int row = 0; row < size; row ++) {
        for (int col = 0; col < size; col ++) {
            ui->gridLayout->removeWidget (&m_container[row][col]);
        }
    }

    for (int i = 0; i < size; i++) {
        delete[] m_container[i];
    }
    delete [] m_container;

    initiateGame ();

}

bool MainWindow::isGameOver()
{

}

void MainWindow::initiateGame()
{
    ui->gridLayout->setSpacing (10);
    m_container = new Cell2048* [size];

    for (int i = 0; i < size; i++) {
        m_container[i] = new Cell2048[size];
    }

    for (int i = 0; i < size; i ++) {
        for( int j = 0; j < size; j++) {
            ui->gridLayout->addWidget (&m_container[i][j], i+1 , j);
        }
    }
    for (int i = 0; i < size/2; i ++)
        generateRandom ();

    if(settings->contains ("bestScore"))  bestScore->setValue (settings->value ("bestScore").toInt ());
}

void MainWindow::generateRandom()
{
    QList < Cell2048*> emptyCells;
    for (int i = 0; i < size; i++) {
        for( int j = 0; j < size; j++) {
            if(m_container[i][j].text ().isEmpty ()) emptyCells << &m_container[i][j];
        }
    }

    int index = rand() % emptyCells.size ();
    emptyCells[index]->setText (index % 2 ? "2" : "4");
}
