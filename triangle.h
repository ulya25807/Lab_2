#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
    double area;
    bool isDegenerate;
};

//Geometry
Point createPoint(double x, double y);
Triangle createTriangle(Point A, Point B, Point C);
double calculateArea(Point A, Point B, Point C);
double crossProduct(Point A, Point B, Point P);
bool isOnSegment(Point A, Point B, Point P);
int checkPoint(Point P, Triangle t);

//User interaction
Point inputPoint(const char* pointName);
Triangle inputTriangle();
void printResult(Point P, int result);
void processDegenerate();
void runPointCheckLoop(Triangle t);

#endif