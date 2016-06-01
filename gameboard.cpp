/**
 * @file gameboard.cpp
 * @brief sets up the gameboard UI where the player can actually play the game
*/

#include "gameboard.h"
#include "mainwindow.h"
#include "ui_gameboard.h"

/**
 * @brief Constructor for the GameBoard class sets the Central Widget of the MainWindow to the game board.
 * @param parent Central Widget
 * @param jellies_speed the speed of the jellies
 * @param lvl game level
 * */
GameBoard::GameBoard(QWidget *parent, size_t jellies_speed, unsigned int lvl) :
    QWidget(parent),
    ui(new Ui::GameBoard), jellies_speed(jellies_speed), level(lvl)
{
    ui->setupUi(this);

    // Create the top widget, that will
    Top = new QWidget;
    // This code creates the Top bar
    // Level: #      Timer: #

    Top->setFixedSize(450,40);
    // set style of the top bar
    Top->setStyleSheet("QLabel{ font-family: Odin Rounded; font-size: 18px; color: white; }");

    // Create the top bar
    QHBoxLayout *top_bar = new QHBoxLayout(Top);
    // top_bar layout is used to space the elements from the Top Widget and the _Board Widget.
    // Level: #
    QLabel* level_text = new QLabel("Level: ");
    level_value = new QLabel(QString::number(level)); // level is either 1, 2 or 3
    // Add the level widgets to the Top bar
    top_bar->addWidget(level_text);
    top_bar->addWidget(level_value);
    // Add in horizontal space before the next labels
    QSpacerItem* horizontal_space = new QSpacerItem(200,10);
    // Add the horizontal space to the top_bar layout
    top_bar->addSpacerItem(horizontal_space);

    // Level: #      Timer: #
    QLabel* time_text = new QLabel("Timer: ");
    time_value = new QLabel(QString::number(0)); // start at 0 seconds

    top_bar->addWidget(time_text);
    top_bar->addWidget(time_value);

    // Create the Board
    Board = new QWidget;
    Board->setFixedSize(450,450);

    // Now we piece everything together
    // Central Widget is composed of Top and Board
    //    Top
    // --------
    //   Board

    // Do not allow board to be resized, otherwise spacings get messed up
    setFixedSize(550,550);

    // Create a vertical box layout for the two pieces
    QVBoxLayout *piece_together = new QVBoxLayout;

    piece_together->addWidget(Top,0,Qt::AlignCenter);
    piece_together->addWidget(Board,0,Qt::AlignCenter);

    QPushButton* quit = new QPushButton("Quit");
    quit->setFixedSize(450, 30);
    QObject::connect(quit, SIGNAL(clicked()), parent, SLOT(game_over()));

    piece_together->addWidget(quit,0,Qt::AlignCenter);

    this->setLayout(piece_together);

    // **************** Everything is now pieced together ******************************

    // **************** We now draw the user box and the angry jellies **************

    // Set user box position to be in the middle of the larger square
    x_player_jelly = 155;
    y_player_jelly = 155;
    // Number of colored jellies
    number_jellies = 4;
    x_jellies = new double[number_jellies];
    y_jellies = new double[number_jellies];
    width_jellies = new double[number_jellies] ;
    height_jellies = new double[number_jellies];
    // Set first jelly size and starting positions
    x_jellies[0] = 220.0;
    y_jellies[0] = 280.0;
    width_jellies[0] = 60.0;
    height_jellies[0] = 50.0;
    // Set second jelly size and starting positions
    x_jellies[1] = 250.0;
    y_jellies[1] = 10.0;
    width_jellies[1] = 100.0;
    height_jellies[1] = 40.0;
    // Set third jelly size and starting positions
    x_jellies[2] = 20.0;
    y_jellies[2] = 20.0;
    width_jellies[2] = 30.0;
    height_jellies[2] = 60.0;
    // Set fourth jelly size and starting positions
    x_jellies[3] = 20.0;
    y_jellies[3] = 270.0;
    width_jellies[3] = 50.0;
    height_jellies[3] = 60.0;
    // set the moving directions of the jellies
    dirx_jellies = new double[4];
    diry_jellies = new double[4];
    // set the x moving directions for the four jellies
    dirx_jellies[0] = 1;
    dirx_jellies[1] = 1;
    dirx_jellies[2] = 1;
    dirx_jellies[3] = 1;
    // set the y moving directions for the four jellies
    diry_jellies[0] = 1;
    diry_jellies[1] = 1;
    diry_jellies[2] = 1;
    diry_jellies[3] = 1;
    // set images

 // **************** CHANGE FILE PATH OF THE IMAGES HERE **************/
//    QString fileName(":/images/black_blank.jpg");
    // set the player's jelly image
    QString fileName(":/images/black_blank.png");
    player_jelly_image = new QPixmap(fileName);
    // set the images for the monsters
    jelly_image_0 = new QPixmap(":/images/yellow_blank.png");
    jelly_image_1 = new QPixmap(":/images/green_blank.png");
    jelly_image_2 = new QPixmap(":/images/red_blank.png");
    jelly_image_3 = new QPixmap(":/images/blue_blank.png");
    // set background images
    large_square_border = new QPixmap(":/images/jelly_background.jpg");
    large_square = new QPixmap(":/images/border.png");
    larger_square_border = new QPixmap(":/images/border.png");
    /*** create the alert box to be displayed when the game is over ***/
    GameOver = new QDialog(this);
    QVBoxLayout *gameover_layout = new QVBoxLayout(GameOver);
    GameOver_text = new QLabel;
    GameOver_text->setStyleSheet("QLabel{ color: white; font: 20px Odin Rounded, sans-serif; }");
    GameOver_pushbutton = new QPushButton("Ok");
    GameOver_pushbutton->setStyleSheet("QPushButton{ background-color: white; color: blue; font: 20px Odin Rounded, sans-serif; }");
    GameOver_pushbutton->setFixedSize(50,25);

    gameover_layout->addWidget(GameOver_text,0,Qt::AlignCenter);
    gameover_layout->addWidget(GameOver_pushbutton, 0,Qt::AlignCenter);

    /*** change image path here ***/
    // set image with the instructions
    GameOver->setStyleSheet("QDialog{ border-image: url(:/images/jellies.jpg);}");

    /*** prepare game settings and slots ***/

    // set score and seconds to 0, since player has not started to play
    seconds = 0;
    score = "";
    // connect the _game_over() signal of the GameBoard class to the game_over() function from the MainWindow class
    connect(this, SIGNAL(_game_over()), parent, SLOT(game_over()));
    // connect the _unlock_medium() signal of the GameBoard class to the unlock_medium() function from the MainWindow class
    connect(this, SIGNAL(_unlock_medium()), parent, SLOT(unlock_medium()));
    // connect the _unlock_hard() signal of the GameBoard class to the unlock_hard() function from the MainWindow class
    connect(this, SIGNAL(_unlock_hard()), parent, SLOT(unlock_hard()));
    // connect easy, medium and hard game signals of the GameBoard class to the easy, medium and hard game signals from the MainWindow class
    // this will enable going from a level to the next
    connect(this, SIGNAL(_medium_game()), parent, SLOT(on_Medium_clicked()));
    connect(this, SIGNAL(_hard_game()), parent, SLOT(on_Hard_clicked()));
    // game has not started yet
    game_on = 0;
    // prepare to move jellies
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_jellies()));
    // prepare chronometer
    time = new QElapsedTimer();
}

