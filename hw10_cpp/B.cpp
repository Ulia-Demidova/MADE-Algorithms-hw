#include <algorithm>
#include <iostream>
#include <map>
#include <set>

using std::cin;
using std::cout;
using std::map;
using std::set;
using std::string;

class RepostGraph {
private:
  map<string, bool> used;
  map<string, set<string>> edges;

public:
  explicit RepostGraph(size_t n) {
    string name1, name2;
    string reposted = "reposted";
    for (size_t i = 0; i < n; ++i) {
      cin >> name1 >> reposted >> name2;
      std::transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
      std::transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
      edges[name2].insert(name1);
    }
  }

  size_t dfs(const string &name) {
    used[name] = true;
    size_t max_length = 1;
    for (auto &repost : edges[name]) {
      if (!used[repost])
        max_length = std::max(max_length, dfs(repost) + 1);
    }
    return max_length;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  size_t n;
  cin >> n;
  RepostGraph graph(n);
  cout << graph.dfs("polycarp");
  return 0;
}
