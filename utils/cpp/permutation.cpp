#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

using namespace std;

void all_permutation(int n) {
  auto temp = vector<int>(n);
  iota(temp.begin(), temp.end(), 0);

  do {
    // DO!
    // Result is temp
  } while (next_permutation(temp.begin(), temp.end()));
}

void all_partial_permutation(int n, int k) {
  assert(k <= n);

  auto temp = vector<int>(n);
  iota(temp.begin(), temp.end(), 0);

  do {
    // DO!
    // Result is temp[0, k)

    // Skip unused permutation
    reverse(temp.begin() + k, temp.end());
  } while (next_permutation(temp.begin(), temp.end()));
}

void all_combination(int n, int k) {
  assert(k <= n);

  auto temp = vector<int>(n, 1);
  fill(temp.begin(), temp.begin() + k, 0);  // [0, ..., 0, 1, ..., 1], first k are 0

  do {
    // DO!
    // Result is zero indices in temp
  } while (next_permutation(temp.begin(), temp.end()));
}
