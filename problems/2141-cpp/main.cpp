// Source: https://leetcode.com/problems/maximum-running-time-of-n-computers
// Title: Maximum Running Time of N Computers
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `n` computers. You are given the integer `n` and a **0-indexed** integer array `batteries` where the `i^th` battery can **run** a computer for `batteries[i]` minutes. You are interested in running **all** `n` computers **simultaneously** using the given batteries.
//
// Initially, you can insert **at most one battery** into each computer. After that and at any integer time moment, you can remove a battery from a computer and insert another battery **any number of times**. The inserted battery can be a totally new battery or a battery from another computer. You may assume that the removing and inserting processes take no time.
//
// Note that the batteries cannot be recharged.
//
// Return the **maximum** number of minutes you can run all the `n` computers simultaneously.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/01/06/example1-fit.png
//
// ```
// Input: n = 2, batteries = [3,3,3]
// Output: 4
// Explanation:
// Initially, insert battery 0 into the first computer and battery 1 into the second computer.
// After two minutes, remove battery 1 from the second computer and insert battery 2 instead. Note that battery 1 can still run for one minute.
// At the end of the third minute, battery 0 is drained, and you need to remove it from the first computer and insert battery 1 instead.
// By the end of the fourth minute, battery 1 is also drained, and the first computer is no longer running.
// We can run the two computers simultaneously for at most 4 minutes, so we return 4.
//
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/01/06/example2.png
//
// ```
// Input: n = 2, batteries = [1,1,1,1]
// Output: 2
// Explanation:
// Initially, insert battery 0 into the first computer and battery 2 into the second computer.
// After one minute, battery 0 and battery 2 are drained so you need to remove them and insert battery 1 into the first computer and battery 3 into the second computer.
// After another minute, battery 1 and battery 3 are also drained so the first and second computers are no longer running.
// We can run the two computers simultaneously for at most 2 minutes, so we return 2.
// ```
//
// **Constraints:**
//
// - `1 <= n <= batteries.length <= 10^5`
// - `1 <= batteries[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <functional>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// Greedy + Heap (TLE)
//
// It is always better to use battery with more power.
class Solution {
 public:
  long long maxRunTime(int n, vector<int>& batteries) {  //
    auto heap = priority_queue(less<int>(), batteries);  // max-heap

    // Loop
    auto ans = 0;
    auto tops = vector<int>(n);
    while (heap.size() >= n) {
      for (auto i = 0; i < n; ++i) {
        tops[i] = heap.top() - 1;
        heap.pop();
      }
      for (auto top : tops) {
        if (top > 0) heap.push(top);
      }
      ++ans;
    }

    return ans;
  }
};

// Binary Search
//
// For given time t, all battery greater than t are overpowered.
// We can only use t hours of them, so just assign each a computer.
//
// Now we claim the follows.
// Assume all batteries B[i] are less than t (i.e. B[i] <= t), and the sum are enough (i.e. Sum(B[i]) >= t*n),
// then we those batteries works.
//
// Prove of induction.
// Say we have m batteries. We have tm >= sum >= tn (i.e. m >= n).
// It is trivial for k = 1.
// Assume that t = k-1 works.
//
// For t = k, we have B[i] <= k and sum(B[i]) >= kn.
// We choose the top n battery and use them for an hour.
//
// Say B' is the batteries after the operation.
// We know that sum(B'[i]) = sum(B[i]) - n >= (k-1)n.
// So if B'[i] <= k-1 then this case works.
// Note that for top-n batteries, we have B'[i] = B[i]-1 <= k-1.
// Now we focus on the smaller batteries (i.e. B'[i] = B[i]).
//
// If there exist a battery j with B'[j] > k-1 (i.e. B'[j] = k).
// Note that if such battery exists, then all top-n batteries satisfies B[i] = k.
// Then in this case, these n batteries with k hours are enough for running the computers for k hours.
class Solution2 {
 public:
  int64_t maxRunTime(int n, vector<int>& batteries) {  //
    auto total = accumulate(batteries.cbegin(), batteries.cend(), int64_t(0));
    auto maxAns = total / n;

    // Helper
    // Check if the computer can run at least `t` hours.
    auto check = [&](int64_t t) -> bool {
      int64_t sum = 0;
      for (auto battery : batteries) {
        sum += min(int64_t(battery), t);
      }
      return sum >= t * n;
    };

    // Binary Search
    // Search in range [0, maxAns]
    // check(0) = true, check(maxAns+1) = false
    // check(lo-1) = true, check(hi=lo) = false
    int64_t lo = 1, hi = maxAns + 1;  // find in [1, hi)
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        lo = mid + 1;  // find in [mid+1, hi)
      } else {
        hi = mid;
      }
    }

    return lo - 1;
  }
};
