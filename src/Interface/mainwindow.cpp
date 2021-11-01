/**
 * @file
 * @brief Main window source file
 * @authors Pavlov Ilya
 *
 * Contains MainWindow class definition
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../FigureFrame/figureframe.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), figureFrame(&figure) {
    ui->setupUi(this);
    figureFrame.FullRedraw();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::UpdateWidgets() noexcept {
    auto points = figure.GetPoints();

    QString strNumOfPoints;
    strNumOfPoints.setNum(points.size());
    ui->numOfPointsBrowser->setText(strNumOfPoints);

    QString strPoints;
    for (size_t i = 0; !points.empty() && i < points.size() - 1; ++i) {
        strPoints += QString("(%1, %2), ").arg(points[i].x).arg(points[i].y);
    }
    strPoints += (QString("(%1, %2)").arg(points.back().x).arg(points.back().y));
    ui->pointsBrowser->setText(strPoints);
}

static void _handleError(Figure::Error error) {
    QString errorMsg;
    switch (error) {
        case Figure::Error::NO_ERROR:
            return;
        case Figure::Error::FORMAT_ERROR:
            errorMsg = "Wrong format! Correct format: x, y";
            break;
        case Figure::Error::MEMORY_ERROR:
            errorMsg = "Memory error";
            break;
        case Figure::Error::OPEN_FILE_ERROR:
            errorMsg = "Could not open file";
            break;
        default:
            errorMsg = "Unknown error";
            break;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(errorMsg);
    msgBox.exec();
}


void MainWindow::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text files (*.txt)");
    if (fileName.isEmpty())
        return;
    auto err = figure.ReadFromFile(fileName);
    if (err == Figure::Error::NO_ERROR) {
        UpdateWidgets();
        figureFrame.FullRedraw();
    }
    else {
        ui->pointsBrowser->clear();
        ui->numOfPointsBrowser->clear();
        figureFrame.update();
        _handleError(err);
    }
}

void MainWindow::on_actionSave_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Open File", "", "Text files (*.txt)");
    if (fileName.isEmpty())
        return;
    auto err = figure.Save(fileName);
    if (err != Figure::Error::NO_ERROR)
        _handleError(err);

}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_showButton_clicked() {
    figureFrame.show();
}

void MainWindow::on_addButton_clicked() {
    bool ok;
    QString str = QInputDialog::getText(this, "Add point", "Enter x,y coordinates",
                                        QLineEdit::Normal, "", &ok);
    if (ok) {
        size_t prevSize = figure.GetPoints().size();
        auto err = figure.AddPoint(str);
        if (err == Figure::Error::NO_ERROR) {
            auto points = figure.GetPoints();
            UpdateWidgets();
            figureFrame.DrawLastPoint();
        }
        else {
            _handleError(err);
        }
    }
}

void MainWindow::on_clearButton_clicked() {
    figure.Clear();
    ui->numOfPointsBrowser->clear();
    ui->pointsBrowser->clear();
    figureFrame.FullRedraw();
}
