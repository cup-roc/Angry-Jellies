/**
 * @file mainwindow.h
 * @brief holds the declaration for the MainWindow class which handles the slots to access
 * the instructions and the different levels within the game.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void game_over();
    void on_Easy_clicked();
    void on_Medium_clicked();
    void on_Hard_clicked();
    void unlock_medium();
    void unlock_hard();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Instructions_clicked();
   void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
    GameBoard* board;

    // level accessors
    bool unlock_medium_;
    bool unlock_hard_;
};

#endif // MAINWINDOW_H
