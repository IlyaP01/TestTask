/**
 * @file
 * @brief FigureFrame source file
 * @authors Pavlov Ilya
 *
 * Contains FigureFrame class definition
 */

#include "figureframe.h"
#include <QPainter>

/**
 * FigureFrame constructor
 * @param[in] figure pointer to the figure to be drawn
 */
FigureFrame::FigureFrame(const Figure* figure) : figure(figure)  {}

/**
 * Draw figure
 * @param event event parameters (not used)
 */
void FigureFrame::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter painter(this);
    painter.translate(this->rect().bottomLeft());
    painter.scale(1.0, -1.0);
    QPen pen(Qt::blue, 2, Qt::SolidLine);
    painter.setPen(pen);

    auto points = figure->GetPoints();
    if (points.empty())
        return;
    for (size_t i = 0; i < points.size() - 1; ++i) {
        painter.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }
}
