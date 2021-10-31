/**
 * @file
 * @brief Main window header file
 * @authors Pavlov Ilya
 *
 * Contains MainWindow class declaration
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Figure/figure.h"
#include "../FigureFrame/figureframe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief MainWindow class
 *
 * Contains interface elements and methods for managing them (controller in MVC)
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Figure figure;
    FigureFrame figureFrame;
    void UpdateWidgets() noexcept;
private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_showButton_clicked();
    void on_addButton_clicked();
    void on_clearButton_clicked();
};

#endif // MAINWINDOW_H
