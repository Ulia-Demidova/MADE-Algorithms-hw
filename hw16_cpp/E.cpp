#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

float EPS = 10e-9;

class Point {
public:
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
  friend class ConvexHull;
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

class ConvexHull {
  vector<Point> points;
  vector<Point> hull;
  size_t n;
  Point p0;
public:
  ConvexHull(size_t n): n(n) {
    int64_t x, y;
    for (size_t i = 0; i < n; ++i) {
      cin >> x >> y;
      points.emplace_back(x, y);
    }
    find_left_point_and_add_to_hull();
    std::sort(points.begin(), points.end(), comp);
  }

  void find_left_point_and_add_to_hull() {
    p0 = points[0];
    for (auto &p : points) {
      if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
        p0 = p;
    }
    hull.push_back(p0);
  }

  bool comp(Point first, Point second) {
    Vector first_vec(p0, first);
    Vector second_vec(p0, second);
    return first_vec.cross_product(second_vec) > 0;
  }


};


int main() {
  size_t n;
  cin >> n;
  vector<Point> points;
  vector<Point> hull;
  int64_t x, y;
  for (size_t i = 0; i < n; ++i) {
    cin >> x >> y;
    points.emplace_back(x, y);
  }

  Point p0 = points[0];
  for (auto &p : points) {
    if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
      p0 = p;
  }
  hull.push_back(p0);

  return 0;
}
