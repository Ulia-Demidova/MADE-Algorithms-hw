#include <iostream>

using std::cin;
using std::cout;
using std::max;

struct Node {
  int key;
  int height;
  uint64_t sum;
  Node *left;
  Node *right;
  explicit Node(int key)
      : key(key), sum(key), height(1), left(nullptr), right(nullptr) {
  }
};

class AVL {
private:
  Node *root = nullptr;

  int get_height(Node *vertex) {
    if (vertex)
      return vertex->height;
    else
      return 0;
  }

  int get_balance(Node *vertex) {
    return get_height(vertex->left) - get_height(vertex->right);
  }

  Node *fix(Node *vertex) {
    vertex->height =
        max(get_height(vertex->left), get_height(vertex->right)) + 1;
    vertex->sum = get_sum(vertex->left) + get_sum(vertex->right) + vertex->key;
    return vertex;
  }

  Node *balance(Node *vertex) {
    if (!vertex)
      return vertex;
    if (abs(get_balance(vertex)) < 2)
      return fix(vertex);
    if (get_balance(vertex) == 2) {
      if (get_height(vertex->left->right) <= get_height(vertex->left->left))
        return smallRotateRight(vertex);
      else
        return bigRotateRight(vertex);
    }
    if (get_balance(vertex) == -2) {
      if (get_height(vertex->right->left) <= get_height(vertex->right->right))
        return smallRotateLeft(vertex);
      else
        return bigRotateLeft(vertex);
    }
  }

  Node *smallRotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    p = fix(p);
    q = fix(q);
    return q;
  }

  Node *smallRotateLeft(Node *p) {
    Node *q = p->right;
    p->right = q->left;
    q->left = p;
    p = fix(p);
    q = fix(q);
    return q;
  }

  Node *bigRotateRight(Node *p) {
    p->left = smallRotateLeft(p->left);
    return smallRotateRight(p);
  }

  Node *bigRotateLeft(Node *p) {
    p->right = smallRotateRight(p->right);
    return smallRotateLeft(p);
  }

  Node *insert_(Node *vertex, int key) {
    if (!vertex)
      return new Node(key);
    else if (key < vertex->key)
      vertex->left = insert_(vertex->left, key);
    else if (key > vertex->key)
      vertex->right = insert_(vertex->right, key);
    return balance(vertex);
  }

  uint64_t get_sum(Node *vertex){
    if (vertex)
      return vertex->sum;
    else
      return 0;
  }

  uint64_t sum_(Node *vertex, int left, int right) {
    while (vertex) {
      if (vertex->key < left)
        vertex = vertex->right;
      else if (vertex->key > right)
        vertex = vertex->left;
      else
        break;
    }

    if (!vertex)
      return 0;

    uint64_t result = vertex->key;

    Node *left_vertex = vertex->left;
    Node *right_vertex = vertex->right;

    while (left_vertex && left_vertex->key >= left) {
      result += left_vertex->key + get_sum(left_vertex->right);
      left_vertex = left_vertex->left;
    }

    if (left_vertex)
      result += sum_(left_vertex->right, left, right);

    while (right_vertex && right_vertex->key <= right) {
      result += right_vertex->key + get_sum(right_vertex->left);
      right_vertex = right_vertex->right;
    }

    if (right_vertex)
      result += sum_(right_vertex->left, left, right);

    return result;
  }

public:
  void insert(int key) { root = insert_(root, key); }
  uint64_t sum(int left, int right) { return sum_(root, left, right); }
};

int main() {
  int n;
  cin >> n;
  bool prev_ask = false;
  char command;
  uint64_t key;
  int left, right;
  uint64_t answer;
  uint64_t MOD = 1'000'000'000;
  AVL tree;
  for (size_t i = 0; i < n; ++i) {
    cin >> command;
    if (command == '+') {
      cin >> key;
      if (!prev_ask)
        tree.insert(key);
      else
        tree.insert((answer + key) % MOD);
      prev_ask = false;
    } else if (command == '?') {
      cin >> left >> right;
      answer = tree.sum(left, right);
      cout << answer << '\n';
      prev_ask = true;
    }
  }
  return 0;
}
