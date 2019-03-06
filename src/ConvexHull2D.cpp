#include "../include/ConvexHull2D.h"

bool comp(Point2D &a, Point2D &b)
{
    
    double thetaA = atan2(a.y - _lowest_point.y, a.x - _lowest_point.x);
    double thetaB = atan2(b.y - _lowest_point.y, b.x - _lowest_point.x);
    // return (thetaA < thetaB);
    if(thetaA > thetaB)
    {
        return false;
    }
    else if(thetaA < thetaB)
    {
        return true;
    }
    else //thetaA == thetaB
    {
        double distanceA2 = (a.x - _lowest_point.x) * (a.x - _lowest_point.x) + (a.y - _lowest_point.y) * (a.y - _lowest_point.y);
        double distanceB2 = (b.x - _lowest_point.x) * (b.x - _lowest_point.x) + (b.y - _lowest_point.y) * (b.y - _lowest_point.y);
        if(distanceA2 > distanceB2)
        {
            return false;
        }
        else if(distanceA2 < distanceB2)
        {
            return true;
        }
    }
    return true;
}


ConvexHull2D::ConvexHull2D() 
{
}

ConvexHull2D::~ConvexHull2D()
{
}

vector<Point2D> ConvexHull2D::getConvexHull(double xs[], double ys[], int size) 
{
    vector<Point2D> points;
    for(int i = 0; i < size; i++)
    {
        points.push_back(Point2D(xs[i], ys[i]));
        cout << "raw point [" << i << "] = "<< points[i];
    }
    return getConvexHull(points);
}

vector<Point2D> ConvexHull2D::getConvexHull(vector<Point2D> points)
{
    vector<Point2D> convex_hull;

    //step1 : sort points and remove duplication 
    sortedPoints(points);

    if(points.size() < 3)
    {
        std::cout << "sorted points less than 3" << std::endl;
        return convex_hull;
    }

    //step2 : GrahamScan 
    stack<Point2D> stackH;
    stackH.push(points[0]);
    stackH.push(points[1]);

    for(int i = 2; i < points.size(); i++)
    {
        Point2D tail = points[i];
        Point2D middle = stackH.top();
        stackH.pop();
        Point2D head = stackH.top();

        switch (getTurn(head, middle, tail))
        {
            case COUNTER_CLOCKWISE:
                stackH.push(middle);
                stackH.push(tail);
                break;
            case CLOCKWISE:
                i--;
                break;
            case COLLINEAR:
                stackH.push(tail);
                break;
            default:
                break;
        }
    }

    //step3 : for output
    stackH.push(points[0]); // contact head and tail

    while(!stackH.empty())
    {
        convex_hull.push_back(stackH.top());
        stackH.pop();
    }

    return convex_hull;
}

Point2D ConvexHull2D::getLowestPoint(vector<Point2D> points)
{
    Point2D lowest = points[0];
    for(int i = 1; i < points.size(); i++)
    {
        Point2D temp = points[i];
        if((temp.y < lowest.y) || (temp.y == lowest.y && temp.x < lowest.x))
        {
            lowest = temp;
        }
    }
    return lowest;
}

void ConvexHull2D::sortedPoints(vector<Point2D> &points)
{
    _lowest_point = getLowestPoint(points);
    sort(points.begin(), points.end(), comp);

    //remove duplicate
    unique(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
}

//vector cross product a(x1, y1), b(x2, y2)
//axb = (x1*y2 - x2*y1)
double ConvexHull2D::crossPruduct(Point2D a, Point2D b)
{
    return (a.x * b.y - b.x * a.y);
}

Turn ConvexHull2D::getTurn(Point2D a, Point2D b, Point2D c)
{
    double cross = crossPruduct(b - a, c - b);
    if(cross > 0)
    {
        return COUNTER_CLOCKWISE;
    }
    else if(cross < 0)
    {
        return CLOCKWISE;
    }
    else
    {
       return COLLINEAR;
    }
}

