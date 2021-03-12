#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
  string p, t;
  cin >> p >> t;
  string s = p + "#" + t;

  vector<int> prefix_func(s.size());
  prefix_func[0] = 0;
  int k;
  for (size_t i = 1; i < s.size(); ++i) {
    k = prefix_func[i - 1];
    while (k > 0 && s[i] != s[k])
      k = prefix_func[k - 1];
    if (s[i] == s[k])
      ++k;
    prefix_func[i] = k;
  }

  vector<int> answer;
  for (size_t i = p.size() + 1; i < s.size(); ++i) {
    if (prefix_func[i] == p.size())
      answer.push_back(i - 2 * p.size() + 1);
  }
  cout << answer.size() << '\n';
  for (auto &idx : answer)
    cout << idx << ' ';
  return 0;
}
