/**
 * @file gameboard.h
 * @brief holds the declaration for the GameBoard class which handles the settings for the game to be run and playable
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <iostream>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include <QMouseEvent>
#include <QDialog>
#include <QElapsedTimer>
#include <QPushButton>
#include <QString>
#include <iomanip>

namespace Ui {
class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
    void move_jellies();
    void start_game();


signals:
    void _game_over();
    void _medium_game();
    void _hard_game();
    void _unlock_medium();
    void _unlock_hard();

public:
    explicit GameBoard(QWidget *parent = 0, size_t jellies_speed = 10, unsigned int level = 1);
    ~GameBoard();

    // Events
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);
    void mousePressEvent ( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event  );

    //move a jelly
    void move_jelly(size_t jelly_number, int x_step, int y_step);
    //end the game
    void end_the_game();
    //check that the player's jelly does not hit any colored jelly
    bool hit_jelly();
    //check that the player's jelly does not hit any border
    bool hit_borders();

private:
    Ui::GameBoard *ui;

    // Elements positions
    // Player's jelly position and size
    double x_player_jelly, y_player_jelly;
    const double width_player_jelly = 40.0;
    const double height_player_jelly = 40.0;
    // jellies' positions
    double* x_jellies;
    double* y_jellies;
    double* width_jellies;
    double* height_jellies;
    // number of jellies
    size_t number_jellies;
    // directions of the jellies
    double* dirx_jellies;
    double* diry_jellies;
    //jellies speed
    size_t jellies_speed;
    // images
    QPixmap* player_jelly_image;
    QPixmap* jelly_image_0;
    QPixmap* jelly_image_1;
    QPixmap* jelly_image_2;
    QPixmap* jelly_image_3;
    // gameboard background images
    QPixmap* large_square_border;
    QPixmap* large_square;
    QPixmap* larger_square_border;

    // Top bar variables
    QLabel* level_value;
    unsigned int level;
    QLabel* time_value;
    QWidget* Top;

    //time variables
    QElapsedTimer* time;
    QTimer* timer;
    double seconds;

    // score
    QString score;

    // game handlers
    bool game_on;

    // Board Variables
    QWidget* Board;

    // game over dialog box
    QDialog* GameOver;
    QLabel* GameOver_text;
    QPushButton* GameOver_pushbutton;
};

#endif // GAMEBOARD_H
