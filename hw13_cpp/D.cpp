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
  vector<size_t> way;

public:
  Graph(int n, int m) : edges(n), used(n, false) {
    size_t a, b;
    for (size_t i = 0; i < m; ++i) {
      cin >> a >> b;
      if (a == b)
        continue;
      --a;
      --b;
      edges[a].push_back({a, b, 1, 0, edges[b].size()});
      edges[b].push_back({b, a, 0, 0, edges[a].size() - 1});
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

  size_t find_flow(size_t s, size_t t) {
    size_t max_flow = 0;
    size_t delta;
    for (size_t i = 0; i < 2; ++i) {
      used.assign(edges.size(), false);
      delta = push_flow(s, t, 1);
      max_flow += delta;
    }
    return max_flow;
  }

  void dfs(size_t v, size_t t) {
    way.push_back(v);
    if (v == t) {
      return;
    }
    for (auto &edge : edges[v]) {
      if (edge.flow == 1) {
        edge.flow -= 1;
        dfs(edge.to, t);
        break;
      }
    }
  }

public:
  void find_way(size_t s, size_t t) {
    size_t max_flow = find_flow(s, t);
    if (max_flow == 2) {
      cout << "YES" << '\n';
      for (size_t i = 0; i < 2; ++i) {
        dfs(s, t);
        for (auto &v : way)
          cout << v + 1 << ' ';
        cout << '\n';
        way.clear();
      }
    } else
      cout << "NO";
  }
};

int main() {
  size_t n, m, s, t;
  cin >> n >> m >> s >> t;
  Graph g(n, m);
  g.find_way(--s, --t);
  return 0;
}
