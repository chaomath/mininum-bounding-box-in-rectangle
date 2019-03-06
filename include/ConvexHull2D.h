#ifndef CONVEXHULL2D_H
#define CONVEXHULL2D_H

#include <vector>
#include <iostream>
#include <stack>
#include <cmath>
#include <algorithm>
#include "./Point2D.h"
using namespace std;

// typedef struct Point2D
// {
//     double x;
//     double y;
//     Point2D()
//     {
//         this->x = 0.0;
//         this->y = 0.0;
//     }
//     Point2D(double x, double y)
//     {
//         this->x = x;
//         this->y = y;
//     }

//     friend std::ostream& operator << (std::ostream& o, const Point2D& p)
//     {
//         o << "(" << p.x << ", " << p.y << ")" << std::endl;
//         return o;
//     }

//     bool operator==(const Point2D& p) 
//     { 
//         return ((*this).x == p.x && (*this).y == p.y );
//     }

//     Point2D operator-(const Point2D& p) 
//     { 
//         return Point2D((*this).x - p.x, (*this).y - p.y);
//     }

//     Point2D operator+(const Point2D& p) 
//     { 
//         return Point2D((*this).x + p.x, (*this).y + p.y);
//     }

// }Point2D;

static Point2D _lowest_point;
bool comp(Point2D &a, Point2D &b);
// bool comp(Point2D &a, Point2D &b)
// {
    
//     double thetaA = atan2(a.y - _lowest_point.y, a.x - _lowest_point.x);
//     double thetaB = atan2(b.y - _lowest_point.y, b.x - _lowest_point.x);
//     // return (thetaA < thetaB);
//     if(thetaA > thetaB)
//     {
//         return false;
//     }
//     else if(thetaA < thetaB)
//     {
//         return true;
//     }
//     else //thetaA == thetaB
//     {
//         double distanceA2 = (a.x - _lowest_point.x) * (a.x - _lowest_point.x) + (a.y - _lowest_point.y) * (a.y - _lowest_point.y);
//         double distanceB2 = (b.x - _lowest_point.x) * (b.x - _lowest_point.x) + (b.y - _lowest_point.y) * (b.y - _lowest_point.y);
//         if(distanceA2 > distanceB2)
//         {
//             return false;
//         }
//         else if(distanceA2 < distanceB2)
//         {
//             return true;
//         }
//     }
//     return true;
// }

enum Turn { CLOCKWISE, COUNTER_CLOCKWISE, COLLINEAR };
//GrahamScan method
class ConvexHull2D 
{
    public:
        ConvexHull2D();
        ~ConvexHull2D();

        vector<Point2D> getConvexHull(double xs[], double ys[], int size);
        vector<Point2D> getConvexHull(vector<Point2D> points);

    private:
        Point2D getLowestPoint(vector<Point2D> points);
        void sortedPoints(vector<Point2D> &points);
        Turn getTurn(Point2D a, Point2D b, Point2D c); 
        double crossPruduct(Point2D a, Point2D b); //vector cross product

    private:
        int _lowest_index;

};


#endif