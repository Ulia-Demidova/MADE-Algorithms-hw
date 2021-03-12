#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

int64_t MAX_D = INT64_MAX;
int64_t MIN_D = INT64_MIN;

struct Edge {
  size_t from;
  size_t to;
  int64_t weight;
  Edge(size_t from, size_t to, int64_t w) : from(from), to(to), weight(w) {}
};

int main() {
  size_t n, m, s;
  cin >> n >> m >> s;
  --s;
  vector<Edge> edges;
  size_t from, to;
  int64_t weight;
  for (size_t i = 0; i < m; ++i) {
    cin >> from >> to >> weight;
    edges.emplace_back(--from, --to, weight);
  }

  vector<int64_t> distance(n, MAX_D);
  distance[s] = 0;
  vector<size_t> prev(n);
  for (size_t i = 0; i < n; ++ i)
    prev[i] = -1;
  prev[s] = s;

  for (size_t i = 0; i < n; ++i) {
    for (auto &edge : edges) {
      if (distance[edge.from] < MAX_D){
        distance[edge.to] = std::min(distance[edge.to], distance[edge.from] + edge.weight);
        prev[edge.to] = edge.from;
      }
    }
  }

  vector<int64_t> answer = distance;

  for (auto &edge : edges) {
    if (answer[edge.from] == MIN_D || (answer[edge.from] < MAX_D && answer[edge.to] > answer[edge.from] + edge.weight)) {
      size_t v = edge.to;
      prev[v] = edge.from;
      answer[v] = MIN_D;
      for (size_t i = 0; i < n; ++i){
        v = prev[v];
        answer[v] = MIN_D;
      }
      size_t cur = v;
      while (prev[cur] != v)
        cur = prev[cur];
      answer[cur] = MIN_D;
    }
  }

  vector<int64_t> prev_answer = answer;
  while (true) {
    for (auto &edge : edges) {
      if (answer[edge.from] == MIN_D)
        answer[edge.to] = MIN_D;
    }
    if (prev_answer == answer)
      break;
    else
      prev_answer = answer;
  }

  for (auto &d : answer){
    if (d == MIN_D)
      cout << '-' << '\n';
    else if (d == MAX_D)
      cout << '*' << '\n';
    else
      cout << d << '\n';
  }
  return 0;
}

