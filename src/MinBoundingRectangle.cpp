#include <iostream>
#include <limits>
#include "../include/ConvexHull2D.h"
#include "../include/MinBoundingRectangle.h"

MinBoundingRectangle::MinBoundingRectangle()
{
}

MinBoundingRectangle::~MinBoundingRectangle()
{
}

vector<Point2D> MinBoundingRectangle::getMinimumBoundingRectangle(double xs[], double ys[], int size)
{
  vector<Point2D> hull2d;
  ConvexHull2D convexHull2D;
  hull2d = convexHull2D.getConvexHull(xs, ys, size);

  //cout << "hull2d size = " << hull2d.size() << endl;
  for(int i = 0; i < hull2d.size(); i++)
  {
      std::cout << hull2d[i];
  }

  vector<Edge2D> edges = getEdgesFromPoints(hull2d);

  vector<double> angles;
  angles = getEdgesAngles(edges);

  //sort angle ascending
  std::sort(angles.begin(), angles.end());
  //remove duplicate
  unique(angles.begin(), angles.end());
  angles.erase(unique(angles.begin(), angles.end()), angles.end());

  // for(size_t i = 0; i < angles.size(); i++)
  // {
  //   std::cout << "sorted angle " << i << " = " << rad2deg(angles[i]) << std::endl;
  // }

  //Rotating by (-theta) R = [cost, sint; -sint, cost];
  vector<BoundingBox> bboxes;
  for(size_t i = 0; i < angles.size(); i++)
  {
    double theta = angles[i];
    vector<Point2D> points_r = rotatingPoints(hull2d, -1.0 * theta); //anti-clock wise
    BoundingBox bbox = getMinAreaRectange(points_r);
    bbox.orientation = theta;
    bboxes.push_back(bbox);
  }

  //find min area bbox
  double area_min = std::numeric_limits<double>::max();
  int index = 0;
  for(size_t i = 0; i < bboxes.size(); i++)
  {
    if(bboxes[i].area < area_min)
    {
      area_min = bboxes[i].area;
      index = i;
    }
  }

  vector<Point2D> min_bounding_box;
  min_bounding_box = rotatingPoints(bboxes[index].rectangle, bboxes[index].orientation);
  return min_bounding_box;
}


vector<Edge2D> MinBoundingRectangle::getEdgesFromPoints(vector<Point2D> points)
{
  vector<Edge2D> edges;
  for(size_t i = 0; i < points.size() - 1; i++)
  {
    Edge2D edge;
    edge.a = points[i];
    edge.b = points[i + 1];
    edges.push_back(edge);
  }
  return edges;
}

vector<double> MinBoundingRectangle::getEdgesAngles(vector<Edge2D> edges)
{
  //std::cout << "edges :" << std::endl;
  for(size_t i = 0; i < edges.size(); i++)
  {
    std::cout << edges[i];
  }

  vector<double> angles;
  for(size_t i = 0; i < edges.size(); i++)
  {
    Edge2D edge = edges[i];
    double angle = atan2(edge.b.y - edge.a.y, edge.b.x - edge.a.x);
    
    //set all angles to [0, 90)
    angle = (angle >= 0.0) ? angle : (angle += (2. * M_PI));
    angle = fmod(angle, M_PI / 2.0);
    angles.push_back(angle);

    // std::cout << "angle " << i << " = " << rad2deg(angle) << std::endl;
  }
  return angles;
}

Point2D MinBoundingRectangle::rotatingPoint(Point2D p, double theta)
{
  Point2D q;
  q.x = cos(theta) * p.x - sin(theta) * p.y;
  q.y = sin(theta) * p.x + cos(theta) * p.y;
  return q;
}

vector<Point2D> MinBoundingRectangle::rotatingPoints(vector<Point2D> points, double theta)
{
  vector<Point2D> points_r;
  for(size_t i = 0; i < points.size(); i++)
  {
    points_r.push_back(rotatingPoint(points[i], theta));
  }
  return points_r;
}

BoundingBox MinBoundingRectangle::getMinAreaRectange(vector<Point2D> points)
{
  BoundingBox bbox;
  if(points.size() < 1)
  {
    std::cout << "getMinAreaRectange----points < 1" << endl;
    return bbox;
  }

  double min_x = points[0].x;
  double max_x = points[0].x;
  double min_y = points[0].y;
  double max_y = points[0].y;
  for(size_t i = 1; i < points.size(); i++)
  {
    if(points[i].x < min_x) min_x = points[i].x;
    if(points[i].x > max_x) max_x = points[i].x;
    if(points[i].y < min_y) min_y = points[i].y;
    if(points[i].y > max_y) max_y = points[i].y;
  }

  bbox.rectangle.push_back(Point2D(min_x, min_y));
  bbox.rectangle.push_back(Point2D(max_x, min_y));
  bbox.rectangle.push_back(Point2D(max_x, max_y));
  bbox.rectangle.push_back(Point2D(min_x, max_y));

  bbox.area = (max_x - min_x) * (max_y - min_y);

  return bbox;
}
