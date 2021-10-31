/**
 * @file
 * @brief Point header file
 * @authors Pavlov Ilya
 *
 * Contains Point class definition
 */

#include "point.h"
#include <cmath>

Point::Point(double x, double y) noexcept : x(x), y(y) {};

Point Point::operator-(const Point &other) const noexcept{
    return Point(x - other.x, y - other.y);
}

double Point::SqrNorm() const noexcept{
    return x * x + y * y;
}
