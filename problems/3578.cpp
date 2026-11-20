// Source: https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k
// Title: Count Partitions With Max-Min Difference at Most K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `k`. Your task is to partition `nums` into one or more **non-empty** contiguous segments such that in each segment, the difference between its **maximum** and **minimum** elements is **at most** `k`.
//
// Return the total number of ways to partition `nums` under this condition.
//
// Since the answer may be too large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: nums = [9,4,1,3,7], k = 4
// Output: 6
// Explanation:
// There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most `k = 4`:
// - `[[9], [4], [1], [3], [7]]`
// - `[[9], [4], [1], [3, 7]]`
// - `[[9], [4], [1, 3], [7]]`
// - `[[9], [4, 1], [3], [7]]`
// - `[[9], [4, 1], [3, 7]]`
// - `[[9], [4, 1, 3], [7]]`
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,3,4], k = 0
// Output: 2
// Explanation:
// There are 2 valid partitions that satisfy the given conditions:
// - `[[3], [3], [4]]`
// - `[[3, 3], [4]]`
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 5 * 10^4`
// - `1 <= nums[i] <= 10^9`
// - `0 <= k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// DP (TLE)
//
// DP[i] is the total number of ways to partition [0:i]
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();

    // DP
    auto dp = vector<int>(n + 1);
    dp[n] = 1;

    for (auto i = n - 1; i >= 0; --i) {
      auto minVal = nums[i], maxVal = nums[i];
      for (auto j = i; j < n; ++j) {
        minVal = min(minVal, nums[j]);
        maxVal = max(maxVal, nums[j]);
        if (maxVal - minVal > k) break;
        dp[i] = (dp[i] + dp[j + 1]) % modulo;  // [j:i] as a segment
      }
    }

    return dp[0];
  }
};
// DP + Multi Set
//
// DP[i] is the total number of ways to partition [0:i]
//
// We know that if [i:j] is a valid segment, all  [>i,j] are also valid.
// Let l be the left pointer, indicate that [k:i] is valid. (If not, move k).
// We also track the sum of all DP in [k:i].
//
// Use multi-set to store the values in the segment.
class Solution2 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();

    auto dp = vector<int>(n + 1);
    auto data = multiset<int>();

    dp[n] = 1;
    auto sum = 1, r = n - 1;

    for (auto i = n - 1; i >= 0; --i) {
      auto num = nums[i];
      data.insert(num);

      while (r > i && *(--data.end()) - *(data.begin()) > k) {
        sum = (sum - dp[r + 1] + modulo) % modulo;
        data.erase(data.find(nums[r]));
        --r;
      }

      dp[i] = sum;
      sum = (sum + dp[i]) % modulo;
    }

    return dp[0];
  }
};

// DP + Heap
//
// DP[i] is the total number of ways to partition [0:i]
//
// We know that if [i:j] is a valid segment, all  [>i,j] are also valid.
// Let l be the left pointer, indicate that [k:i] is valid. (If not, move k).
// We also track the sum of all DP in [k:i].
//
// Use max-heap and min-heap to store the values in the segment.
class Solution3 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();

    auto dp = vector<int>(n + 1);
    auto maxQ = priority_queue(less(), vector<pair<int, int>>());     // (val, idx)
    auto minQ = priority_queue(greater(), vector<pair<int, int>>());  // (val, idx)

    dp[n] = 1;
    auto sum = 1, r = n - 1;

    for (auto i = n - 1; i >= 0; --i) {
      auto num = nums[i];
      maxQ.push({num, i});
      minQ.push({num, i});

      while (maxQ.top().first - minQ.top().first > k) {
        sum = (sum - dp[r + 1] + modulo) % modulo;
        --r;
        while (maxQ.top().second > r) maxQ.pop();
        while (minQ.top().second > r) minQ.pop();
      }

      dp[i] = sum;
      sum = (sum + dp[i]) % modulo;
    }

    return dp[0];
  }
};

// DP + Monotonic Queue
//
// DP[i] is the total number of ways to partition [0:i]
//
// We know that if [i:j] is a valid segment, all  [>i,j] are also valid.
// Let l be the left pointer, indicate that [k:i] is valid. (If not, move k).
// We also track the sum of all DP in [k:i].
//
// Use max-queue and min-queue to store the values in the segment.
class Solution4 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();

    auto dp = vector<int>(n + 1);
    auto maxQ = deque<pair<int, int>>();  // (val, idx), decreasing
    auto minQ = deque<pair<int, int>>();  // (val, idx), increasing

    dp[n] = 1;
    auto sum = 1, r = n - 1;

    for (auto i = n - 1; i >= 0; --i) {
      auto num = nums[i];
      while (!maxQ.empty() && maxQ.back().first < num) maxQ.pop_back();
      while (!minQ.empty() && minQ.back().first > num) minQ.pop_back();
      maxQ.push_back({num, i});
      minQ.push_back({num, i});

      while (maxQ.front().first - minQ.front().first > k) {
        sum = (sum - dp[r + 1] + modulo) % modulo;
        --r;
        while (maxQ.front().second > r) maxQ.pop_front();
        while (minQ.front().second > r) minQ.pop_front();
      }

      dp[i] = sum;
      sum = (sum + dp[i]) % modulo;
    }

    return dp[0];
  }
};

// DP + Monotonic Queue
//
// DP[i] is the total number of ways to partition [0:i]
//
// We know that if [i:j] is a valid segment, all  [>i,j] are also valid.
// Let l be the left pointer, indicate that [k:i] is valid. (If not, move k).
// We also track the sum of all DP in [k:i].
//
// Use max-queue and min-queue to store the values in the segment.
class Solution5 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countPartitions(vector<int>& nums, int k) {
    int n = nums.size();

    auto dp = vector<int>(n + 1);
    auto maxQ = deque<int>();  // idx, nums[i] decreasing
    auto minQ = deque<int>();  // idx, nums[i] increasing

    dp[n] = 1;
    auto sum = 1, r = n - 1;

    for (auto i = n - 1; i >= 0; --i) {
      auto num = nums[i];
      while (!maxQ.empty() && nums[maxQ.back()] < num) maxQ.pop_back();
      while (!minQ.empty() && nums[minQ.back()] > num) minQ.pop_back();
      maxQ.push_back(i);
      minQ.push_back(i);

      while (nums[maxQ.front()] - nums[minQ.front()] > k) {
        sum = (sum - dp[r + 1] + modulo) % modulo;
        --r;
        while (maxQ.front() > r) maxQ.pop_front();
        while (minQ.front() > r) minQ.pop_front();
      }

      dp[i] = sum;
      sum = (sum + dp[i]) % modulo;
    }

    return dp[0];
  }
};
