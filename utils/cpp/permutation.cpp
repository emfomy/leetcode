#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

using namespace std;

// Input: frequencies of item 0 ~ (n-1)
// Input: k is 1-based
//
// Idea:
// For each position, loop for each item `x`.
// Let `c` be the number of permutations when we use `x` in this position.
// If k <= c, then we can use `x` in this position.
// Otherwise, skip `x` and try next item, also `k -= c`.
vector<int> kth_permutation(vector<int>& freqs, int k) {
  const int n = accumulate(freqs.cbegin(), freqs.cend(), 0);  // array size
  const int m = freqs.size();                                 // item set

  // Multinomial
  // Permutations number for (c1, c2, ..., cm) = n! / c1! c2! ... cm!
  // However, factorial will overflow, we compute using multiple binomial instead.
  // n! / c1! c2! ... cm! = C(c1+c2, c2) * C(c1+c2+c3, c3) * ...
  //
  // Note that for the result greater than k, we don't need exact number.
  // Therefore we will early stop when the result the too large.
  auto countPerms = [&freqs, k]() -> int {
    int64_t total = 1;
    int acc = 0;
    for (int freq : freqs) {
      for (int i = 1; i <= freq; ++i) {
        total *= ++acc;
        total /= i;
        if (total >= k) return k;  // early stop
      }
    }
    return total;
  };

  // Construct
  auto ans = vector<int>();
  ans.reserve(n);
  for (int i = 0; i < n; ++i) {
    bool found = false;

    for (int x = 0; x < m; ++x) {  // try each item
      if (freqs[x] == 0) continue;

      --freqs[x];  // try to use x here
      int perms = countPerms();

      // enough permutation, use x
      if (k < perms) {
        ans.push_back(x);
        found = true;
        break;
      }

      // no enough permutation, skip x
      k -= perms;
      ++freqs[x];  // put x back
    }

    if (!found) return {};  // invalid k
  }

  return ans;
}

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
