// Source: https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii
// Title: Divide an Array Into Subarrays With Minimum Cost II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array of integers `nums` of length `n`, and two **positive** integers `k` and `dist`.
//
// The **cost** of an array is the value of its **first** element. For example, the cost of `[1,2,3]` is `1` while the cost of `[3,4,1]` is `3`.
//
// You need to divide `nums` into `k` **disjoint contiguous subarrays**, such that the difference between the starting index of the **second** subarray and the starting index of the `kth` subarray should be **less than or equal to** `dist`. In other words, if you divide `nums` into the subarrays `nums[0..(i_1 - 1)], nums[i_1..(i_2 - 1)], ..., nums[i_k-1..(n - 1)]`, then `i_k-1 - i_1 <= dist`.
//
// A **subarray** is a contiguous **non-empty** sequence of elements within an array.
//
// Return the **minimum** possible sum of the cost of these subarrays.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
// Output: 5
// Explanation: The best possible way to divide nums into 3 subarrays is: [1,3], [2,6,4], and [2]. This choice is valid because i_k-1 - i_1 is 5 - 2 = 3 which is equal to dist. The total cost is nums[0] + nums[2] + nums[5] which is 1 + 2 + 2 = 5.
// It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 5.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
// Output: 15
// Explanation: The best possible way to divide nums into 4 subarrays is: [10], [1], [2], and [2,2,1]. This choice is valid because i_k-1 - i_1 is 3 - 1 = 2 which is less than dist. The total cost is nums[0] + nums[1] + nums[2] + nums[3] which is 10 + 1 + 2 + 2 = 15.
// The division [10], [1], [2,2,2], and [1] is not valid, because the difference between i_k-1 and i_1 is 5 - 1 = 4, which is greater than dist.
// It can be shown that there is no possible way to divide nums into 4 subarrays at a cost lower than 15.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [10,8,18,9], k = 3, dist = 1
// Output: 36
// Explanation: The best possible way to divide nums into 4 subarrays is: [10], [8], and [18,9]. This choice is valid because i_k-1 - i_1 is 2 - 1 = 1 which is equal to dist.The total cost is nums[0] + nums[1] + nums[2] which is 10 + 8 + 18 = 36.
// The division [10], [8,18], and [9] is not valid, because the difference between i_k-1 and i_1 is 3 - 1 = 2, which is greater than dist.
// It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 36.
// ```
//
// **Constraints:**
//
// - `3 <= n <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `3 <= k <= n`
// - `k - 2 <= dist <= n - 2`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

using namespace std;

// Sliding Window + Tree Set
//
// First we know that nums[0] must be chosen.
//
// Next put all nums[1~dist] (with their indices) into a set,
// and compute the sum of the smallest k-1 numbers.
//
// Next remove nums[1] and insert nums[i+dist+1], and compute the sum again.
// Repeat above algorithm for all numbers.
class Solution {
  using Item = pair<int, int>;  // num, idx;

 public:
  long long minimumCost(vector<int>& nums, int k, int dist) {
    int n = nums.size();

    // Helper
    auto sumK = [=](set<Item>& data, int k) -> int64_t {
      auto it = data.cbegin();
      int64_t sum = 0;
      for (auto i = 0; i < k; ++i) {
        sum += it->first;
        ++it;
      }
      return sum;
    };

    // Prepare
    auto data = set<Item>();
    for (auto idx = 1; idx <= dist + 1; ++idx) {
      data.insert({nums[idx], idx});
    }
    auto ans = sumK(data, k - 1);

    // Loop
    for (auto i = 1, j = dist + 2; j < n; ++i, ++j) {  // (i, j] is in the set
      data.erase({nums[i], i});
      data.insert({nums[j], j});
      ans = min(ans, sumK(data, k - 1));
    }

    return ans + nums[0];
  }
};

// Sliding Window + Tree Set
//
// First we know that nums[0] must be chosen.
//
// Now we focus on the rest k-1 numbers.
// Those numbers must be chosen from a range [i, i+dist].
// The main idea is to try all possible i.
//
// We use two tree set to track minimal k-1 numbers in the range.
class Solution2 {
  using Item = pair<int, int>;  // num, idx

  // Data structure for minimal k numbers.
  class Container {
    set<Item> lower, upper;  // size(lower) should always be k
    int k;
    int64_t sum;  // sum of minimal k numbers

   public:
    Container(int k) : k(k), sum(0) {}

    void insert(Item x) {
      if (!upper.empty() && x >= (*upper.cbegin())) {
        upper.insert(x);
      } else {
        lower.insert(x);
        sum += x.first;
      }
    }

    // We will only call this for existing x
    void remove(Item x) {
      if (upper.contains(x)) {
        upper.erase(x);
      } else {
        lower.erase(x);
        sum -= x.first;
      }
    }

    int64_t getSum() {
      // Ensure size(lower) == k
      while (lower.size() < k && !upper.empty()) {
        auto it = upper.begin();
        lower.insert(*it);
        sum += it->first;
        upper.erase(it);
      }

      while (lower.size() > k) {
        auto it = prev(lower.cend());
        upper.insert(*it);
        sum -= it->first;
        lower.erase(it);
      }

      return sum;
    }
  };

 public:
  long long minimumCost(vector<int>& nums, int k, int dist) {
    int n = nums.size();

    auto data = Container(k - 1);

    // Insert [1, dist+1]
    for (auto i = 1; i <= dist + 1; ++i) {
      data.insert({nums[i], i});
    }
    auto ans = data.getSum();

    // Loop
    for (auto i = 2, j = dist + 2; j < n; ++i, ++j) {  // [i, j]
      data.remove({nums[i - 1], i - 1});
      data.insert({nums[j], j});
      ans = min(ans, data.getSum());
    }

    return ans + nums[0];
  }
};
