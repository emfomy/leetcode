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

#include <deque>
#include <queue>
#include <vector>

using namespace std;

// Monotonic Queue
class Solution {
  class MonotonicQueue {
    queue<int> que;
    deque<int> inc;   // increasing values
    deque<int> desc;  // decreasing values

   public:
    void push(int val) {  //
      que.push(val);

      while (!inc.empty() && inc.back() > val) inc.pop_back();
      inc.push_back(val);

      while (!desc.empty() && desc.back() < val) desc.pop_back();
      desc.push_back(val);
    }

    void pop() {  //
      auto front = que.front();
      que.pop();
      if (inc.front() == front) inc.pop_front();
      if (desc.front() == front) desc.pop_front();
    }

    int min() {  //
      return inc.front();
    }

    int max() {  //
      return desc.front();
    }

    int front() {  //
      return que.front();
    }

    int back() {  //
      return que.back();
    }

    int size() {  //
      return que.size();
    }
  };

 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    auto window = MonotonicQueue();

    auto ans = vector<int>();
    for (auto num : nums) {
      window.push(num);
      if (window.size() == k) {
        ans.push_back(window.max());
        window.pop();
      }
    }

    return ans;
  }
};
