#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct DSF {
  vector<size_t> parent;
  vector<size_t> rank;

  explicit DSF(size_t n) : parent(n), rank(n, 0) {
    for (size_t i = 0; i < n; ++i)
      parent[i] = i;
  }

  size_t get(size_t &x) {
    if (parent[x] != x)
      parent[x] = get(parent[x]);
    return parent[x];
  }

  void join(size_t &x, size_t &y) {
    size_t root_x = get(x);
    size_t root_y = get(y);
    if (root_x == root_y)
      return;
    if (rank[root_x] > rank[root_y])
      std::swap(root_x, root_y);
    if (rank[root_x] == rank[root_y])
      ++rank[root_y];
    parent[root_x] = root_y;
  }
};

struct Edge {
  size_t from;
  size_t to;
  size_t weight;
};

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<Edge> edges(m);
  size_t from, to, weight;
  for (size_t i = 0; i < m; ++i) {
    cin >> from >> to >> weight;
    --from;
    --to;
    edges[i] = {from, to, weight};
  }
  std::sort(edges.begin(), edges.end(),
            [](Edge &u, Edge &v) { return u.weight < v.weight; });
  uint64_t final_weight = 0;
  DSF dsf(n);
  for (auto &edge : edges) {
    if (dsf.get(edge.to) != dsf.get(edge.from)) {
      final_weight += edge.weight;
      dsf.join(edge.from, edge.to);
    }
  }
  cout << final_weight;
  return 0;
}