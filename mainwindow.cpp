#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), bestScore(new ScoreLogo("Best Score :\n %1", this)),
    currentScore (new ScoreLogo("Score :\n %1", this)), button( new NewGameButton(this)), undoButton(new UndoButton(this)),
    settings (new QSettings( qApp->organizationName (), qApp->applicationName (), this))
{
    ui->setupUi(this);
    this->setWindowTitle (qApp->applicationName ());
    srand(time(NULL));

    ui->gridLayout->addWidget (undoButton, 0, 0);
    ui->gridLayout->addWidget (currentScore, 0, 1);
    ui->gridLayout->addWidget (bestScore, 0, 2);
    ui->gridLayout->addWidget (button, 0, 3);
    initiateGame ();

    QObject::connect (button, &NewGameButton::initiateNewGame, [=](){
        this->restartGame ();
    });
    QObject::connect (ui->action_4, &QAction::triggered, qApp, &QCoreApplication::quit);
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

        switch (event->key ()) {
        case Qt::Key_A:
        case Qt::Key_Left :
            moveLeft ();
            checkForGameOver ();
            break;

        case Qt::Key_D:
        case Qt::Key_Right :
            moveRight ();
            checkForGameOver ();
            break;

        case Qt::Key_W:
        case Qt::Key_Up:
            moveUp ();
            checkForGameOver ();
            break;

        case Qt::Key_S:
        case Qt::Key_Down:
            moveDown ();
            checkForGameOver ();
            break;
        }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::moveLeft()
{
    bool isRandomValueNeededToGenerate = false;
    // смещаем пока всё влево
    // заменяя пустоты на цифры справа
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size - 1; column ++) {
            if ( m_container[row][column].text ().isEmpty () && !m_container[row][column + 1].text ().isEmpty ()) {
                m_container[row][column].animate(Cell2048::Direction::Left);
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
                m_container[row][column].animate(Cell2048::Direction::Left);
                m_container[row][column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row][column + 1].setText ("");
                column++;
                isRandomValueNeededToGenerate = true;
            }
        }
    }
    // и еще раз сдвинули
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size-1; column ++) {
            if ( m_container[row][column].text ().isEmpty () && !m_container[row][column + 1].text ().isEmpty ()) {
                m_container[row][column].animate(Cell2048::Direction::Left);
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
                m_container[row][column].animate(Cell2048::Direction::Right);
                m_container[row][column].setText (m_container[row][column - 1].text ());
                m_container[row][column - 1].setText ("");
                row = 0;
                column = size - 1;
                isRandomValueNeededToGenerate = true;
            }
        }
    }
    // тут мы сложили одинаковые цифры
    for (int row = 0; row < size; row++) {
        for (int column = size - 1; column > 0 ;column --) {
            if(m_container[row][column].text () == m_container[row][column - 1].text () && !m_container[row][column].text ().isEmpty ()) {
                m_container[row][column].animate(Cell2048::Direction::Right);
                m_container[row][column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row][column - 1].setText ("");
                isRandomValueNeededToGenerate = true;
                column --;
            }
        }
    }
