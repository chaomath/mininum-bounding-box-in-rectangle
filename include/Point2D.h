#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>

typedef struct Point2D
{
    double x;
    double y;
    Point2D()
    {
        this->x = 0.0;
        this->y = 0.0;
    }
    Point2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    friend std::ostream& operator << (std::ostream& o, const Point2D& p)
    {
        o << "(" << p.x << ", " << p.y << ")" << std::endl;
        return o;
    }

    bool operator==(const Point2D& p) 
    { 
        return ((*this).x == p.x && (*this).y == p.y );
    }

    Point2D operator-(const Point2D& p) 
    { 
        return Point2D((*this).x - p.x, (*this).y - p.y);
    }

    Point2D operator+(const Point2D& p) 
    { 
        return Point2D((*this).x + p.x, (*this).y + p.y);
    }

}Point2D;


// typedef struct Rectangle
// {
//     Point2D point0; 
//     Point2D point1;
//     Point2D point2;
//     Point2D point3;

//     friend std::ostream& operator << (std::ostream& o, const Rectangle& rect)
//     {
//         o << endl;
//         o << rect.point0 << rect.point1 << rect.point2 << rect.point3;
//         return o;
//     }
// }Rectangle;


#endif
