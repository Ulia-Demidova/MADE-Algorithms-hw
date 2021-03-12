#include <iostream>

using std::cin;
using std::cout;

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
};

bool point_on_segment(const Point &a, const Point &b, const Point &c) {
  Vector ab(a, b);
  Vector ac(a, c);
  if (ab.cross_product(ac) == 0 && ab.dot_product(ac) <= 0)
    return true;
  return false;
}

bool segments_intersection(const Point &a, const Point &b, const Point &c,
                           const Point &d) {
  Vector ab(a, b);
  Vector ac(a, c);
  Vector ad(a, d);
  Vector cd(c, d);
  Vector cb(c, b);
  Vector ca(c, a);
  if (ab.cross_product(ac) * ab.cross_product(ad) <= 0 &&
      cd.cross_product(ca) * cd.cross_product(cb) <= 0) {
    if (!ab.cross_product(ac) && !ab.cross_product(ad)) {
      if (point_on_segment(c, a, b) || point_on_segment(d, a, b) ||
          point_on_segment(a, c, d))
        return true;
      return false;
    }
    return true;
  }
  return false;
}

int main() {
  Point a, b, c, d;
  if (segments_intersection(a, b, c, d))
    cout << "YES";
  else
    cout << "NO";
  return 0;
}
