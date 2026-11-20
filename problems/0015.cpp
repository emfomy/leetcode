// Source: https://leetcode.com/problems/3sum
// Title: 3Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.
//
// Notice that the solution set must not contain duplicate triplets.
//
// **Example 1:**
//
// ```
// Input: nums = [-1,0,1,2,-1,-4]
// Output: [[-1,-1,2],[-1,0,1]]
// Explanation:
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
// The distinct triplets are [-1,0,1] and [-1,-1,2].
// Notice that the order of the output and the order of the triplets does not matter.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,1,1]
// Output: []
// Explanation: The only possible triplet does not sum up to 0.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [0,0,0]
// Output: [[0,0,0]]
// Explanation: The only possible triplet sums up to 0.
// ```
//
// **Constraints:**
//
// - `3 <= nums.length <= 3000`
// - `-10^5 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

// Use sort & hashmap
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    auto n = nums.size();
    sort(nums.begin(), nums.end());

    unordered_set<int> num_set;
    set<tuple<int, int, int>> ans_set;
    vector<vector<int>> ans;

    for (auto i = 0; i < n; i++) {
      auto numI = nums[i];
      for (auto j = i + 1; j < n; j++) {
        auto numJ = nums[j];
        auto numK = -numI - numJ;
        if (num_set.count(numK) > 0) {
          if (ans_set.count({numK, numI, numJ}) == 0) {
            ans_set.insert({numK, numI, numJ});
            ans.push_back({numK, numI, numJ});
          }
        }
      }
      num_set.insert(numI);
    }

    return ans;
  }
};

// Use sort & hashmap
class Solution2 {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    auto n = nums.size();
    sort(nums.begin(), nums.end());

    // Count numbers
    unordered_map<int, int> counter;
    for (auto num : nums) {
      counter[num]++;
    }

    // Find answer, i < j < k
    vector<vector<int>> ans;
    for (auto i = 0; i < n; i++) {
      auto numI = nums[i];
      if (numI > 0) {  // no more answer
        break;
      }
      if (i > 0 && nums[i - 1] == numI) {  // skip duplication
        continue;
      }

      for (auto j = i + 1; j < n; j++) {
        auto numJ = nums[j];
        if (nums[j - 1] == numJ) {  // skip duplication
          continue;
        }

        auto numK = -numI - numJ;
        if (numK <= numJ) {  // no more answer
          break;
        }
        if (counter[numK] > 0) {
          ans.push_back({numI, numJ, numK});
        }
      }
    }

    // Find answer, i = j != k
    for (auto i = 0; i < n; i++) {
      auto numI = nums[i];
      if (i > 0 && nums[i - 1] == numI) {  // skip duplication
        continue;
      }
      if (counter[numI] <= 1) {
        continue;
      }

      auto numK = -2 * numI;
      if (numK == numI) {
        continue;
      }
      if (counter[numK] > 0) {
        ans.push_back({numI, numI, numK});
      }
    }

    // Find answer i = j = k (i.e. all zero)
    if (counter[0] >= 3) {
      ans.push_back({0, 0, 0});
    }

    return ans;
  }
};

// Use sort & two pointer
//
// Keep i < j < k.
// Loop i, use two pointer to find j & k.
class Solution3 {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    auto n = nums.size();
    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;
    auto i = 0;
    while (i < n) {
      auto numI = nums[i];
      if (numI > 0) {  // no more answer
        break;
      }

      // Two pointer
      auto j = i + 1;
      auto k = n - 1;
      while (j < k) {
        auto numJ = nums[j];
        auto numK = nums[k];

        auto sum = numI + numJ + numK;
        if (sum == 0) {
          ans.push_back({numI, numJ, numK});
          j++;
          k--;
          while (j < k && nums[j] == numJ) {
            j++;
          }
          while (j < k && nums[k] == numK) {
            k--;
          }
          continue;
        }

        if (sum < 0) {
          j++;
        } else {
          k--;
        }
      }

      i++;
      while (i < n && nums[i] == numI) {
        i++;
      }
    }

    return ans;
  }
};
