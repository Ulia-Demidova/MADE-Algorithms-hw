#include <climits>
#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::set;
using std::vector;

size_t MAX_D = UINT_MAX;

struct Edge {
  size_t from;
  size_t to;
  size_t weight;
  Edge(size_t from, size_t to, size_t w) : from(from), to(to), weight(w) {}
};

class Graph {
private:
  vector<vector<Edge>> edges;
  size_t n;

public:
  Graph(size_t n, size_t m) : edges(n), n(n) {
    size_t u, v, w;
    for (size_t i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u;
      --v;
      edges[u].push_back({u, v, w});
      edges[v].push_back({v, u, w});
    }
  }

  void shortest_paths() {
    vector<size_t> distance(n, MAX_D);
    vector<bool> used(n, false);
    set<pair<size_t, size_t>> queue;
    distance[0] = 0;
    queue.insert({0, 0});
    for (size_t i = 0; i < n; ++i) {
      if (queue.empty())
        break;
      size_t next = queue.extract(queue.begin()).value().second;
      used[next] = true;
      for (auto &edge : edges[next]) {
        if (!used[edge.to]) {
          queue.erase({distance[edge.to], edge.to});
          distance[edge.to] =
              std::min(distance[edge.to], distance[next] + edge.weight);
          queue.insert({distance[edge.to], edge.to});
        }
      }
    }
    for (auto &d : distance) {
      cout << d << ' ';
    }
  }
};

int main() {
  size_t n, m;
  cin >> n >> m;
  Graph graph(n, m);
  graph.shortest_paths();
  return 0;
}