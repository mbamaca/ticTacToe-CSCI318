#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QWidget>
#include <QtWidgets>
#include <QLayout>
#include <QtGui>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameDone(false)

{
    ui->setupUi(this);

    QWidget *center = new QWidget();
    setCentralWidget(center);

    QVBoxLayout *mainLayout = new QVBoxLayout(center);

    /* rules and instructions button */
    QPushButton *welcomeButton = new QPushButton("Welcome to Tic tac toe! Player X starts!");
    mainLayout->addWidget(welcomeButton);

    /* use this button for resetting game */
    QPushButton *resetButton = new QPushButton("Press me to reset!");
    mainLayout->addWidget(resetButton);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetButtonClicked);

    QPushButton *closeButton = new QPushButton("Press me to close game!");
    mainLayout->addWidget(closeButton);
    /* signal stuff */
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeButtonClicked);

    /* our grid for tic tac toe */
    QGridLayout *gameGrid = new QGridLayout();

    /* Game grid should be 3 rows and 3 columns */
    for(int i=0; i < 3; i++) {
        for(int j=0; j < 3; j++) {

            buttons[i][j] = new QPushButton(this);
            gameGrid->addWidget(buttons[i][j], j, i);
            connect(buttons[i][j], &QPushButton::clicked,this, &MainWindow::gameButtonClicked);
        }

        /* position game grid in center */
        mainLayout->addLayout(gameGrid);
    }
}


/* first player will always be X */
QString currentPlayer = "X";

/* Players should alternate when playing the game */
void MainWindow::gameButtonClicked() {

    if(gameDone) {
        return; /* no more moves if game is done */
    }

    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if(button && button->text().isEmpty()) {
        button->setText(currentPlayer);
        currentPlayer = (currentPlayer == "X") ? "O" : "X";
    }

    /* after one move should be checking for winner */
    checkWinner();
}


void MainWindow::resetButtonClicked() {

    for(int i=0; i < 3; i++) {
        for(int j=0; j < 3; j++) {

            buttons[i][j]->setText("");
            /* reenable our buttons */
            buttons[i][j]->setEnabled(true);
        }
    }
    /* reset current player */
    currentPlayer = 'X';
    gameDone = false;
}


void MainWindow::closeButtonClicked() {
    closeButton->setEnabled(false) ;

}


/* check for either winner or draws */
void MainWindow::checkWinner() {
    bool win = false;

    /* winning conditions */
    for (int i = 0; i < 3; i++) {
        /* checking columns */
        if(buttons[i][0]->text() == 'X' && buttons[i][1]->text() == 'X' && buttons[i][2]->text() == 'X' && !buttons[i][0]->text().isEmpty()) {
            win = true;
            break;
        }
        if(buttons[i][0]->text() == 'O' && buttons[i][1]->text() == 'O' && buttons[i][2]->text() == 'O' && !buttons[i][0]->text().isEmpty()) {
            win = true;
            break;
        }

        /* checking rows */
        if(buttons[0][i]->text() == 'X' && buttons[1][i]->text() == 'X' && buttons[2][i]->text() == 'X' && !buttons[0][i]->text().isEmpty()) {
            win = true;
            break;
        }
        if(buttons[0][i]->text() == 'O' && buttons[1][i]->text() == 'O' && buttons[2][i]->text() == 'O' && !buttons[0][i]->text().isEmpty()) {
            win = true;
            break;
        }
    }

    /* checkng diagnols */
    if(buttons[0][0]->text() == 'X' && buttons[1][1]->text() == 'X' && buttons[2][2]->text() == 'X' && !buttons[0][0]->text().isEmpty()) {
        win = true;
    }
    if(buttons[0][0]->text() == 'O' && buttons[1][1]->text() == 'O' && buttons[2][2]->text() == 'O' && !buttons[0][0]->text().isEmpty()) {
        win = true;
    }
    if(buttons[2][0]->text() == 'X' && buttons[1][1]->text() == 'X' && buttons[0][2]->text() == 'X' && !buttons[2][0]->text().isEmpty()) {
        win = true;
    }
    if(buttons[2][0]->text() == 'O' && buttons[1][1]->text() == 'O' && buttons[0][2]->text() == 'O' && !buttons[2][0]->text().isEmpty()) {
        win = true;
    }

    if(win) {
        showWinner();
        return;
    }

    /* checking for draw */
    bool draw = true;
    for(int i=0; i < 3; i++) {
        for(int j=0; j < 3; j++) {
            if(buttons[i][j]->text().isEmpty()) {
                draw = false;
                break;
            }
        }
        if(!draw) {
            break;
        }
    }

    if(draw) {
        showDraw();
    }
}


void MainWindow::showDraw() {

    QMessageBox msgBox;
    msgBox.setText("Draw! NO WINNER!");
    msgBox.exec();

    /* to avoid any extra popups happening */
    for(int i=0; i < 3; i++) {
        for(int j=0; j < 3; j++) {
            buttons[i][j]->setEnabled(false);
        }
    }
    gameDone = true;  /* set game as finished */
}


void MainWindow::showWinner() {

    QMessageBox msgBox;
    msgBox.setText("3 IN A ROW! we have a winner!");
    msgBox.exec();

    /* to avoid any extra popups happening */
    for(int i=0; i < 3; i ++) {
        for(int j=0; j < 3; j++) {
            buttons[i][j]->setEnabled(false);
        }
    }
    gameDone = true;
}


MainWindow::~MainWindow()
{
    delete ui;
}





