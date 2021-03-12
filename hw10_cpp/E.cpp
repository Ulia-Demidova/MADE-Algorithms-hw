#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::set;
using std::vector;

class Graph {
private:
  vector<set<size_t>> edges;
  vector<size_t> tin;
  vector<size_t> up;
  vector<bool> used;
  size_t time = 0;
  set<size_t> points;
  size_t root_child_count = 0;
  size_t root = 0;

public:
  Graph(size_t n, size_t m) : edges(n), used(n), tin(n), up(n) {
    size_t u, v;
    for (size_t i = 0; i < m; ++i) {
      cin >> u >> v;
      if (u == v)
        continue;
      --u;
      --v;
      edges[u].insert(v);
      edges[v].insert(u);
    }
  }

  void dfs(size_t vertex) {
    used[vertex] = true;
    tin[vertex] = time;
    up[vertex] = time;
    for (auto &u : edges[vertex]) {
      if (!used[u]) {
        if (vertex == root) {
          ++root_child_count;
        }
        ++time;
        dfs(u);
        up[vertex] = std::min(up[vertex], up[u]);
        if (vertex != root && up[u] >= tin[vertex]) {
          points.insert(vertex + 1);
        }
      } else if (tin[u] < tin[vertex] - 1) {
        up[vertex] = std::min(up[vertex], tin[u]);
      }
    }
  }

  void find_points(size_t n) {
    for (size_t i = 0; i < n; ++i) {
      if (!used[i]) {
        root = i;
        dfs(i);
        if (root_child_count > 1)
          points.insert(root + 1);
        root_child_count = 0;
      }
    }
    cout << points.size() << '\n';
    for (auto &v : points)
      cout << v << ' ';
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  size_t n, m;
  cin >> n >> m;

  Graph graph(n, m);
  graph.find_points(n);
  return 0;
}
