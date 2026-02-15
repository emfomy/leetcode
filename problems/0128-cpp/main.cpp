// Source: https://leetcode.com/problems/longest-consecutive-sequence
// Title: Longest Consecutive Sequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in`O(n)`time.
//
// **Example 1:**
//
// ```
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is `[1, 2, 3, 4]`. Therefore its length is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,3,7,2,5,8,4,6,0,1]
// Output: 9
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,0,1,2]
// Output: 3
// ```
//
// **Constraints:**
//
// - `0 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Union-Find + Hash Map
//
// Use a hash map to assign a increment ID to each unique number.
// Use union find the find the maximum sequence.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;  // rank is faster, but we need size here.

    UnionFind(const int n) : parents(n), sizes(n, 1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    // Find parent of x
    int find(const int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    // Union x and y
    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure size(x) >= size(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into y
      sizes[x] += sizes[y];
      parents[y] = x;
    }
  };

 public:
  int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;

    // Assign each unique number an ID
    int n = 0;                               // number of unique numbers
    auto idMap = unordered_map<int, int>();  // number to ID
    idMap.reserve(nums.size());
    for (int num : nums) {
      if (!idMap.contains(num)) {
        idMap[num] = n++;
      }
    }

    // Union-find on unique numbers
    auto uf = UnionFind(n);
    for (auto [num, id] : idMap) {
      // Unite with next number
      if (idMap.contains(num + 1)) {
        uf.unite(id, idMap[num + 1]);
      }
    }

    // Find maximum group
    auto maxIt = max_element(uf.sizes.cbegin(), uf.sizes.cend());
    return *maxIt;  // uf.sizes is not empty
  }
};

// Hash Set
//
// Use a hash set to store the unique numbers.
// For each unique number x, if x-1 not exist (i.e. x is start of a sequence),
// we loop through x+1, x+2, ... to find the length of this sequence.
class Solution2 {
 public:
  int longestConsecutive(vector<int>& nums) {
    // Unique numbers
    const auto numSet = unordered_set(nums.cbegin(), nums.cend());

    // Find sequences
    int maxLen = 0;
    for (int num : numSet) {
      if (numSet.contains(num - 1)) continue;  // not start of a sequence

      // Find current length
      int currLen = 1;
      while (numSet.contains(num + currLen)) {
        ++currLen;
      }

      maxLen = max(maxLen, currLen);
    }

    return maxLen;
  }
};