/**
* @brief This function is the destructor event for the GameBoard class.
*/
GameBoard::~GameBoard()
{
    delete [] x_jellies;
    delete [] y_jellies;
    delete [] width_jellies;
    delete [] height_jellies;
    delete [] dirx_jellies;
    delete [] diry_jellies;
    delete timer;
    delete ui;
}

/**
* @brief This function is an event handler function. It is the paintEvent.
* It paints the jellies, the player's jelly, the game board square,
* based on their width, their height, and coordinates.
* @param event event parameter
*/
void GameBoard::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    // Set the window so that we can work on the board
    // so that we can start putting the squares and jellies at (0,0)
    painter.setWindow(-99,-112, 550, 550);
    // Draw the larger square, by building a large frame
    painter.drawPixmap(-50,-50,450, 450, *large_square_border);
    // Draw the extreme limit of jellies territory
    painter.drawPixmap(-50,-50,450, 450, *larger_square_border);
    // Draw the larger square, put a border on it, the actual larger square
    painter.drawPixmap(-4,-4,358, 358, *large_square);
    // Draw the four colored jellies
    painter.drawPixmap(x_jellies[0], y_jellies[0], width_jellies[0], height_jellies[0], *jelly_image_0);
    painter.drawPixmap(x_jellies[1], y_jellies[1], width_jellies[1], height_jellies[1], *jelly_image_1);
    painter.drawPixmap(x_jellies[2], y_jellies[2], width_jellies[2], height_jellies[2], *jelly_image_2);
    painter.drawPixmap(x_jellies[3], y_jellies[3], width_jellies[3], height_jellies[3], *jelly_image_3);
    // Draw the player's jelly
    painter.drawPixmap(x_player_jelly, y_player_jelly, width_player_jelly, height_player_jelly, *player_jelly_image);
    return;
}

