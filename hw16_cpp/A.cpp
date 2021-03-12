#include <iostream>

using std::cin;
using std::cout;

class Point {
private:
  int x, y;

public:
  Point() {
    int x_, y_;
    cin >> x_ >> y_;
    x = x_;
    y = y_;
  }
  Point(int x, int y) : x(x), y(y) {}
  friend class Vector;
};

class Vector {
private:
  int x, y;

public:
  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }

  int dot_product(const Vector &other) { return x * other.x + y * other.y; }

  int cross_product(const Vector &other) { return x * other.y - y * other.x; }
};

bool point_on_segment(const Point &a, const Point &b, const Point &c) {
  Vector ab(a, b);
  Vector ac(a, c);
  if (!ab.cross_product(ac) && ab.dot_product(ac) <= 0)
    return true;
  return false;
}

int main() {
  Point a, b, c;
  if (point_on_segment(a, b, c))
    cout << "YES";
  else
    cout << "NO";
  return 0;
}
