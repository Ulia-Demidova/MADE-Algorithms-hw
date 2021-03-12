#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

float EPS = 10e-9;

class Point {
private:
  int64_t x, y;

public:
  Point() {
    int64_t x_, y_;
    cin >> x_ >> y_;
    x = x_;
    y = y_;
  }
  Point(int x, int y) : x(x), y(y) {}
  friend class Vector;
};

class Vector {
private:
  int64_t x, y;

public:
  Vector(Point a) {
    x = a.x;
    y = a.y;
  }

  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }

  int64_t dot_product(const Vector &other) { return x * other.x + y * other.y; }

  int64_t cross_product(const Vector &other) {
    return x * other.y - y * other.x;
  }

  float angle(const Vector &other) {
    return std::atan2(cross_product(other), dot_product(other));
  }
};

class Polygon {
private:
  vector<Point> points;
  size_t n;

public:
  Polygon(size_t n) : n(n) {
    for (size_t i = 0; i < n; ++i) {
      int64_t x, y;
      cin >> x >> y;
      points.emplace_back(x, y);
    }
  }

  float square() {
    float result = 0;
    for (size_t i = 0; i < n; ++i) {
      Vector first_vec(points[i]);
      Vector second_vec(points[(i + 1) % n]);
      result += first_vec.cross_product(second_vec);
    }
    return abs(result) / 2.;
  }
};

int main() {
  size_t n;
  cin >> n;
  Polygon polygon(n);
  cout << polygon.square();
  return 0;
}
