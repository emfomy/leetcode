// Source: https://leetcode.com/problems/sliding-window-maximum
// Title: Sliding Window Maximum
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of integers`nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.
//
// Return the max sliding window.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [3,3,5,5,6,7]
// Explanation:
// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       **3**
//  1 [3  -1  -3] 5  3  6  7       **3**
//  1  3 [-1  -3  5] 3  6  7      ** 5**
//  1  3  -1 [-3  5  3] 6  7       **5**
//  1  3  -1  -3 [5  3  6] 7       **6**
//  1  3  -1  -3  5 [3  6  7]      **7**
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1], k = 1
// Output: [1]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `-10^4 <= nums[i] <= 10^4`
// - `1 <= k <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Heap
class Solution {
 public:
  vector<int> maxSlidingWindow(const vector<int>& nums, const int k) {
    const int n = nums.size();

    auto heap = priority_queue<pair<int, int>>();  // (num, idx)
    auto ans = vector<int>();
    ans.reserve(n - k + 1);

    for (int i = 0; i < n; ++i) {
      heap.emplace(nums[i], i);

      if (i >= k - 1) {
        // Remove outdated number
        while (heap.top().second <= i - k) heap.pop();

        ans.push_back(heap.top().first);
      }
    }

    return ans;
  }
};

// Monotonic Queue
//
// Store index in the queue.
// The number must be increasing (from back to front) in the queue.
class Solution2 {
 public:
  vector<int> maxSlidingWindow(const vector<int>& nums, const int k) {
    const int n = nums.size();

    auto que = deque<int>();  // index
    auto ans = vector<int>();
    ans.reserve(n - k + 1);

    for (int i = 0; i < n; ++i) {
      // Remove useless data from back
      while (!que.empty() && nums[i] >= nums[que.back()]) que.pop_back();

      // Push index
      que.emplace_back(i);

      if (i >= k - 1) {
        // Remove outdated number
        while (que.front() <= i - k) que.pop_front();

        ans.push_back(nums[que.front()]);
      }
    }

    return ans;
  }
};
