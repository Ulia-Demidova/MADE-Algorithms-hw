#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int MAX_D = 10'000'000;
int MIN_D = INT_MIN;
int IS_NOT_EDGE = 100'000;

int main() {
  size_t n;
  cin >> n;
  vector<vector<int>> distance(n, vector<int>(n));
  vector<vector<size_t>> next(n, vector<size_t>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      int weight;
      cin >> weight;
      if (weight == IS_NOT_EDGE)
        weight = MAX_D;
      distance[i][j] = weight;
      next[i][j] = j;
    }
  }

  for (size_t k = 0; k < n; ++k) {
    for (size_t u = 0; u < n; ++u) {
      for (size_t v = 0; v < n; ++v) {
        if (distance[u][v] > distance[u][k] + distance[k][v]) {
          distance[u][v] = std::max(MIN_D, distance[u][k] + distance[k][v]);
          next[u][v] = next[u][k];
        }
      }
    }
  }

  vector<size_t> cycle;

  for (size_t v = 0; v < n; ++v) {
    if (distance[v][v] < 0) {
      cout << "YES" << '\n';
      cycle.push_back(v);
      size_t cur = next[v][v];
      while (cur != v) {
        cycle.push_back(cur);
        cur = next[cur][v];
        if (cycle.size() > n) {
          cycle.clear();
          v = cur;
          cycle.push_back(cur);
          cur = next[cur][v];
        }
      }
      cout << cycle.size() << '\n';
      for (auto &vertex : cycle)
        cout << vertex + 1 << ' ';
      break;
    }
  }
  if (cycle.empty())
    cout << "NO";

  return 0;
}
