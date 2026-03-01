// Source: https://leetcode.com/problems/minimum-operations-to-equalize-binary-string
// Title: Minimum Operations to Equalize Binary String
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary string `s`, and an integer `k`.
//
// In one operation, you must choose **exactly** `k` **different** indices and **flip** each `'0'` to `'1'` and each `'1'` to `'0'`.
//
// Return the **minimum** number of operations required to make all characters in the string equal to `'1'`. If it is not possible, return -1.
//
// **Example 1:**
//
// ```
// Input: s = "110", k = 1
// Output: 1
// Explanation:
// - There is one `'0'` in `s`.
// - Since `k = 1`, we can flip it directly in one operation.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "0101", k = 3
// Output: 2
// Explanation:
// One optimal set of operations choosing `k = 3` indices in each operation is:
// - **Operation 1**: Flip indices `[0, 1, 3]`. `s` changes from `"0101"` to `"1000"`.
// - **Operation 2**: Flip indices `[1, 2, 3]`. `s` changes from `"1000"` to `"1111"`.
// Thus, the minimum number of operations is 2.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "101", k = 2
// Output: -1
// Explanation:
// Since `k = 2` and `s` has only one `'0'`, it is impossible to flip exactly `k` indices to make all `'1'`. Hence, the answer is -1.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^​​​​​​​5`
// - `s[i]` is either `'0'` or `'1'`.
// - `1 <= k <= s.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <string>
#include <vector>

using namespace std;

// Math + DP + BFS
//
// Say there are total n bits, z of them are 0.
//
// If z = 0, k = 1, k = z, then it is trivial.
// If k <= 0 or k > n, then it is impossible.
// If z odd & k even, then it is impossible (parity won't change).
//
// ---
//
// Let DP[z] be the min-ops from stop.
// For each step, we try to flip k bits.
//
// If z >= k, then we can flip all zeros; that is, z -= k.
// Also, if (n-z) >= k, then we can flip all ones; that is, z += k.
//
// Otherwise, if z < k, then we can flip all zeros with (k-d) zeros; that is z -> k-z
// Also, if (n-z) < k, then we can flip all ones with (k+d-n) zeros; that is z -> 2n-k-z
//
// Therefore, next step should be in above ranges (with same parity).
//
// ---
//
// Note that for in each step, we know that all node in a range with the same parity is visited.
// Therefore, we can store the visited range for both parity, and speed up the further BFS.
//
class Solution {
 public:
  int minOperations(const string &s, int k) {
    const int n = s.size();
    const int z = count(s.cbegin(), s.cend(), '0');

    // Trivial
    if (z == 0) return 0;
    if (k == 1) return z;
    if (k == z) return 1;

    // Impossible
    if (k <= 0 || k >= n) return -1;
    if (z % 2 == 1 && k % 2 == 0) return -1;

    // Visited ranges
    int minVisited[] = {n + 1, n + 1};  // even, odd
    int maxVisited[] = {-1, -1};        // even, odd

    // DP
    auto ops = vector<int>(n + 1);
    auto que = queue<int>();
    ops[z] = 0;
    que.push(z);
    while (!que.empty()) {
      auto curr = que.front();
      que.pop();

      // Traverse
      int minNext = max(curr - k, k - curr);
      int maxNext = min(curr + k, 2 * n - k - curr);
      int nextOps = ops[curr] + 1;
      int nextParity = (minNext) % 2;

      for (int next = minNext; next <= min(minVisited[nextParity] - 1, maxNext); next += 2) {
        if (next == 0) return nextOps;
        ops[next] = nextOps;
        que.push(next);
      }
      for (int next = maxNext; next >= max(maxVisited[nextParity] + 1, minNext); next -= 2) {
        if (next == 0) return nextOps;
        ops[next] = nextOps;
        que.push(next);
      }

      // Update visted range
      minVisited[nextParity] = min(minVisited[nextParity], minNext);
      maxVisited[nextParity] = max(maxVisited[nextParity], maxNext);
    }

    return -1;  // maybe unreachable
  }
};

// Math
//
// Say there are total n bits, z of them are 0.
//
// If z = 0, k = 1, k = z, then it is trivial.
// If k <= 0 or k > n, then it is impossible.
// If z odd & k even, then it is impossible (parity won't change).
//
// Say we need total m operations; i.e. total mk flips.
// Say we flip the i-th bit f[i] times.
//
// We can find the following constraints:
// 1. All zeros need odd flips, and all ones need even flips.
// 2. sum f[i] = mk.
// 3. 0 <= f[i] <= m.
//
// Now lets find the range of m.
//
// At minimal, we can only flip the zeros:
// mk >= z => m >= ceil(z / k).
//
// At maximum, we can flip all bits for almost m times.
// If m is odd, then we flip the zeros m times, and the ones m-1 times:
// zm + (n-z)(m-1) = mn - n + z >= mk => m(n-k) >= n-z => m >= ceil((n-z)/(n-k))
// If m is even, then we flip the zeros m-1 times, and the ones m times:
// z(m-1) + (n-z)m = mn - z >= mk => m(n-k) >= z => m >= ceil(z/(n-k))
//
// Note that the mk should have the same parity as z.
// If k is even, then k can be either even or odd.
// If k is odd, then k must have the same parity as z.
//
// By Gale-Ryser theorem, such m works.
class Solution2 {
  inline int ceilDiv(int a, int b) noexcept {  //
    return (a + b - 1) / b;
  }

 public:
  int minOperations(const string &s, int k) {
    const int n = s.size();
    const int z = count(s.cbegin(), s.cend(), '0');

    // Trivial
    if (z == 0) return 0;
    if (k == 1) return z;
    if (k == z) return 1;

    // Impossible
    if (k <= 0 || k >= n) return -1;
    if (z % 2 == 1 && k % 2 == 0) return -1;

    // From lower bound to find m
    int mBase = ceilDiv(z, k);

    // From odd upper bound to find m
    int mOdd = max(mBase, ceilDiv(n - z, n - k));
    mOdd += (mOdd % 2 == 0);

    // From even upper bound to find m
    int mEven = max(mBase, ceilDiv(z, n - k));
    mEven += (mEven % 2 == 1);

    // Consider k's parity
    if (k % 2) {  // k odd
      return (z % 2) ? mOdd : mEven;
    } else {  // k even
      return min(mOdd, mEven);
    }
  }
};
