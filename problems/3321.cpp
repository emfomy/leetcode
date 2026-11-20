// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii
// Title: Find X-Sum of All K-Long Subarrays II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` of `n` integers and two integers `k` and `x`.
//
// The **x-sum** of an array is calculated by the following procedure:
//
// - Count the occurrences of all elements in the array.
// - Keep only the occurrences of the top `x` most frequent elements. If two elements have the same number of occurrences, the element with the **bigger** value is considered more frequent.
// - Calculate the sum of the resulting array.
//
// **Note** that if an array has less than `x` distinct elements, its **x-sum** is the sum of the array.
//
// Return an integer array `answer` of length `n - k + 1` where `answer[i]` is the **x-sum** of the <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1s:" data-state="closed" class="">subarray</button> `nums[i..i + k - 1]`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
// Output: [6,10,12]
// Explanation:
// - For subarray `[1, 1, 2, 2, 3, 4]`, only elements 1 and 2 will be kept in the resulting array. Hence, `answer[0] = 1 + 1 + 2 + 2`.
// - For subarray `[1, 2, 2, 3, 4, 2]`, only elements 2 and 4 will be kept in the resulting array. Hence, `answer[1] = 2 + 2 + 2 + 4`. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// - For subarray `[2, 2, 3, 4, 2, 3]`, only elements 2 and 3 are kept in the resulting array. Hence, `answer[2] = 2 + 2 + 2 + 3 + 3`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,8,7,8,7,5], k = 2, x = 2
// Output: [11,15,15,15,12]
// Explanation:
// Since `k == x`, `answer[i]` is equal to the sum of the subarray `nums[i..i + k - 1]`.
// ```
//
// **Constraints:**
//
// - `nums.length == n`
// - `1 <= n <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `1 <= x <= k <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// Sliding Window + Set
//
// Use two sets, one for the top x common numbers, another for the less common numbers.
class Solution {
 public:
  vector<long long> findXSum(vector<int>& nums, int k, int x) {
    int n = nums.size();

    auto sum = 0LL;

    auto freqMap = unordered_map<int, int>();  // num -> freq
    auto largeSet = set<pair<int, int>>();     // (freq, num)
    auto smallSet = set<pair<int, int>>();     // (freq, num)

    // Internal Helper
    auto internalInsert = [&](const pair<int, int> p) {
      if (largeSet.size() < x || p > *largeSet.cbegin()) {
        sum += static_cast<long long>(p.first) * p.second;
        largeSet.insert(p);

        if (largeSet.size() > x) {
          auto it = largeSet.cbegin();
          sum -= static_cast<long long>(it->first) * it->second;
          smallSet.insert(*it);
          largeSet.erase(it);
        }
      } else {
        smallSet.insert(p);
      }
    };

    auto internalRemove = [&](const pair<int, int> p) {
      if (p >= *largeSet.cbegin()) {
        sum -= static_cast<long long>(p.first) * p.second;
        largeSet.erase(p);

        if (!smallSet.empty()) {
          auto it = smallSet.crbegin();
          sum += static_cast<long long>(it->first) * it->second;
          largeSet.insert(*it);
          smallSet.erase(*it);
        }
      } else {
        smallSet.erase(p);
      }
    };

    // Main Helper
    auto insert = [&](int num) {
      if (freqMap[num]) internalRemove({freqMap[num], num});
      ++freqMap[num];
      internalInsert({freqMap[num], num});
    };

    auto remove = [&](int num) {
      internalRemove({freqMap[num], num});
      --freqMap[num];
      if (freqMap[num]) internalInsert({freqMap[num], num});
    };

    // Loop
    auto ans = vector<long long>();
    for (auto i = 0; i < n; ++i) {
      insert(nums[i]);
      if (i >= k) remove(nums[i - k]);
      if (i >= k - 1) ans.push_back(sum);
    }

    return ans;
  }
};
