/**
 * @file
 * @brief Main program source file
 * @authors Pavlov Ilya
 *
 * Contains main function to start program
 */

#include "Interface/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("Test Task");
    w.show();
    return app.exec();
}
