#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::list;

struct Edge {
  size_t from;
  size_t to;
  int weight;
};

bool dfs(size_t start, const vector<vector<Edge>> &edges, vector<bool>& used) {
  used[start] = true;
  for (auto &edge : edges[start]) {
    if (!used[edge.to])
      dfs(edge.to, edges, used);
  }
  for (size_t i = 0; i < used.size(); ++i) {
    if (!used[i])
      return false;
  }
  return true;
}

class Graph {
private:
  size_t DEFAULT_COLOR = 0;
  vector<vector<Edge>> edges;
  vector<vector<Edge>> reversed_edges;
  vector<bool> used;
  vector<size_t> color;
  list<size_t> sorted;
  vector<vector<Edge>> condensation_edges;

public:
  Graph(vector<vector<Edge>> &edges, size_t n, size_t m) : edges(edges), reversed_edges(n), color(n), used(n) {
    for (auto &edges_list : edges) {
      for (auto &edge : edges_list) {
      reversed_edges[edge.to].push_back({edge.to, edge.from, edge.weight});
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



int MST(size_t root, vector<vector<Edge>> &edges, size_t n) {
  int64_t res = 0;
  vector<int> min_edge(n, INT_MAX);
  for (auto &edges_list : edges) {
    for (auto &edge : edges_list)
      min_edge[edge.to] = std::min(min_edge[edge.to], edge.weight);
  }
  for (size_t i = 0; i < n; ++i) {
    if (i != root)
      res += min_edge[i];
  }

  vector<vector<Edge>> zero_edges(n);
  for (auto &edges_list : edges) {
    for (auto &edge : edges_list) {
      edge.weight -= min_edge[edge.to];
      if (edge.weight == 0)
        zero_edges[edge.from].push_back(edge);
    }
  }
  vector<bool> used(n, false);
  if (dfs(root, zero_edges, used))
    return res;




}




int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<Edge>> edges(n);
  size_t from, to;
  int weight;
  for (size_t i = 0; i < m; ++i) {
    cin >> from >> to >> weight;
    if (from == to)
      continue;
    --from;
    --to;
    edges[from].push_back({from, to, weight});
  }
  vector<bool> used(n, false);
  if (dfs(0, edges, used)) {
    cout << "YES" << '\n' << MST();
  } else {
    cout << "NO";
  }
  return 0;
}