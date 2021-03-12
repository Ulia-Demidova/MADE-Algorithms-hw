#include <cstdio>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::min;
using std::pair;
using std::string;
using std::vector;

class Tree {
  const int64_t MAX_VAL = 9223372036854775807;
  vector<int64_t> tree;
  vector<pair<int64_t, bool>> upd;

public:
  Tree(const vector<int64_t> &array, const size_t &n, const int &size) {
    tree.assign(2 * size - 1, MAX_VAL);
    upd.assign(2 * size - 1, make_pair(0, true));
    for (size_t i = 0; i < n; ++i)
      tree[i + size - 1] = array[i];

    for (int i = size - 2; i >= 0; --i) {
      tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  void push(const size_t &vertex, const size_t &left, const size_t &right) {
    if (left == right) {
      tree[vertex] = get(vertex);
    } else {
      if (upd[vertex].second) {
        upd[2 * vertex + 1].first += upd[vertex].first;
        upd[2 * vertex + 2].first += upd[vertex].first;
      } else {
        upd[2 * vertex + 1].first = upd[vertex].first;
        upd[2 * vertex + 2].first = upd[vertex].first;
        upd[2 * vertex + 1].second = false;
        upd[2 * vertex + 2].second = false;
      }
      tree[vertex] = min(get(2 * vertex + 1), get(2 * vertex + 2));
    }
    upd[vertex].first = 0;
    upd[vertex].second = true;
  }

  int64_t get(const size_t &vertex) {
    if (upd[vertex].second)
      return tree[vertex] + upd[vertex].first;
    else
      return upd[vertex].first;
  }

  int64_t rmq(const size_t &vertex, const size_t &left, const size_t &right,
              const size_t &a, const size_t &b) {
    if (left > b || right < a)
      return MAX_VAL;
    if (left >= a && right <= b)
      return get(vertex);
    push(vertex, left, right);
    size_t m = (left + right) / 2;
    return min(rmq(2 * vertex + 1, left, m, a, b),
               rmq(2 * vertex + 2, m + 1, right, a, b));
  }

  void update(const size_t &vertex, const size_t &left, const size_t &right,
              const size_t &a, const size_t &b, const int64_t &value,
              bool to_add = true) {
    push(vertex, left, right);
    if (left > b || right < a)
      return;
    if (left >= a && right <= b) {
      upd[vertex].first += value;
      if (!to_add)
        upd[vertex].second = false;
      return;
    }
    size_t m = (left + right) / 2;
    update(2 * vertex + 1, left, m, a, b, value, to_add);
    update(2 * vertex + 2, m + 1, right, a, b, value, to_add);
    tree[vertex] = min(get(2 * vertex + 1), get(2 * vertex + 2));
  }
};

int main() {
  size_t n;
  cin >> n;
  vector<int64_t> a(n);
  for (size_t i = 0; i < n; ++i)
    cin >> a[i];

  int k = 1;
  while (k < n)
    k *= 2;
  Tree segment_tree(a, n, k);

  string command;
  size_t i, j;
  int64_t val;

  while (cin >> command) {
    cin >> i >> j;
    if (command == "set") {
      cin >> val;
      segment_tree.update(0, 0, k - 1, i - 1, j - 1, val, false);
    } else if (command == "add") {
      cin >> val;
      segment_tree.update(0, 0, k - 1, i - 1, j - 1, val);
    } else {
      cout << segment_tree.rmq(0, 0, k - 1, i - 1, j - 1) << '\n';
    }
  }
  return 0;
}