//    // и еще раз сдвинули
    for (int row = 0; row < size; row ++){
        for (int column = size - 1; column > 0; column -- ){
            if(m_container[row][column].text().isEmpty () && !m_container[row][column - 1].text ().isEmpty ()) {
                m_container[row][column].animate(Cell2048::Direction::Right);
                m_container[row][column].setText (m_container[row][column - 1].text ());
                m_container[row][column - 1].setText ("");
                row = 0;
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
                m_container[row][column].animate(Cell2048::Direction::Up);
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
                m_container[row][column].animate(Cell2048::Direction::Up);
                m_container[row] [column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row+1][column].setText ("");
                row ++;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    for (int column = 0; column < size; column ++) {
        for( int row = 0; row < size - 1; row ++) {
            if(m_container[row] [column].text ().isEmpty () && !m_container[row+1][column].text ().isEmpty ()) {
                m_container[row][column].animate(Cell2048::Direction::Up);
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
                m_container[row][column].animate(Cell2048::Direction::Down);
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
                m_container[row][column].animate(Cell2048::Direction::Down);
                m_container[row] [column].setText (QString::number (m_container[row][column].text ().toInt () * 2));
                updateScore (m_container[row][column].text ().toInt ());
                m_container[row - 1][column].setText ("");

                row --;
                isRandomValueNeededToGenerate = true;
            }
        }
    }

    for (int column = 0; column < size; column ++) {
        for( int row = size - 1 ; row > 0; row --) {
            if(m_container[row] [column].text ().isEmpty () && !m_container[row - 1][column].text ().isEmpty ()) {
                m_container[row][column].animate(Cell2048::Direction::Down);
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

void MainWindow::restartGame( int size)
{
    type = m_container[0][0].paintType();
    count = 0;
    isContinueAfterWinning = false;
    updateBestScoreIsNeeded (bestScore->value ());
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
    //есть ли пустые клетки?
    for(int i = 0; i < size; i++) {
        for (int j = 0; j <size; j++) {
            if(m_container[i][j].text ().isEmpty ()) return false;
        }
    }
    // по строкам прошлись
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if(m_container[i][j].text () == m_container[i][j+1].text () && !m_container[i][j].text ().isEmpty ()) {
                return false;
            }
        }
    }
    // теперь по столбцам
    for (int col = 0; col < size; col ++) {
        for (int row = 0; row < size-1; row++) {
            if(m_container[row][col].text () == m_container[row+1][col].text () && !m_container[row][col].text ().isEmpty ()) {
                return false;
            }
        }
    }

    return true;
}

void MainWindow::checkForGameOver()
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (m_container[i][j].text().toInt() == 2048 && !isContinueAfterWinning) {
                if(QMessageBox::question (this, "", "Hoooray!!!You win!!!\nDo you want to start new game?") == QMessageBox::StandardButton::Yes) {
                    restartGame ();
                } else isContinueAfterWinning = true;
            }
        }
    }

    if(isGameOver ()) {

        updateBestScoreIsNeeded (bestScore->value ());
        if(QMessageBox::question (this, "", "Game Over!You lose!\nDo you want to start new game?") == QMessageBox::StandardButton::Yes) {
            restartGame ();
        }
    }

}

void MainWindow::updateBestScoreIsNeeded(int value)
{
    if(settings->contains ("bestScore")) {
        if(settings->value ("bestScore").toInt () < value) {
            settings->setValue ("bestScore", value);
        }
    } else settings->setValue ("bestScore", value);
}


void MainWindow::initiateGame()
{
    m_container = new Cell2048* [size];

    for (int i = 0; i < size; i++) {
        m_container[i] = new Cell2048[size];
    }


    for (int i = 0; i < size; i ++) {
        for( int j = 0; j < size; j++) {
            ui->gridLayout->addWidget (&m_container[i][j], i+1 , j);

            if( m_container[i][j].paintType() != type) m_container[i][j].changePaintType();
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

    if(count > size/2) {
        for (int i = 0; i < size ; i++)
            for (int j=0; j< size;j++) {
                if(emptyCells[index] == &m_container[i][j]) {
                   if( i < size/2 && j < size/2) {
                        m_container[i][j].animate(Cell2048::Direction::LeftNorth);
                   } else if( i < size/2 && j > size/2) {
                        m_container[i][j].animate(Cell2048::Direction::RightHorth);
                   } else if (i >= size/2 && j < size/2) {
                        m_container[i][j].animate(Cell2048::Direction::LeftSouth);
                   } else {
                       m_container[i][j].animate(Cell2048::Direction::RightSouth);
                   }
                   break;
            }
        }
    }

    count ++;

    emptyCells[index]->setText (index % 10 ? "2" : "4");
}

void MainWindow::on_action4x4_triggered()
{
    int oldSize = size;
    size = 4;
    restartGame (oldSize);
    ui->action4x4->setChecked (true);
    ui->action5x5->setChecked (false);
    ui->action6x6->setChecked (false);
    ui->action7x7->setChecked (false);
    ui->action8x8->setChecked (false);
}

void MainWindow::on_action5x5_triggered()
{
    int oldSize = size;
    size = 5;
    restartGame (oldSize);
    ui->action4x4->setChecked (false);
    ui->action5x5->setChecked (true);
    ui->action6x6->setChecked (false);
    ui->action7x7->setChecked (false);
    ui->action8x8->setChecked (false);
}

void MainWindow::on_action6x6_triggered()
{
    int oldSize = size;
    size = 6;
    restartGame (oldSize);
    ui->action4x4->setChecked (false);
    ui->action5x5->setChecked (false);
    ui->action6x6->setChecked (true);
    ui->action7x7->setChecked (false);
    ui->action8x8->setChecked (false);
}

void MainWindow::on_action7x7_triggered()
{
    int oldSize = size;
    size = 7;
    restartGame (oldSize);
    ui->action4x4->setChecked (false);
    ui->action5x5->setChecked (false);
    ui->action6x6->setChecked (false);
    ui->action7x7->setChecked (true);
    ui->action8x8->setChecked (false);
}

void MainWindow::on_action8x8_triggered()
{
    int oldSize = size;
    size = 8;
    restartGame (oldSize);
    ui->action4x4->setChecked (false);
    ui->action5x5->setChecked (false);
    ui->action6x6->setChecked (false);
    ui->action7x7->setChecked (false);
    ui->action8x8->setChecked (true);
}

void MainWindow::on_actionChange_cell_Type_triggered()
{
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size ; j++) {
            m_container[i][j].changePaintType();
        }
    }
}
