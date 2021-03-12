#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::string;

struct Node {
  int key;
  int height;
  Node *left;
  Node *right;
  explicit Node(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
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

  Node *balance(Node *vertex) {
    if (!vertex)
      return vertex;
    if (abs(get_balance(vertex)) < 2) {
      vertex->height = fix_height(vertex);
      return vertex;
    }
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

  int fix_height(Node *vertex) {
    return max(get_height(vertex->left), get_height(vertex->right)) + 1;
  }

  Node *smallRotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    p->height = fix_height(p);
    q->height = fix_height(q);
    return q;
  }

  Node *smallRotateLeft(Node *p) {
    Node *q = p->right;
    p->right = q->left;
    q->left = p;
    p->height = fix_height(p);
    q->height = fix_height(q);
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

  bool exists_(Node *vertex, int key) {
    if (!vertex)
      return false;
    if (vertex->key == key)
      return true;
    if (key < vertex->key)
      return exists_(vertex->left, key);
    if (key > vertex->key)
      return exists_(vertex->right, key);
  }

  void print_key(Node *result) {
    if (result)
      cout << result->key << '\n';
    else
      cout << "none" << '\n';
  }

  void next_(int key) {
    Node *vertex = root;
    Node *res = nullptr;
    while (vertex) {
      if (key < vertex->key) {
        res = vertex;
        vertex = vertex->left;
      } else
        vertex = vertex->right;
    }
    print_key(res);
  }

  void prev_(int key) {
    Node *vertex = root;
    Node *res = nullptr;
    while (vertex) {
      if (key > vertex->key) {
        res = vertex;
        vertex = vertex->right;
      } else
        vertex = vertex->left;
    }
    print_key(res);
  }

public:
  void insert(int key) { root = insert_(root, key); }
  void del(int key) { root = del_(root, key); }
  bool exists(int key) { return exists_(root, key); }
  void next(int key) { next_(key); }
  void prev(int key) { prev_(key); }
};

int main() {
  string command;
  int key;
  AVLTree tree;
  while (cin >> command >> key) {
    if (command == "insert")
      tree.insert(key);
    else if (command == "delete")
      tree.del(key);
    else if (command == "exists") {
      if (tree.exists(key))
        cout << "true" << '\n';
      else
        cout << "false" << '\n';
    } else if (command == "next")
      tree.next(key);
    else
      tree.prev(key);
  }
  return 0;
}
