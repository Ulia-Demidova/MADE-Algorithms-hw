#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::set;
using std::vector;

class Graph {
private:
  size_t DEFAULT_COLOR = 0;
  size_t n;
  vector<set<size_t>> edges;
  vector<size_t> color;

public:
  explicit Graph(size_t n, size_t m) : n(n), edges(n), color(n, 0) {
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

  void dfs(const size_t &vertex, const size_t &cur) {
    color[vertex] = cur;
    for (auto &u : edges[vertex]) {
      if (color[u] == DEFAULT_COLOR)
        dfs(u, cur);
    }
  }

  void find_connected() {
    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
      if (color[i] == DEFAULT_COLOR) {
        ++count;
        dfs(i, count);
      }
    }

    cout << count << '\n';
    for (auto c : color)
      cout << c << ' ';
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  size_t n, m;
  cin >> n >> m;
  Graph graph(n, m);
  graph.find_connected();
  return 0;
}