/**
* @brief This function is an event handler function. It moves the player's jelly based on the mouse of the user.
* The player's jelly can be moved to the bottom, to the top, to the left or to the right.
* @param event event parameter
*/
void GameBoard::mouseMoveEvent( QMouseEvent * event  ){
    // if the mouse if close enough to the player's jelly, the mouse can move the player's jelly
    if((game_on &&
        event->x() -99 + 50 >= x_player_jelly && event->x() -99 - 50 <= x_player_jelly+width_player_jelly &&
        event->y() -112 +50 >= y_player_jelly && event->y() -112 - 50 <= y_player_jelly+height_player_jelly))
    {
        x_player_jelly = event->x() -99 - (width_player_jelly/2);
        y_player_jelly = event->y() -112 - (height_player_jelly/2) ;
    }

    repaint();
}

/**
* @brief This function is an event handler function. It shows the events, that just happened, by setting the focus.
* @param event event parameter
*/
void GameBoard::showEvent(QShowEvent *e) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}

/**
* @brief This function is an event handler function. It launches the game. When the user clicks on the game board, it starts the game by calling
* the start_game() function
* @param event event parameter
*/
void GameBoard::mousePressEvent ( QMouseEvent * ){
    if(!game_on){
        start_game();
    }
   return;
}

/**
 * @brief This function starts the game. It has no parameter or return type. It just launches the timer to start moving the jellies.
*/
void GameBoard::start_game(){
    // turn the game on
    game_on = 1;
    // start the timer to start making the jellies move based on the level chosen
    timer->start(jellies_speed);
    //start chronometer
    time->start();

    // set the images to be the same but with the faces of the players, because game is starting
    player_jelly_image->load(":/images/black.png");
    jelly_image_0->load(":/images/yellow.png");
    jelly_image_1->load(":/images/green.png");
    jelly_image_2->load(":/images/red.png");
    jelly_image_3->load(":/images/blue.png");
}

/**
* @brief This function is an event handler function. It moves one jelly given its id, and x and y shifts.
* @param jelly_number id of the jelly
* @param x_step x shift of the jelly
* @param y_step y shift of the jelly
*/
void GameBoard::move_jelly(size_t jelly_number, int x_step, int y_step){
    // modify the direction of the jelly, if it has reached on board of the large game board square
    if(x_jellies[jelly_number] >= 400 - width_jellies[jelly_number] || x_jellies[jelly_number] <= -50)
        dirx_jellies[jelly_number] = -1 * dirx_jellies[jelly_number];
    if(y_jellies[jelly_number] >= 400 - height_jellies[jelly_number] || y_jellies[jelly_number] <= -50)
        diry_jellies[jelly_number] = -1 * diry_jellies[jelly_number];
    // compute the new x and y coordinates
    x_jellies[jelly_number] = x_jellies[jelly_number] + x_step*dirx_jellies[jelly_number];
    y_jellies[jelly_number] = y_jellies[jelly_number] + y_step*diry_jellies[jelly_number];

    repaint();
    QCoreApplication::processEvents();
}

/**
* @brief This function is a general call to move all the jellies.
* The function calls the move_jelly() function for the four colored jellies.
* The function also checks if none of the jellies has hit the player's jelly, or that the player's jelly has not hit any border of the game board square.
* Otherwise, the game is over.
*/
void GameBoard::move_jellies(){
    move_jelly(0,-9,14);
    move_jelly(1,-11,-22);
    move_jelly(2,13,-15);
    move_jelly(3,15,12);

    // update the chronometer in the top bar, with the number of seconds played
    time_value->setText(QString::number(time->elapsed()/1000));

    // check that jellies do not run into the player's jelly, otherwise game is over
    // or that the player's jelly is not hitting any border
    if(hit_borders() || hit_jelly())
    {
        end_the_game();
    }
}

/**
* @brief This function is an boolean function. The function checks if the player's jelly does not hit any jelly.
* The function checks for each of the four colored jellies.
* If the player's jelly hits any jelly, it returns true. Otherwise false.
*/
bool GameBoard::hit_jelly(){
    // check the position of all 4 jellies compared to the player's jelly coordinates
    for(size_t i = 0; i < 4; i++){
        // if the player's jelly hit a jelly, return true
        if (x_player_jelly+width_player_jelly >= x_jellies[i] && x_player_jelly+width_player_jelly <= x_jellies[i]+width_jellies[i]+width_player_jelly &&
                y_jellies[i]+height_jellies[i] >= y_player_jelly &&  y_jellies[i]+height_jellies[i] <= y_player_jelly+height_player_jelly+height_jellies[i])
               return true;
    }
    // if the player's jelly doesn't hit anything, return false
    return false;
}

