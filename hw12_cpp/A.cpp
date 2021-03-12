#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;


struct DSF {
  vector<size_t> parent;
  vector<size_t> rank;
  vector<size_t> max_element;
  vector<size_t> min_element;
  vector<size_t> count;

  explicit DSF(size_t n)
      : parent(n), max_element(n), min_element(n), rank(n, 0), count(n, 1) {
    for (size_t i = 0; i < n; ++i) {
      parent[i] = i;
      max_element[i] = i;
      min_element[i] = i;
    }
  }

  size_t get_(size_t &x) {
    if (parent[x] != x)
      parent[x] = get_(parent[x]);
    return parent[x];
  }

  void get(size_t &x) {
    size_t root = get_(x);
    cout << min_element[root] + 1 << ' ' << max_element[root] + 1 << ' '
         << count[root] << '\n';
  }

  void join(size_t &x, size_t &y) {
    size_t root_x = get_(x);
    size_t root_y = get_(y);
    if (root_x == root_y)
      return;
    if (rank[root_x] > rank[root_y])
      std::swap(root_x, root_y);
    if (rank[root_x] == rank[root_y])
      ++rank[root_y];
    min_element[root_y] = std::min(min_element[root_y], min_element[root_x]);
    max_element[root_y] = std::max(max_element[root_y], max_element[root_x]);
    count[root_y] += count[root_x];
    parent[root_x] = root_y;
  }
};

int main() {
  size_t n;
  cin >> n;
  DSF dsf(n);
  string operation;
  size_t x, y;
  while (cin >> operation) {
    cin >> x;
    if (operation == "union") {
      cin >> y;
      dsf.join(--x, --y);
    } else if (operation == "get")
      dsf.get(--x);
  }
  return 0;
}
