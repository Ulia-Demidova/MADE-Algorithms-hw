#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

float MAX_WEIGHT = 100'000;

struct Point {
  int x;
  int y;
};

float distance(const Point &p, const Point &q) {
  return std::sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

int main() {
  size_t n;
  cin >> n;
  vector<float> weight(n);
  vector<Point> points(n);

  int x, y;
  for (size_t i = 0; i < n; ++i) {
    cin >> x >> y;
    points[i] = {x, y};
  }
  for (size_t i = 0; i < n; ++i) {
    weight[i] = distance(points[0], points[i]);
  }

  float final_weight = 0;
  for (size_t i = 0; i < n; ++i) {
    size_t next;
    float min_weight = MAX_WEIGHT;
    for (size_t j = 0; j < n; ++j) {
      if (weight[j] > 0 && weight[j] < min_weight) {
        min_weight = weight[j];
        next = j;
      }
    }
    final_weight += weight[next];
    weight[next] = 0;

    for (size_t j = 0; j < n; ++j)
      weight[j] = std::min(weight[j], distance(points[next], points[j]));
  }
  cout << final_weight;
  return 0;
}
