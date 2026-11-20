// Source: https://leetcode.com/problems/sorted-gcd-pair-queries
// Title: Sorted GCD Pair Queries
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n` and an integer array `queries`.
//
// Let `gcdPairs` denote an array obtained by calculating the <button>GCD</button> of all possible pairs `(nums[i], nums[j])`, where `0 <= i < j < n`, and then sorting these values in **ascending** order.
//
// For each query `queries[i]`, you need to find the element at index `queries[i]` in `gcdPairs`.
//
// Return an integer array `answer`, where `answer[i]` is the value at `gcdPairs[queries[i]]` for each query.
//
// The term `gcd(a, b)` denotes the **greatest common divisor** of `a` and `b`.
//
// **Example 1:**
//
// ```
// Input: nums = [2,3,4], queries = [0,2,2]
// Output: [1,2,2]
// Explanation:
// `gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1]`.
// After sorting in ascending order, `gcdPairs = [1, 1, 2]`.
// So, the answer is `[gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,4,2,1], queries = [5,3,1,0]
// Output: [4,2,1,1]
// Explanation:
// `gcdPairs` sorted in ascending order is `[1, 1, 1, 2, 2, 4]`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [2,2], queries = [0,0]
// Output: [2,2]
// Explanation:
// `gcdPairs = [2]`.
// ```
//
// **Constraints:**
//
// - `2 <= n == nums.length <= 10^5`
// - `1 <= nums[i] <= 5 * 10^4`
// - `1 <= queries.length <= 10^5`
// - `0 <= queries[i] < n * (n - 1) / 2`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Inclusion-Exclusion Principle + Prefix Sum
//
// Let n be the length, and m be the maximum number.
//
// Brute-force is not possible since n^2 is too large.
// However, since gcd(a, b) <= min(a, b), the range of GCD is [1, m].
// Therefore, we can instead count the number of pairs for each GCD value.
//
// Let g be the GCD value we want to count.
// We count the number of numbers that is divisible by g.
// The GCD of the pairs from them are at least g.
//
// However, it is not "exact" g since the GCD may be 2g, 3g, etc.
// Therefore, we do the process from large to small,
// and substract the pairs of multiple of g.
class Solution {
 public:
  vector<int> gcdValues(const vector<int>& nums, const vector<long long>& queries) {
    const int n = nums.size();
    const int m = *max_element(nums.cbegin(), nums.end());
    vector<long long> cnts(m + 1);

    // cnts[a]: # of a
    for (int num : nums) {
      ++cnts[num];
    }

    // cnts[a]: # of multiple of a
    for (int i = 1; i <= m; ++i) {
      for (int j = i * 2; j <= m; j += i) {
        cnts[i] += cnts[j];
      }
    }

    // cnts[a]: # of pairs where gcd is multiple of a
    for (int i = 1; i <= m; ++i) {
      cnts[i] = cnts[i] * (cnts[i] - 1) / 2;
    }

    // cnts[a]: # of pairs where gcd is exact a
    for (int i = m; i >= 1; --i) {
      for (int j = i * 2; j <= m; j += i) {
        cnts[i] -= cnts[j];
      }
    }

    // Prefix Sum
    for (int i = 1; i <= m; ++i) {
      cnts[i] += cnts[i - 1];
    }

    // Query
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (long long query : queries) {
      ++query;  // 1-indexing
      int pos = lower_bound(cnts.cbegin(), cnts.cend(), query) - cnts.cbegin();
      ans.push_back(pos);
    }

    return ans;
  }
};
