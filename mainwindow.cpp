/**
 * @file mainwindow.cpp
 * @brief creates the mainwindow UI where the player can start a game or reach the instructions
*/

#include "mainwindow.h"
#include "gameboard.h"
#include "ui_mainwindow.h"
#include <QWidget>

/**
 * @brief constructor for the MainWindow class, sets up the ui, blocks access to level 2 and 3.
 * */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(550,600);

    // set MainWindow's style
    this->setStyleSheet("MainWindow{ border-image: url(:/images/jellies.jpg);}"
                        "QPushButton{ color: white; background-color: blue; "
                        "font-family: Odin Rounded; font-size: 14px; color: white;}"
                        "QPushButton:hover{ color: blue; background-color: white }");

    // block access to more advanced levels if the user has not completed the previous levels first.
    unlock_medium_ = 0;
    unlock_hard_ = 0;
}

/**
 * @brief launches a new game at a low speed at the first level.
 * The function is triggered by an on click event on the push button "Level 1 - Easy".
 * */
void MainWindow::on_Easy_clicked()
{
    board = new GameBoard(this,50,1);
    this->setCentralWidget(board);
}

/**
 * @brief launches a new game at a medium speed at the second level.
 * The function is triggered by an on click event on the push button "Level 2 - Medium".
 * If medium level is not unlocked, does not launch a new game and displays a dialog box.
 * */
void MainWindow::on_Medium_clicked()
{
    if(unlock_medium_){
    board = new GameBoard(this,10,2);
    this->setCentralWidget(board);
    }
    // if player has not passed level 1
    else{
        QDialog* no_access_medium = new QDialog(this);
        QVBoxLayout *piece_together = new QVBoxLayout(no_access_medium);

        QLabel* access_text = new QLabel("You cannot access this level. You have to pass level 1 first.");
        access_text->setStyleSheet("QLabel{ color: white; font: 20px Odin Rounded, sans-serif; }");

        QPushButton* ok = new QPushButton("Ok");
        ok->setStyleSheet("QPushButton{ background-color: white; color: blue; font: 20px Odin Rounded, sans-serif; }");
        QObject::connect(ok, SIGNAL(clicked()), no_access_medium, SLOT(close()));
        ok->setFixedSize(50,25);

        piece_together->addWidget(access_text,0,Qt::AlignCenter);
        piece_together->addWidget(ok, 0,Qt::AlignCenter);

        /*** change image path here ***/
        // set image with the instructions
        no_access_medium->setStyleSheet("QDialog{ border-image: url(:/images/jellies.jpg);}");
        no_access_medium->exec();
    }
}

/**
 * @brief launches a new game for at a high speed at the third level.
 * The function is triggered by an on click event on the push button "Level 3 - Hard".
 * If hard level is not unlocked, does not launch a new game and displays a dialog box.
 * */
void MainWindow::on_Hard_clicked()
{
    if(unlock_hard_){
    board = new GameBoard(this,1,3);
    this->setCentralWidget(board);
    }
    // if player has not passed level 2
    else{
        QDialog* no_access_medium = new QDialog(this);
        QVBoxLayout *piece_together = new QVBoxLayout(no_access_medium);

        QLabel* access_text = new QLabel("You cannot access this level. You have to pass level 2 first.");
        access_text->setStyleSheet("QLabel{ color: white; font: 20px Odin Rounded, sans-serif; }");

        QPushButton* ok = new QPushButton("Ok");
        ok->setStyleSheet("QPushButton{ background-color: white; color: blue; font: 20px Odin Rounded, sans-serif; }");
        QObject::connect(ok, SIGNAL(clicked()), no_access_medium, SLOT(close()));
        ok->setFixedSize(50,25);

        piece_together->addWidget(access_text,0,Qt::AlignCenter);
        piece_together->addWidget(ok, 0,Qt::AlignCenter);

        /*** change image path here ***/
        // set image with the instructions
        no_access_medium->setStyleSheet("QDialog{ border-image: url(:/images/jellies.jpg);}");
        no_access_medium->exec();
    }
}

/**
 * @brief calls the current board game to take it out of the central widget,
 * and then resets the MainWindow to the initial screen.
 * */
void MainWindow::game_over() {
    // Call the current board game to move out of the central widget of MainWindow
    QWidget* central_widget = this->centralWidget();
    // Delete the widget
    central_widget->setParent(nullptr);
    // Reset the MainWindow with the initial screen
    ui->setupUi(this);
    this->setFixedSize(550,600);
}

/**
 * @brief the destructor for the MainWindow class
 * */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief displays the Instructions to play the Angry Jellies game
 * */
void MainWindow::on_Instructions_clicked()
{
    // new dialog box
    QDialog* Instructions = new QDialog(this);
    /*** change image path here ***/
    // set image with the instructions
    Instructions->setStyleSheet("QDialog{ border-image: url(:/images/Instructions.png); }");
    // prevent from being resized
    Instructions->setFixedSize(768,512);
    Instructions->exec();
}

/**
 * @brief unlocks the access to the second level for the player.
 */
void MainWindow::unlock_medium(){
    unlock_medium_ = 1;
}

/**
 * @brief unlocks the access to the third level for the player.
 */
void MainWindow::unlock_hard(){
    unlock_hard_ = 1;
}

/**
 * @brief closes the application
 */
void MainWindow::on_Quit_clicked()
{
    this->close();
}
