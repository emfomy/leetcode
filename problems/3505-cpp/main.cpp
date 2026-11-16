// Source: https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal
// Title: Minimum Operations to Make Elements Within K Subarrays Equal
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and two integers, `x` and `k`. You can perform the following operation any number of times (**including zero**):
//
// - Increase or decrease any element of `nums` by 1.
//
// Return the **minimum** number of operations needed to have **at least** `k` non-overlapping <button>subarrays</button> of size **exactly** `x` in `nums`, where all elements within each subarray are equal.
//
// **Example 1:**
//
// ```
// Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
// Output: 8
// Explanation:
// - Use 3 operations to add 3 to `nums[1]` and use 2 operations to subtract 2 from `nums[3]`. The resulting array is `[5, 1, 1, 1, 7, 3, 6, 4, -1]`.
// - Use 1 operation to add 1 to `nums[5]` and use 2 operations to subtract 2 from `nums[6]`. The resulting array is `[5, 1, 1, 1, 7, 4, 4, 4, -1]`.
// - Now, all elements within each subarray `[1, 1, 1]` (from indices 1 to 3) and `[4, 4, 4]` (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [9,-2,-2,-2,1,5], x = 2, k = 2
// Output: 3
// Explanation:
// - Use 3 operations to subtract 3 from `nums[4]`. The resulting array is `[9, -2, -2, -2, -2, 5]`.
// - Now, all elements within each subarray `[-2, -2]` (from indices 1 to 2) and `[-2, -2]` (from indices 3 to 4) are equal. Since 3 operations were used, 3 is the output.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 10^5`
// - `-10^6 <= nums[i] <= 10^6`
// - `2 <= x <= nums.length`
// - `1 <= k <= 15`
// - `2 <= k * x <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <set>
#include <vector>

using namespace std;

// DP
//
// DP[i, t] be the min ops for nums[:i] to have t such subarrays.
// DP[:, 0] = 0
// DP[0,>0] = INF (impossible)
//
// For each t, loop through all i.
// For each i, we can construct a new subarray from DP[i-x, t-1].
// DP[i, t] = min(
//   DP[i-1, t],          // extending
//   DP[i-x, t-1] + cost, // construct new subarray
// )
//
// To compute the cost of each subarray, we move them to its medium.
// We can precompute all the costs.
class Solution {
  static constexpr long long kInf = LLONG_MAX / 4;

  struct MediumSet {
    using Item = pair<int, int>;  // number, index

    int n;  // size of this set
    long long upperSum = 0;
    long long lowerSum = 0;

    set<Item, less<Item>> upper;     // size n/2
    set<Item, greater<Item>> lower;  // size n/2 + n%2

    MediumSet(int n) : n(n) {}

    void balance() {
      while (upper.size() > n / 2) {
        auto it = upper.cbegin();
        lowerSum += it->first;
        upperSum -= it->first;
        lower.insert(*it);
        upper.erase(it);
      }

      while (upper.size() < n / 2 && !lower.empty()) {
        auto it = lower.cbegin();
        upperSum += it->first;
        lowerSum -= it->first;
        upper.insert(*it);
        lower.erase(it);
      }
    }

    void insert(const Item item) {
      if (upper.empty() || item >= *upper.cbegin()) {
        upper.insert(item);
        upperSum += item.first;
      } else {
        lower.insert(item);
        lowerSum += item.first;
      }
      balance();
    }

    void erase(const Item item) {  // item must exist
      if (upper.erase(item)) {
        upperSum -= item.first;
      } else {
        lower.erase(item);
        lowerSum -= item.first;
      }
      balance();
    }

    int median() {  // call this only when size is n
      return lower.cbegin()->first;
    }
  };

 public:
  long long minOperations(const vector<int>& nums, int x, int k) {
    const int n = nums.size();

    // Compute subarray medians
    auto costs = vector<long long>();
    costs.reserve(n - x + 1);
    auto mset = MediumSet(x);
    for (int i = 0; i < n; ++i) {
      // Add/Remove item
      mset.insert({nums[i], i});
      if (i >= x) {
        mset.erase({nums[i - x], i - x});
      }

      // Compute median
      if (i >= x - 1) {
        int median = mset.median();
        costs.push_back(median * (x % 2) + mset.upperSum - mset.lowerSum);
      }
    }

    // DP
    auto dp = vector(k + 1, vector<long long>(n + 1));
    fill(dp[0].begin(), dp[0].end(), 0);
    for (int t = 1; t <= k; ++t) {
      fill(dp[t].begin(), dp[t].begin() + x, kInf);
      for (int i = x; i <= n; ++i) {
        dp[t][i] = min(dp[t][i - 1], dp[t - 1][i - x] + costs[i - x]);
      }
    }

    return dp.back().back();
  }
};
