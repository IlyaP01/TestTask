/**
 * @file
 * @brief Point header file
 * @authors Pavlov Ilya
 *
 * Contains Point class declaration
 */

#ifndef POINT_H
#define POINT_H

/**
 * @brief The Point class
 */
class Point {
public:
    double x = 0;
    double y = 0;

    Point() = default;
    Point(double x, double y) noexcept;
    Point operator-(const Point& other) const noexcept;
    double SqrNorm() const noexcept;
};

#endif // POINT_H
