#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using namespace std;

class Point {

public:
    double x, y;

    Point() {}
    Point(double current_x, double current_y) : x(current_x), y(current_y) {}

    Point operator+(Point p2) {
        return Point(x + p2.x, y + p2.y);
    }

    Point operator-(Point p2) {
        return Point(x - p2.x, y - p2.y);
    }

    bool operator==(Point p2) {
        return x == p2.x && y == p2.y;
    }

    bool operator!=(Point p2) {
        return x != p2.x || y != p2.y;
    }

    Point operator-=(Point p2) {
        return Point(x -= p2.x, y -= p2.y);
    }

    Point operator+=(Point p2) {
        return Point(x += p2.x, y += p2.y);
    }
};

typedef Point Vector;

double crossProduct(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

double dotProduct(Vector v1, Vector v2) {
    cout << v1.x << " " << v2.x << endl;
    return v1.x * v2.x + v1.y * v2.y;
}

bool isCollinear(Point p1,Point p2, Point p3) {
    return crossProduct(p2 - p1, p3 - p1) == 0.0;
}

int Relate(Point p1, Point p2, Point p3) {

    if(isCollinear(p1, p2, p3)) return 0;

    double result = crossProduct(p2 - p1, p3 - p1);
    if(result > 0.0) return 1;
    else return -1;

}

int Intersection(Point p1, Point p2, Point p3, Point p4, Point& p0) {
    Vector v1 = p2 - p1;
    Vector v2 = p4 - p3;

    if (v1.x - v2.x == 0.0 && v1.y - v2.y == 0.0) return 2;
    cout << "current dot prod: " << dotProduct(v1, v2) << endl;
    if (dotProduct(v1, v2) == 1) return 1;
    
    /*y = mx + b
    double placeHolder = crossProduct(p3 - p1, p2 - p1)/crossProduct(p4- p3, p2 - p1);
    p0.x = p3.x + v2.x * placeHolder;
    p0.y = p3.y + v2.y * placeHolder;
    */
    
    double m1 = v1.y / v1.x;
    // y = mx + b
    // intercept b = y - mx
    double c1 = v1.y - m1 * p2.x; 
 
 
    double m2 = v2.y / v1.x;
    double c2 = p4.y - m2 * p4.x; 
    
    double intersectionX = abs(c2 - c1)/(m1 - m2);
    double intersectionY = m1 * intersectionX + c1;
    p0.x = intersectionX;
    p0.y = intersectionY;
    return 3;
}

int main() {

    Point p0 = Point(0.0,0.0);
    //build some points
    Point A = Point(1.0,0.0);
    Point B = Point(2.0,1.0);
    Point C = Point(5.0,1.0);
    Point D = Point(5.0,3.0);
    Point E = Point(2.0,4.0);
    Point F = Point(0.0,5.0);
    Point G = Point(4.0, 2.0);
    //build some lines
    Vector Q = B - A;
    Vector R = D - E;
    Vector S = F - E;

    cout << "----Testing RELATE----" << endl;
    cout << Relate(A, B, A) << endl;
    cout << Relate(D, E, F) << endl;

    cout << "----Testing Intersection----" << endl;
    cout << Intersection(A, B, A, G, p0) << " (" << p0.x << ", " << p0.y << ")" << endl;

    cout << Intersection(A, B, E, F, p0) << " (" << p0.x << ", " << p0.y << ")" << endl;

    return 0;
}
