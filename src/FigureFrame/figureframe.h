/**
 * @file
 * @brief FigureFrame header file
 * @authors Pavlov Ilya
 *
 * Contains FigureFrame class declaration
 */


#ifndef FIGUREFRAME_H
#define FIGUREFRAME_H

#include <QFrame>
#include "../Figure/figure.h"

/**
 * @brief The FigureFrame class
 *
 * Overrides QFrame to draw point-by-point figure (view in MVC)
 */
class FigureFrame : public QFrame {
public:
    /**
     * FigureFrame constructor
     * @param[in] figure pointer to the figure to be drawn
     */
    FigureFrame(const Figure* figure);
private:
    const Figure* figure;
    /**
     * Draw figure
     * @param event event parameters (not used)
     */
    void paintEvent(QPaintEvent *event) override;
};

#endif // FIGUREFRAME_H
