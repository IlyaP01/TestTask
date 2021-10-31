/**
 * @file
 * @brief Figure header file
 * @authors Pavlov Ilya
 *
 * Contains Figure class declaration
 */

#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include <QString>
#include <limits>
#include "Point/point.h"

/**
 * @brief The Figure class
 *
 * Class of point-by-point figure (model in MVC)
 */
class Figure {
private:
    std::vector<Point> points;
public:
    /**
     * @brief The Error enum
     *
     * Contains types of possible errors in figure's methods
     */
    enum class Error {
        NO_ERROR,         ///< All right, no errors
        FORMAT_ERROR,     ///< Wrong format of point
        OPEN_FILE_ERROR,  ///< Could not open file
        MEMORY_ERROR,     ///< Could not allocate memory
    };

    /**
     * Default constructor
     */
    Figure() = default;

    /**
     * Read figure points from file
     * @param[in] fileName path to file
     * @return Error enum with information about errors
     */
    Error ReadFromFile(const QString& fileName) noexcept;

    /**
     * Save figure to file
     * @param[in] fileName path to file
     * @return Error enum with information about errors
     */
    Error Save(const QString& fileName) const noexcept;

    /**
     * Add point to the end of figure
     * @param[in] line string contains point coordinates
     * @return Error enum with information about errors
     */
    Error AddPoint(const QString& line) noexcept;

    /**
     * Get vector of figure points
     * @return vector of figure points
     */
    const std::vector<Point>& GetPoints() const noexcept;

    /**
     * Remove all points from figure
     */
    void Clear() noexcept;
};

#endif // FIGURE_H
