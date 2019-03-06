#include <iostream>
#include "../include/MinBoundingRectangle.h"

int main()
{
    double xs[] = {200, 100, -400, -300, 50, -50, 100};
    double ys[] = {200, -100, 0, -150, 0, 25, -100};
    int size = sizeof(xs) / sizeof(sizeof(xs[0]));
    std::cout << "raw points-----------size =" << size << endl;

    std::vector<Point2D> min_bounding_box;

    MinBoundingRectangle minBoundingRectangle;
    min_bounding_box = minBoundingRectangle.getMinimumBoundingRectangle(xs, ys, size);

    cout << "min_bounding_box size = " << min_bounding_box.size() << endl;
    for(int i = 0; i < min_bounding_box.size(); i++)
    {
        std::cout << min_bounding_box[i];
    }
}
