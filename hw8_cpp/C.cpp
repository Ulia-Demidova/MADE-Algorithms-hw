#include <iostream>

using std::cin;
using std::cout;
using std::max;

struct Node {
  int key;
  int height;
  int count;
  Node *left;
  Node *right;
  explicit Node(int key)
      : key(key), height(1), count(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
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

  int get_count(Node *vertex) {
    if (vertex)
      return vertex->count;
    else
      return 0;
  }

  Node *fix(Node *vertex) {
    vertex->height =
        max(get_height(vertex->left), get_height(vertex->right)) + 1;
    vertex->count = get_count(vertex->left) + get_count(vertex->right) + 1;
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

  Node *find_max(Node *vertex) {
    while (vertex->right)
      vertex = vertex->right;
    return vertex;
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

  Node *del_(Node *vertex, int key) {
    if (!vertex)
      return vertex;
    if (key < vertex->key)
      vertex->left = del_(vertex->left, key);
    else if (key > vertex->key)
      vertex->right = del_(vertex->right, key);
    else if (!vertex->right && !vertex->left) {
      delete vertex;
      vertex = nullptr;
    } else if (!vertex->left) {
      Node *temp = vertex;
      vertex = vertex->right;
      delete temp;
    } else if (!vertex->right) {
      Node *temp = vertex;
      vertex = vertex->left;
      delete temp;
    } else {
      vertex->key = find_max(vertex->left)->key;
      vertex->left = del_(vertex->left, vertex->key);
    }
    return balance(vertex);
  }

  Node *k_max(Node *vertex, int k) {
    if (get_count(vertex->right) == k - 1)
      return vertex;
    else if (get_count(vertex->right) >= k)
      return k_max(vertex->right, k);
    else if (get_count(vertex->right) < k - 1)
      return k_max(vertex->left, k - get_count(vertex->right) - 1);
  }
public:
  void insert(int key) { root = insert_(root, key); }
  void del(int key) { root = del_(root, key); }
  int search(int k) { return k_max(root, k)->key; }
};

int main() {
  int n;
  cin >> n;
  int command, key;
  AVLTree tree;
  for (size_t i = 0; i < n; ++i) {
    cin >> command >> key;
    if (command == 1)
      tree.insert(key);
    else if (command == -1)
      tree.del(key);
    else if (command == 0) {
      cout << tree.search(key) << '\n';
    }
  }

  return 0;
}