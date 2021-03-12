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
  size_t DEFAULT_COLOR = 0;
  vector<set<size_t>> edges;
  vector<set<size_t>> reversed_edges;
  vector<bool> used;
  vector<size_t> color;
  list<size_t> sorted;
  set<std::pair<size_t, size_t>> condensation_edges;

public:
  Graph(size_t n, size_t m) : edges(n), reversed_edges(n), color(n), used(n) {
    size_t u, v;
    for (size_t i = 0; i < m; ++i) {
      cin >> u >> v;
      if (u == v)
        continue;
      --u;
      --v;
      edges[u].insert(v);
      reversed_edges[v].insert(u);
    }
  }

  void dfs_straight(size_t vertex) {
    used[vertex] = true;
    for (auto &u : edges[vertex]) {
      if (!used[u])
        dfs_straight(u);
    }
    sorted.push_front(vertex);
  }

  void dfs_reversed(size_t vertex, size_t cur) {
    color[vertex] = cur;
    for (auto &u : reversed_edges[vertex]) {
      if (color[u] == DEFAULT_COLOR)
        dfs_reversed(u, cur);
      else if (color[u] != color[vertex])
        condensation_edges.insert({color[u], color[vertex]});
    }
  }

  size_t condensation(size_t n) {
    for (size_t i = 0; i < n; ++i) {
      if (!used[i])
        dfs_straight(i);
    }
    size_t cnt = 0;
    for (auto &v : sorted) {
      if (color[v] == DEFAULT_COLOR) {
        ++cnt;
        dfs_reversed(v, cnt);
      }
    }
    return condensation_edges.size();
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  size_t n, m;
  cin >> n >> m;

  Graph graph(n, m);
  cout << graph.condensation(n);
  return 0;
}