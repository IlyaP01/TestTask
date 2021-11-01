/**
 * @file
 * @brief Figure source file
 * @authors Pavlov Ilya
 *
 * Contains Figure class definition
 */


#include "figure.h"
#include <QFile>
#include <QTextStream>

/**
 * Сheck if three points belong to the same straight line
 * @param[in] p1 the first point
 * @param[in]  p2 the second point
 * @param[in]  p3 the third point
 * @return result of checking
 */
static bool _checkIfOnLine(const Point& p1, const Point& p2, const Point& p3) {
    // floating point arithmetic error alignment
    constexpr double err = 1e-10;

    if ((p3 - p1).SqrNorm() < err * err)
        return (p3 - p2).SqrNorm() < err * err;

    if (fabs(p3.x - p1.x) < err)
        return fabs(p2.x - p1.x) < err;

    if (fabs(p3.y - p1.y) < err)
        return fabs(p2.y - p1.y) < err;

    // use the equation of a straight line through two points
    return fabs((p2.x - p1.x) / (p3.x - p1.x) - (p2.y - p1.y) / (p3.y - p1.y)) < err;
}

/**
 * Check if the coordinates of the second point are between the coordinates of the first and third points
 * @param[in]  p1 the first point
 * @param[in]  p2 the second point
 * @param[in]  p3 the third point
 * @return result of checking
 */

static inline bool _checkIfBetween(const Point& p1, const Point& p2, const Point& p3) {
    // floating point arithmetic error alignment
    constexpr double err = 1e-10;
    return (p3.x - p2.x) * (p2.x - p1.x) >= 0 - err && (p3.y - p2.y) * (p2.y - p1.y) >= 0 - err;
}

/**
 * Check if figure can be built without the second point
 * @param[in]  p1 the first point
 * @param[in]  p2 the second point
 * @param[in]  p3 the third point
 * @return result of checking
 * @see _checkIfOnLine
 * @see _checkIfBetween
 */

static bool _checkIfNeedless(const Point& p1, const Point& p2, const Point& p3) {
    return _checkIfOnLine(p1, p2, p3) && _checkIfBetween(p1, p2, p3);
}

/**
 * Add point to the end of figure
 * @param[in] line string contains point coordinates
 * @return Error enum with information about errors
 */
Figure::Error Figure::AddPoint(const QString& line) noexcept {
    if (line.count(',') != 1)
        return Error::FORMAT_ERROR;
    auto pointsStr = line.split(',', Qt::SkipEmptyParts);
    if (pointsStr.length() == 2) {
        bool ok;
        double x = pointsStr[0].toDouble(&ok);
        if (!ok)
            return Error::FORMAT_ERROR;

        double y = pointsStr[1].toDouble(&ok);
        if (!ok)
            return Error::FORMAT_ERROR;

        if (points.size() >= 2 && _checkIfNeedless(points[points.size() - 2], points.back(),{x, y})) {
            points.back() = {x, y};
        }
        else {
            try {
                points.emplace_back(x, y);
            } catch (std::bad_alloc) {
                return Error::MEMORY_ERROR;
            }
        }
    }
    else {
        return Error::FORMAT_ERROR;
    }

    return Error::NO_ERROR;
}

/**
 * Read figure points from file
 * @param[in] fileName path to file
 * @return Error enum with information about errors
 */
Figure::Error Figure::ReadFromFile(const QString& fileName) noexcept {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        points.clear();
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                auto err = AddPoint(line);
                if (err != Error::NO_ERROR) {
                    points.clear();
                    return err;
                }
            }
        }
        file.close();
    }
    else {
        return Error::OPEN_FILE_ERROR;
    }

    return Error::NO_ERROR;
}

/**
 * Save figure to file
 * @param[in] fileName path to file
 * @return Error enum with information about errors
 */
Figure::Error Figure::Save(const QString& fileName) const noexcept {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (const auto& point : points)
           out << point.x << ", " << point.y << Qt::endl;
        file.close();
    }
    else {
        return Error::OPEN_FILE_ERROR;
    }

    return Error::NO_ERROR;
}

/**
 * Get vector of figure points
 * @return vector of figure points
 */
const std::vector<Point>& Figure::GetPoints() const noexcept {
    return points;
}

/**
 * Remove all points from figure
 */
void Figure::Clear() noexcept {
    points.clear();
}
