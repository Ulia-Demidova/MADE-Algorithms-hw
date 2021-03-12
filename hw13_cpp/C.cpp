#include <iostream>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::set;

struct Edge {
  size_t from;
  size_t to;
  int capacity;
  int flow;
  size_t pair_edge_id;
  size_t edge_order;
  Edge(size_t a, size_t b, int c, int f, size_t i, size_t order)
      : from(a), to(b), capacity(c), flow(f), pair_edge_id(i), edge_order(order) {}
};

class Graph {
private:
  vector<vector<Edge>> edges;
  vector<bool> used;

public:
  Graph(int n, int m) : edges(n), used(n, false) {
    size_t a, b;
    int c;
    for (size_t i = 0; i < m; ++i) {
      cin >> a >> b >> c;
      --a;
      --b;
      edges[a].push_back({a, b, c, 0, edges[b].size(), i});
      edges[b].push_back({b, a, 0, 0, edges[a].size() - 1, i});

      edges[b].push_back({b, a, c, 0, edges[a].size(), i});
      edges[a].push_back({a, b, 0, 0, edges[b].size() - 1, i});
    }
  }

private:
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

  size_t find_flow(size_t start, size_t finish) {
    size_t max_flow = 0;
    while (true) {
      used.assign(edges.size(), false);
      size_t delta = push_flow(start, finish, INT_MAX);
      if (delta > 0)
        max_flow += delta;
      else
        break;
    }
    return max_flow;
  }

  void cut(size_t s) {
    used[s] = true;
    for (auto &edge : edges[s]) {
      if (!used[edge.to] && edge.flow < edge.capacity)
        cut(edge.to);
    }
  }

public:
  void find_cut(size_t s) {
    size_t max_flow = find_flow(0, edges.size() - 1);
    used.assign(edges.size(), false);
    cut(s);
    set<size_t> cut_edges;
    for (auto &edge_list : edges) {
      for (auto &edge : edge_list) {
        if (used[edge.from] != used[edge.to])
          cut_edges.insert(edge.edge_order);
      }
    }
    cout << cut_edges.size() << ' ' << max_flow << '\n';
    for (auto &edge_id : cut_edges)
      cout << edge_id + 1 << ' ';
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  Graph g(n, m);
  g.find_cut(0);
  return 0;
}
