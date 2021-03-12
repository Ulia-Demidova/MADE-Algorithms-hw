#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::list;
using std::set;
using std::vector;

class Graph {
private:
  vector<set<size_t>> edges;
  vector<size_t> color;
  list<size_t> sorted;

public:
  Graph(size_t n, size_t m) : edges(n), color(n) {
    size_t u, v;
    for (size_t i = 0; i < m; ++i) {
      cin >> u >> v;
      --u;
      --v;
      edges[u].insert(v);
    }
  }

  void dfs(size_t vertex) {
    color[vertex] = 1;
    for (auto &u : edges[vertex]) {
      if (color[u] == 0)
        dfs(u);
      else if (color[u] == 1) {
        return;
      }
    }
    color[vertex] = 2;
    sorted.push_front(vertex + 1);
  }

  void topological_sort(size_t n) {
    for (size_t i = 0; i < n; ++i) {
      if (color[i] == 0)
        dfs(i);
    }
    if (sorted.size() < n)
      cout << -1;
    else {
      for (auto &v : sorted)
        cout << v << ' ';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  size_t n, m;
  cin >> n >> m;

  Graph graph(n, m);
  graph.topological_sort(n);

  return 0;
}
