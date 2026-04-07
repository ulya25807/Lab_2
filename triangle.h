#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
};

//Geometry
double calculateArea(const Point& A, const Point& B, const Point& C);
double crossProduct(const Point& A, const Point& B, const Point& P);
bool isOnSegment(const Point& A, const Point& B, const Point& P);
int checkPoint(const Point& P, const Triangle& t);

//User interaction
Point inputPoint(const char* pointName);
Triangle inputTriangle();
void printResult(const Point& P, int result);
void processDegenerate(const Triangle& t);
void runPointCheckLoop(const Triangle& t);

#endif