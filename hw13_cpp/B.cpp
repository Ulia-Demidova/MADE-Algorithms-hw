#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::pair;

struct Edge {
  size_t from;
  size_t to;
  int capacity;
  int flow;
  size_t pair_edge_id;
};

class Graph {
private:
  vector<vector<Edge>> edges;
  vector<bool> used;
  queue<pair<size_t, int>> q;
  vector<Edge*> parent;

public:
  Graph(size_t n, size_t m) : edges(n), parent(n), used(n, false) {
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

  size_t bfs(size_t s, size_t t) {
    used.assign(edges.size(), false);
    used[s] = true;

    q.push({s, INT_MAX});

    while (!q.empty()) {
      size_t v = q.front().first;
      int cur_flow = q.front().second;
      q.pop();

      int next_flow;
      for (auto &edge : edges[v]) {
        if (!used[edge.to] && edge.flow < edge.capacity) {
          parent[edge.to] = &edge;
          next_flow = std::min(cur_flow, edge.capacity - edge.flow);
          if (edge.to == t)
            return next_flow;
          q.push({edge.to, next_flow});
        }
      }
    }
    return 0;
  }

  size_t find_max_flow(size_t s, size_t t) {
    size_t max_flow = 0;
    while (true) {
      size_t delta = bfs(s, t);
      if (delta) {
        max_flow += delta;
        size_t cur = t;
        while (cur != s) {
          parent[cur]->flow += delta;
          edges[parent[cur]->to][parent[cur]->pair_edge_id].flow -= delta;
          cur = parent[cur]->from;
        }
      } else
        break;
    }
    return max_flow;
  }
};


int main() {
  size_t n, m;
  cin >> n >> m;
  Graph g(n, m);
  cout << g.find_max_flow(0, n-1);
  return 0;
}
