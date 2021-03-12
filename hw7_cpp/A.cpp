#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::vector;

uint64_t answer(const vector<uint64_t> &array, const int &left,
                const int &right) {
  if (left == 0)
    return array[right];
  return array[right] - array[left - 1];
}

int main() {
  int n;
  int x, y, a; // or unsigned short int
  cin >> n >> x >> y >> a;
  int m;
  int z, t, b0;
  cin >> m >> z >> t >> b0;

  size_t const MOD_A = 1 << 16;
  size_t const MOD_B = 1 << 30;

  vector<uint64_t> prefix_sum(n);
  prefix_sum[0] = a;
  for (size_t i = 1; i < n; ++i) {
    a = (x * a + y) % MOD_A;
    prefix_sum[i] = prefix_sum[i - 1] + a;
  }

  int c0 = (b0 + n) % n;
  int b1 = (MOD_B + (z * b0 + t) % MOD_B) % MOD_B;

  int c1 = (b1 + n) % n;
  int64_t s = 0;
  for (size_t i = 0; i < m; ++i) {
    s += answer(prefix_sum, min(c0, c1), max(c0, c1));
    b0 = (MOD_B + (z * b1 + t) % MOD_B) % MOD_B;
    b1 = (MOD_B + (z * b0 + t) % MOD_B) % MOD_B;
    c0 = (b0 + n) % n;
    c1 = (b1 + n) % n;
  }
  cout << s << endl;
  return 0;
}
