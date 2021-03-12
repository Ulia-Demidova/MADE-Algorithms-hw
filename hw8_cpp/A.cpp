#include <iostream>

using std::cin;
using std::cout;
using std::string;

struct Node {
  int key;
  Node *left;
  Node *right;
  explicit Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

class BST {
private:
  Node *root = nullptr;

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
    return vertex;
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
    return vertex;
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

  void print_key(Node *vertex) {
    if (vertex)
      cout << vertex->key << '\n';
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
      } else {
        vertex = vertex->right;
      }
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
  BST tree;
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
