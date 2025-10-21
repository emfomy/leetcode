// Source: https://leetcode.com/problems/top-k-frequent-elements
// Title: Top K Frequent Elements
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in **any order**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1,2,2,3], k = 2
// Output: [1,2]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1], k = 1
// Output: [1]
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2
// Output: [1,2]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `-10^4 <= nums[i] <= 10^4`
// - `k` is in the range `[1, the number of unique elements in the array]`.
// - It is **guaranteed** that the answer is **unique**.
//
// **Follow up:** Your algorithm's time complexity must be better than `O(n log n)`, where n is the array's size.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Sort, (n log n)
class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    // Frequency
    auto freqMap = unordered_map<int, int>();
    for (auto num : nums) {
      ++freqMap[num];
    }

    // Sort frequency
    auto freqs = vector<pair<int, int>>();
    for (auto [num, freq] : freqMap) freqs.push_back({freq, num});
    sort(freqs.begin(), freqs.end(), greater<>());

    // Answer
    auto ans = vector<int>();
    for (auto i = 0; i < k; ++i) {
      ans.push_back(freqs[i].second);
    }

    return ans;
  }
};

// Heap, (n log k)
class Solution2 {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    // Frequency
    auto freqMap = unordered_map<int, int>();
    for (auto num : nums) {
      ++freqMap[num];
    }

    // Heap
    auto heap = priority_queue<pair<int, int>>();
    for (auto [num, freq] : freqMap) {
      heap.push({-freq, num});
      if (heap.size() > k) {
        heap.pop();
      }
    }

    // Answer
    auto ans = vector<int>();
    while (!heap.empty()) {
      ans.push_back(heap.top().second);
      heap.pop();
    }

    return ans;
  }
};
