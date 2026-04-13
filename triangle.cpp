#include "triangle.h"
#include <iostream>
#include <cmath>

const double EPSILON = 1e-9;

double distance(const Point& A, const Point& B) {
    return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}

double calculateArea(const Point& A, const Point& B, const Point& C) {
    double a = distance(A, B);
    double b = distance(B, C);
    double c = distance(C, A);
    double s = (a + b + c) / 2.0;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

double crossProduct(const Point& A, const Point& B, const Point& P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

bool isOnSegment(const Point& A, const Point& B, const Point& P) {
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

int checkPointHeron(const Point& P, const Triangle& t) {
    double sABC = calculateArea(t.A, t.B, t.C);
    double s1 = calculateArea(t. A, t.B, P);
    double s2 = calculateArea(t.A, t.C, P);
    double s3 = calculateArea(t.B, t.C, P);
    double sum = s1 + s2 + s3;

    if (fabs(sABC - sum) > 1e-7) {
        return 0;
    }

    if (s1 < 1e-7 || s2 < 1e-7 || s3 < 1e-7) {
        return 2;
    }
    return 1;
}

int checkPointVector(const Point& P, const Triangle& t) {
    bool onAB = isOnSegment(t.A, t.B, P);
    bool onBC = isOnSegment(t.B, t.C, P);
    bool onAC = isOnSegment(t.C, t.A, P);

    if (onAB || onBC || onAC) {
        return 2;
    }

    if (calculateArea(t.A, t.B, t.C) < EPSILON) {
        return 0;
    }

    double v1 = crossProduct(t.A, t.B, P);
    double v2 = crossProduct(t.B, t.C, P);
    double v3 = crossProduct(t.C, t.A, P);

    if ((fabs(v1) < EPSILON && isOnSegment(t.A, t.B, P)) ||
        (fabs(v2) < EPSILON && isOnSegment(t.B, t.C, P)) ||
        (fabs(v3) < EPSILON && isOnSegment(t.C, t.A, P))) {
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
    return Point{x, y};
}

Triangle inputTriangle() {
    std::cout << "Enter the coordinates of triangle vertices (x, y) one by one: " << std::endl;
    Point A = inputPoint("A");
    Point B = inputPoint("B");
    Point C = inputPoint("C");
    if(calculateArea(A, B, C) < EPSILON) {
        std::cout << "Triangle created succsesfully. It is degenerate.\n" << "Area: " << calculateArea(A, B, C) << std::endl;
    } else {
        std::cout << "Triangle created succsesfully. It is not degenerate.\n" << "Area: " << calculateArea(A, B, C) << std::endl;
    }
    return Triangle{A, B, C};
}

void printResult(const Point& P, const Triangle& t, int result) {
    std::cout << "Result for point (" << P.x << ", " << P.y << ")" << std::endl;
    std::cout << "Vector method: ";
    if (result == 0) {
        std::cout << "outside the triangle." << std::endl;
    } else if (result == 1) {
        std::cout << "inside the triangle." << std::endl;
    } else {
        std::cout << "on the edge of triangle." << std::endl;
    }

    int resHeron = checkPointHeron(P, t);
    std::cout << "Heron's formula method: ";
    if (resHeron == 0) {
        std::cout << "outside the triangle." << std::endl;
    } else if (resHeron == 1) {
        std::cout << "inside the triangle." << std::endl;
    } else {
        std::cout << "on the edge of triangle." << std::endl;
    }
}

void runPointCheckLoop(const Triangle& t) {
    char choice = 'y';
     while (choice == 'y' || choice == 'Y') {
        Point P = inputPoint("P");
        printResult(P, t, checkPointVector(P, t));
        
        std::cout << "\nWanna continue? (y/n): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
    }
    std::cout << "Exiting... Bye!" << std::endl;
}