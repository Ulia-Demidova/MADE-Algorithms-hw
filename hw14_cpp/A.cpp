#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

const int64_t MOD = 1073676287;
const int64_t p = 31;

class StringHash {
private:
  vector<int64_t> hash;
  vector<int64_t> pow;

public:
  StringHash(string &s) : hash(s.size()), pow(s.size()) {
    hash[0] = (int64_t)s[0];
    pow[0] = 1;
    for (size_t i = 1; i < s.size(); ++i) {
      hash[i] = (hash[i - 1] * p + (int64_t)s[i]) % MOD;
      pow[i] = (pow[i - 1] * p) % MOD;
    }
  }

  int get_hash(size_t left, size_t right) {
    if (left == 0)
      return hash[right];
    return (hash[right] - (hash[left - 1] * pow[right - left + 1]) % MOD +
            MOD) %
           MOD;
  }
};

int main() {
  string s;
  size_t m;
  cin >> s >> m;
  StringHash str_hash(s);
  size_t a, b, c, d;
  for (size_t i = 0; i < m; ++i) {
    cin >> a >> b >> c >> d;
    if (str_hash.get_hash(a - 1, b - 1) == str_hash.get_hash(c - 1, d - 1))
      cout << "Yes" << '\n';
    else
      cout << "No" << '\n';
  }
  return 0;
}