/**
* @brief This function is an boolean function. The function checks if the player's jelly does not hit any border of the game board square.
* The function checks the position of the player's jelly compared to the borders of the large square.
* If the player's jelly hits any border, it returns true. Otherwise false.
*/
bool GameBoard::hit_borders(){
    if(x_player_jelly <= 0 || x_player_jelly >= 350- width_player_jelly || y_player_jelly <= 0 || y_player_jelly >= 350 - height_player_jelly)
        return true;
     return false;
}

/**
* @brief This function ends the game.
* The function turns the game off, stops the timer, that is stopping the jellies from moving
* And the function calls _game_over() signal to call the game_over() function of the Main Waindow.
*/
void GameBoard::end_the_game(){
    // turn game off
    game_on = 0;
    // stop timer
    timer->stop();

    seconds = time->elapsed() / 1000.0;
    score = QString::number(seconds);

    // set the images to be the same but without the faces of the players, because game is over
    player_jelly_image->load(":/images/black_blank.png");
    jelly_image_0->load(":/images/yellow_blank.png");
    jelly_image_1->load(":/images/green_blank.png");
    jelly_image_2->load(":/images/red_blank.png");
    jelly_image_3->load(":/images/blue_blank.png");

    // Player won, if he stayed more than 30 seconds alive, otherwise he lost.
    if(seconds > 30){ //< Player won

        // update the level that the user just won, so that the user gains access to the next level

        if(level == 1){//< if level was 1, the player is sent to level 2

            // connect the clicked() signal of the message box to the close() slot from the dialog box
            connect(GameOver_pushbutton, SIGNAL(clicked(bool)), GameOver, SLOT(close()));
            // connect the rejected() signal of the message box to the _medium_game() function from the GameBoard class
            // this way the user has no possibiliy to avoid the alert box
            connect(GameOver, SIGNAL(rejected()), this, SIGNAL(_medium_game()));
            // set message box's text
            GameOver_text->setText("<h1 >You won!"
                              "<br/><br/>You survived " +score + " seconds."
                              "<br/><br/>Let's go for level 2.</h1>");
            // level 2 is unlocked
            _unlock_medium();

        }

        if(level == 2){//< if level was 2, the player is sent to level 3

            // connect the clicked() signal of the message box to the close() slot from the dialog box
            connect(GameOver_pushbutton, SIGNAL(clicked(bool)), GameOver, SLOT(close()));
            // connect the rejected() signal of the message box to the _hard_game() function from the GameBoard class
            // this way the user has no possibiliy to avoid the alert box
            connect(GameOver, SIGNAL(rejected()), this, SIGNAL(_hard_game()));
            // set message box's text
            GameOver_text->setText("<h1>You won!"
                              "<br/><br/>You survived " +score + " seconds."
                              "<br/><br/>Let's go for level 3.</h1>");
            // level 3 is unlocked;
            _unlock_hard();

        }

        if(level == 3){//< if level was 3, the player just won the whole game

            // connect the clicked() signal of the message box to the close() slot from the dialog box
            connect(GameOver_pushbutton, SIGNAL(clicked(bool)), GameOver, SLOT(close()));
            // connect the rejected() signal of the message box to the game_over() function from the GameBoard class
            // this way the user has no possibiliy to avoid the alert box
            connect(GameOver, SIGNAL(rejected()), this, SIGNAL(_game_over()));
            // set message box's text
            GameOver_text->setText("<h1>YOU WON THE GAME!"
                              "<br/><br/>You survived " +score + " seconds.</h1>");

        }
    }


    else{//< Player lost

        // connect the clicked() signal of the message box to the close() slot from the dialog box
        connect(GameOver_pushbutton, SIGNAL(clicked(bool)), GameOver, SLOT(close()));
        // connect the rejected() signal of the message box to the game_over() function from the MainWindow class
        // this way the user has no possibiliy to avoid the alert box
        connect(GameOver, SIGNAL(rejected()), this, SIGNAL(_game_over()));
        // set message box's text
        GameOver_text->setText("You lost! You survived " +score + " seconds.");

    }
    // show message box
    GameOver->exec();
}
