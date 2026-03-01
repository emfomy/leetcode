#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

using namespace std;

void all_permutation(int n) {
  auto idxs = vector<int>(n);
  iota(idxs.begin(), idxs.end(), 0);

  do {
    // DO!
  } while (next_permutation(idxs.begin(), idxs.end()));
}

void all_partial_permutation(int n, int k) {
  assert(k <= n);

  auto idxs = vector<int>(n);
  iota(idxs.begin(), idxs.end(), 0);

  do {
    // DO!

    // Skip unused permutation
    reverse(idxs.begin() + k, idxs.end());
  } while (next_permutation(idxs.begin(), idxs.end()));
}

void all_combination(int n, int k) {
  assert(k <= n);

  auto idxs = vector<int>(n, 0);
  fill(idxs.begin() + n - k, idxs.end(), 1);  // [0, ..., 0, 1, ..., 1], k times 1

  do {
    // DO!
  } while (next_permutation(idxs.begin(), idxs.end()));
}
