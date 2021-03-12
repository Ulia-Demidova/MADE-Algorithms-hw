#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

const char start_letter = 'a';

class Trie {
private:
  vector<vector<int>> next;
  vector<int> is_terminal;

public:
  Trie() {
    next.emplace_back(vector<int>(26, -1));
    is_terminal.push_back(-1);
  }

  void insert(string &word, int idx) {
    int v = 0;
    for (auto &c : word) {
      if (next[v][c - start_letter] == -1) {
        next[v][c - start_letter] = next.size();
        next.emplace_back(vector<int>(26, -1));
        is_terminal.push_back(-1);
      }
      v = next[v][c - start_letter];
    }
    is_terminal[v] = idx;
  }

  void search(string &t, int m) {
    vector<bool> answer(m, false);
    for (size_t i = 0; i < t.size(); ++i) {
      int v = 0;
      int j = i;
      while (j < t.size() && next[v][t[j] - start_letter] != -1) {
        v = next[v][t[j] - start_letter];
        if (is_terminal[v] > -1)
          answer[is_terminal[v]] = true;
        ++j;
      }
    }
    for (auto ans : answer) {
      if (ans)
        cout << "Yes" << '\n';
      else
        cout << "No" << '\n';
    }
  }
};

int main() {
  string t;
  size_t m;
  cin >> t >> m;
  Trie trie;

  string word;
  for (size_t i = 0; i < m; ++i) {
    cin >> word;
    trie.insert(word, i);
  }

  trie.search(t, m);
  return 0;
}