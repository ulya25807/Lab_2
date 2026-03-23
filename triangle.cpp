#include "triangle.h"
#include <iostream>
#include <cmath>

const double EPSILON = 1e-9;

Point createPoint(double x, double y) {
    return Point{x, y};
}

double calculateArea(Point A, Point B, Point C) {
    return 0.5 * fabs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)));
}

Triangle createTriangle(Point A, Point B, Point C) {
    Triangle t;
    t.A = A;
    t.B = B;
    t.C = C;
    t.area = calculateArea(A, B, C);

    if (t.area < EPSILON) {
        t.isDegenerate = true;  
    } else {
        t.isDegenerate = false;
    }

    return t;
}

double crossProduct(Point A, Point B, Point P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

bool isOnSegment(Point A, Point B, Point P) {
    double cp = crossProduct(A, B, P);
    if (fabs(cp) > EPSILON) {
        return false;
    }

    double min_x = fmin(A.x, B.x) - EPSILON;
    double max_x = fmax(A.x, B.x) + EPSILON;
    double min_y = fmin(A.y, B.y) - EPSILON;
    double max_y = fmax(A.y, B.y) + EPSILON;

    if ((P.x >= min_x) && (P.x <= max_x) && (P.y >= min_y) && (P.y <= max_y)) {
        return true;
    } else {
        return false;
    }
}

int checkPoint(Point P, Triangle t) {
    if (t.isDegenerate) {
        processDegenerate();
        return -1;
    }

    double v1 = crossProduct(t.A, t.B, P);
    double v2 = crossProduct(t.B, t.C, P);
    double v3 = crossProduct(t.C, t.A, P);

    if ((fabs(v1) < EPSILON && isOnSegment(t.A, t.B, P)) || (fabs(v2) < EPSILON && isOnSegment(t.B, t.C, P)) || (fabs(v3) < EPSILON && isOnSegment(t.C, t.A, P))) {
        return 2;
    }

    bool has_pos = (v1 > EPSILON) || (v2 > EPSILON) || (v3 > EPSILON);
    bool has_neg = (v1 < -EPSILON) || (v2 < -EPSILON) || (v3 < -EPSILON);

    if (has_pos && has_neg) {
        return 0;
    }
    
    return 1;
}

Point inputPoint(const char* pointName) {
    std::cout << "Enter the coordinates of point " << pointName <<  " (x, y): ";
    double x, y;
    std::cin >> x >> y;
    return createPoint(x, y);
}

Triangle inputTriangle() {
    std::cout << "Enter the coordinates of triangle vertices (x, y) one by one: " << std::endl;
    Point A = inputPoint("A");
    Point B = inputPoint("B");
    Point C = inputPoint("C");
    return createTriangle(A, B, C);
}

void printResult(Point P, int result) {
    std::cout << "Point (" << P.x << ", " << P.y << ") is ";
    switch (result) {
        case 0:
            std::cout << "outside the triangle." << std::endl;
            break;
        case 1:
            std::cout << "inside the triangle." << std::endl;
            break;
        case 2:
            std::cout << "on the edge of triangle." << std::endl;
            break;
        default:
            std::cout << "unknown (check logic)." << std::endl;
            break;
    }
}
    
void processDegenerate() {
    std::cout << "This triangle is degenerate. Further calculation is not possible." << std::endl;
}

void runPointCheckLoop(Triangle t) {
    char choice = 'y';
     while (choice == 'y' || choice == 'Y') {
        Point P = inputPoint("P");
        printResult(P, checkPoint(P, t));
        
        std::cout << "\nWanna continue? (y/n): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
    }
    std::cout << "Exiting... Bye!" << std::endl;
}