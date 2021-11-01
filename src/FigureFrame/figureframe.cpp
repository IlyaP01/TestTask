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
FigureFrame::FigureFrame(const Figure* figure) : figure(figure)  {
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void FigureFrame::DrawLastPoint() {
    fullRedraw = false;
    update();
    fullRedraw = true;
}

void FigureFrame::FullRedraw() {
    fullRedraw = true;
    update();
}

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

    if (!fullRedraw) {
        if (!points.empty()) {
            painter.drawLine(points[points.size() - 2].x, points[points.size() - 2].y,
                             points.back().x, points.back().y);
        }
    }
    else {
        painter.eraseRect(rect());
        for (size_t i = 0; !points.empty() && i < points.size() - 1; ++i) {
            painter.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
    }
}
