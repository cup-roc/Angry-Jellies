/**
 * @file main.cpp
 * @author Corentin Poret
 * @date May 15, 2016
 * @brief creates the angry jellies game
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
