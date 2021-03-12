#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
  string s;
  cin >> s;

  vector<int> z_func(s.size());
  int left = 0;
  int right = 0;
  for (int i = 1; i < s.size(); ++i) {
    z_func[i] = std::max(0, std::min(right - i, z_func[i - left]));
    while (i + z_func[i] < s.size() && s[z_func[i]] == s[i + z_func[i]])
      ++z_func[i];

    if (i + z_func[i] > right) {
      left = i;
      right = i + z_func[i];
    }
  }

  for (size_t i = 1; i < z_func.size(); ++i)
    cout << z_func[i] << ' ';

  return 0;
}