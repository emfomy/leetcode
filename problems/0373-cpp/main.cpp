// Source: https://leetcode.com/problems/find-k-pairs-with-smallest-sums
// Title: Find K Pairs with Smallest Sums
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integer arrays `nums1` and `nums2` sorted in **non-decreasingorder** and an integer `k`.
//
// Define a pair `(u, v)` which consists of one element from the first array and one element from the second array.
//
// Return the `k` pairs `(u_1, v_1), (u_2, v_2), ..., (u_k, v_k)` with the smallest sums.
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
// Output: [[1,2],[1,4],[1,6]]
// Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
// Output: [[1,1],[1,1]]
// Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
// ```
//
// **Constraints:**
//
// - `1 <= nums1.length, nums2.length <= 10^5`
// - `-10^9 <= nums1[i], nums2[i] <= 10^9`
// - `nums1` and `nums2` both are sorted in **non-decreasing order**.
// - `1 <= k <= 10^4`
// - `k <=nums1.length *nums2.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Use Heap
//
// Put all pair with numbers from nums1 with the first number from nums2.
// For each loop, pop the minimal pair, the push the pair with the next number for nums2.
//
// Note that if n1 > n2, we can swap them to speed up.
class Solution {
 public:
  vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    int n1 = nums1.size(), n2 = nums2.size();

    // Assume k >= n1
    // We only need k pairs
    if (n1 > k) {
      n1 = k;
    }

    // Prepare data
    auto data = vector<tuple<int, int, int>>();  //(sum, idx1, idx2)
    for (auto idx1 = 0; idx1 < n1; ++idx1) {
      data.emplace_back(nums1[idx1] + nums2[0], idx1, 0);
    }

    // Queue
    auto pq = priority_queue(greater(), std::move(data));  // min-heap
    auto ans = vector<vector<int>>();
    for (auto i = 0; i < k; ++i) {
      auto [sum, idx1, idx2] = pq.top();
      pq.pop();
      ans.push_back({nums1[idx1], nums2[idx2]});

      idx2++;
      if (idx2 >= n2) continue;
      pq.push({nums1[idx1] + nums2[idx2], idx1, idx2});
    }

    return ans;
  }
};
