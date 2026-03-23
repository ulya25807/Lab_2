#include "triangle.h"
#include <iostream>

using namespace std;

int main() {
    Triangle t = inputTriangle();
    if (t.isDegenerate) {
        processDegenerate();
        return 1;
    } else {
        cout << "\nTriangle created successfully. It is not degenerate." << endl;
        cout << "Area = " << t.area << endl << endl;
    }

    runPointCheckLoop(t);
    return 0;
}