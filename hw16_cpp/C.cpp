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

bool point_on_segment(const Point &a, const Point &b, const Point &c) {
  Vector ab(a, b);
  Vector ac(a, c);
  if (ab.cross_product(ac) == 0 && ab.dot_product(ac) <= 0)
    return true;
  return false;
}

class Polygon {
private:
  vector<Point> points;
  int64_t n;

public:
  Polygon(int64_t n) : n(n) {
    for (size_t i = 0; i < n; ++i) {
      int64_t x, y;
      cin >> x >> y;
      points.emplace_back(x, y);
    }
  }

  bool contain_point_inside(const Point &point) {
    float sum_angle = 0;
    for (size_t i = 0; i < n; ++i) {
      if (point_on_segment(point, points[i], points[(i + 1) % n]))
        return true;
      Vector first_vec(point, points[i]);
      Vector second_vec(point, points[(i + 1) % n]);
      sum_angle += first_vec.angle(second_vec);
    }
    if (abs(sum_angle) < EPS)
      return false;
    return true;
  }
};

int main() {
  int64_t n;
  cin >> n;
  Point point;
  Polygon polygon(n);
  if (polygon.contain_point_inside(point))
    cout << "YES";
  else
    cout << "NO";
  return 0;
}
