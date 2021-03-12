#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::string;
using std::vector;

struct DSF {
  vector<size_t> parent;
  vector<size_t> rank;
  vector<size_t> experience;
  vector<size_t> experience_to_add;

  explicit DSF(size_t n)
      : parent(n), rank(n, 0), experience(n, 0), experience_to_add(n, 0) {
    for (size_t i = 0; i < n; ++i)
      parent[i] = i;
  }

  pair<size_t, size_t> get_(size_t &x) {
    if (parent[x] != x) {
      auto p = get_(parent[x]);
      experience_to_add[x] += p.second;
      parent[x] = p.first;
      return {parent[x], experience_to_add[x]};
    } else
      return {parent[x], 0};
  }

  void get(size_t &x) {
    get_(x);
    if (parent[x] == x)
      cout << experience[x] + experience_to_add[x] << '\n';
    else
      cout << experience[x] + experience_to_add[x] +
                  experience_to_add[parent[x]]
           << '\n';
  }

  void add(size_t x, size_t value) {
    size_t root = get_(x).first;
    experience_to_add[root] += value;
  }

  void join(size_t &x, size_t &y) {
    size_t root_x = get_(x).first;
    size_t root_y = get_(y).first;
    if (root_x == root_y)
      return;
    if (rank[root_x] > rank[root_y])
      std::swap(root_x, root_y);
    if (rank[root_x] == rank[root_y])
      ++rank[root_y];
    parent[root_x] = root_y;
    experience_to_add[root_x] -= experience_to_add[root_y];
  }
};

int main() {
  size_t n, m;
  cin >> n >> m;
  DSF dsf(n);
  string operation;
  size_t x, y;
  for (size_t i = 0; i < m; ++i) {
    cin >> operation;
    cin >> x;
    --x;
    if (operation == "add") {
      cin >> y;
      dsf.add(x, y);
    } else if (operation == "join") {
      cin >> y;
      --y;
      dsf.join(x, y);
    } else if (operation == "get") {
      dsf.get(x);
    }
  }
  return 0;
}
