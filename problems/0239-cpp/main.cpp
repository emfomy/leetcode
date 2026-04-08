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
#include <set>
#include <vector>

using namespace std;

// Sliding Window + Tree Set
//
// Store the numbers in the window in the tree set.
class Solution {
  using Data = pair<int, int>;  // number, index

 public:
  vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Prepare data
    auto ans = vector<int>();
    ans.reserve(n - k + 1);
    auto window = set<Data>();

    // Loop
    for (int i = 0; i < n; ++i) {
      window.insert(Data{nums[i], i});
      if (i >= k) {  // window size > k
        window.erase(Data{nums[i - k], i - k});
      }
      if (i >= k - 1) {  // window size == k
        ans.push_back(window.crbegin()->first);
      }
    }

    return ans;
  }
};

// Sliding Window + Heap
//
// Store the numbers in the window in the heap.
// We remove the element lazily.
class Solution2 {
  using Data = pair<int, int>;        // number, index
  using Heap = priority_queue<Data>;  // max-heap

 public:
  vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Prepare data
    auto ans = vector<int>();
    ans.reserve(n - k + 1);
    Heap window;

    // Loop
    for (int i = 0; i < n; ++i) {
      window.push(Data{nums[i], i});

      // window size < k
      if (i < k - 1) {
        continue;
      }

      // Remove outdated element
      while (window.top().second <= i - k) window.pop();

      // Get largest
      ans.push_back(window.top().first);
    }

    return ans;
  }
};

// Sliding Window + Monotonic Queue
//
// Store the numbers in the window in the monotonic queue.
// The front is the largest, and the back is the smallest.
class Solution3 {
 public:
  vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Prepare data
    auto ans = vector<int>();
    ans.reserve(n - k + 1);
    auto window = deque<int>();  // indices

    // Loop
    for (int i = 0; i < n; ++i) {
      // Maintain decreasing
      while (!window.empty() && nums[window.back()] < nums[i]) window.pop_back();
      window.push_back(i);

      // window size < k
      if (i < k - 1) {
        continue;
      }

      // Remove outdated element
      if (window.front() <= i - k) window.pop_front();

      // Get largest
      ans.push_back(nums[window.front()]);
    }

    return ans;
  }
};
