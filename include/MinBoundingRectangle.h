#ifndef MINBOUNDINGRECTANGLE_H
#define MINBOUNDINGRECTANGLE_H

#include <vector>
#include <list>
#include <iostream>
#include "./Point2D.h"

using namespace std;

#define M_PI 3.14159265358979323846
#define rad2deg(x) ((x)*180./M_PI)  //弧度转角度 
#define deg2rad(x) ((x)*M_PI/180.)  //角度转弧度

typedef struct Edge2D
{
    Point2D a;
    Point2D b;

    Edge2D()
    {
        this->a = Point2D(0.0, 0.0);
        this->b = Point2D(0.0, 0.0);
    }

    friend std::ostream& operator << (std::ostream& o, const Edge2D& e)
    {
        o <<"[ ("<<e.a.x<<", "<<e.a.y<<")"<<"--->"<<"("<<e.b.x<<", "<<e.b.y<<") ]"<<std::endl;
        return o;
    }
}Edge2D;

typedef struct BoundingBox
{
    vector<Point2D> rectangle; //left_down, right_down, right_up, left_up
    double area;
    double orientation;
}BoundingBox;

class MinBoundingRectangle 
{
    public:
        MinBoundingRectangle();
        ~MinBoundingRectangle();

        vector<Point2D> getMinimumBoundingRectangle(double xs[], double ys[], int size);
        vector<Edge2D> getEdgesFromPoints(vector<Point2D> points);
        vector<double> getEdgesAngles(vector<Edge2D> edges);

        Point2D rotatingPoint(Point2D p, double theta);
        vector<Point2D> rotatingPoints(vector<Point2D> points, double theta);
        BoundingBox getMinAreaRectange(vector<Point2D> points);
};

#endif