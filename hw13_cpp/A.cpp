#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
  size_t from;
  size_t to;
  int capacity;
  int flow;
  size_t pair_edge_id;
  Edge(size_t a, size_t b, int c, int f, size_t i)
      : from(a), to(b), capacity(c), flow(f), pair_edge_id(i) {}
};

class Graph {
private:
  vector<vector<Edge>> edges;
  vector<bool> used;

  size_t push_flow(size_t v, size_t t, int cur_flow) {
    used[v] = true;
    if (v == t)
      return cur_flow;

    int next_flow;
    for (auto &edge : edges[v]) {
      if (!used[edge.to] && edge.flow < edge.capacity) {
        next_flow = std::min(cur_flow, edge.capacity - edge.flow);
        size_t delta = push_flow(edge.to, t, next_flow);
        if (delta > 0) {
          edge.flow += delta;
          edges[edge.to][edge.pair_edge_id].flow -= delta;
          return delta;
        }
      }
    }
    return 0;
  }

public:
  Graph(int n, int m) : edges(n), used(n, false) {
    size_t a, b;
    int c;
    for (size_t i = 0; i < m; ++i) {
      cin >> a >> b >> c;
      --a;
      --b;
      edges[a].push_back({a, b, c, 0, edges[b].size()});
      edges[b].push_back({b, a, 0, 0, edges[a].size() - 1});

      edges[b].push_back({b, a, c, 0, edges[a].size()});
      edges[a].push_back({a, b, 0, 0, edges[b].size() - 1});
    }
  }

  size_t find_flow(size_t s, size_t t) {
    size_t max_flow = 0;
    while (true) {
      used.assign(edges.size(), false);
      size_t delta = push_flow(s, t, INT_MAX);
      if (delta > 0)
        max_flow += delta;
      else
        break;
    }
    return max_flow;
  }
};

int main() {
  size_t n, m;
  cin >> n >> m;
  Graph g(n, m);
  cout << g.find_flow(0, n - 1);
  return 0;
}
