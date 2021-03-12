#include <iostream>

using std::cin;
using std::cout;
using std::pair;
using std::string;

struct Node {
  int key;
  int priority;
  Node *left;
  Node *right;
  explicit Node(int key, int y)
      : key(key), priority(y), left(nullptr), right(nullptr) {}
};

class Treap {
private:
  Node *root = nullptr;

  pair<Node *, Node *> split(Node *vertex, int x) {
    if (!vertex)
      return {nullptr, nullptr};
    if (vertex->key > x) {
      pair<Node *, Node *> tree_split = split(vertex->left, x);
      vertex->left = tree_split.second;
      return {tree_split.first, vertex};
    } else {
      pair<Node *, Node *> tree_split = split(vertex->right, x);
      vertex->right = tree_split.first;
      return {vertex, tree_split.second};
    }
  }

  Node *merge(Node *root1, Node *root2) {
    if (!root1)
      return root2;
    if (!root2)
      return root1;
    if (root1->priority > root2->priority) {
      root1->right = merge(root1->right, root2);
      return root1;
    } else {
      root2->left = merge(root1, root2->left);
      return root2;
    }
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

  Node *insert_(Node *vertex, int key, int y) {
    if (!vertex)
      return new Node(key, y);

    if (vertex->priority < y) {
      std::pair<Node *, Node *> split_tree = split(vertex, key);
      Node *new_vertex = new Node(key, y);
      new_vertex->left = split_tree.first;
      new_vertex->right = split_tree.second;
      return new_vertex;
    }

    else if (key < vertex->key) {
      vertex->left = insert_(vertex->left, key, y);
      return vertex;
    } else if (key > vertex->key) {
      vertex->right = insert_(vertex->right, key, y);
      return vertex;
    }
  }

  Node *del_(Node *vertex, int key) {
    if (!vertex)
      return vertex;

    if (vertex->key == key) {
      Node *temp = vertex;
      vertex = merge(vertex->left, vertex->right);
      delete temp;
    } else if (key < vertex->key) {
      vertex->left = del_(vertex->left, key);
    } else if (key > vertex->key) {
      vertex->right = del_(vertex->right, key);
    }

    return vertex;
  }

public:
  void insert(int key, int y) {
    if (!exists(key)) {
      root = insert_(root, key, y);
    }
  }
  void del(int key) { root = del_(root, key); }
  bool exists(int key) { return exists_(root, key); }
  void next(int key) {
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
  void prev(int key) {
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
};

int main() {
  string command;
  int key;
  Treap tree;
  while (cin >> command >> key) {
    if (command == "insert")
      tree.insert(key, rand());
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
