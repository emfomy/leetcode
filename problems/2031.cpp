// Source: https://leetcode.com/problems/count-subarrays-with-more-ones-than-zeros
// Title: Count Subarrays With More Ones Than Zeros
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary array `nums` containing only the integers `0` and `1`. Return the number of **subarrays** in nums that have **more** `1`'s than `0`'s. Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// A **subarray** is a contiguous sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [0,1,1,0,1]
// Output: 9
// Explanation:
// The subarrays of size 1 that have more ones than zeros are: [1], [1], [1]
// The subarrays of size 2 that have more ones than zeros are: [1,1]
// The subarrays of size 3 that have more ones than zeros are: [0,1,1], [1,1,0], [1,0,1]
// The subarrays of size 4 that have more ones than zeros are: [1,1,0,1]
// The subarrays of size 5 that have more ones than zeros are: [0,1,1,0,1]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0]
// Output: 0
// Explanation:
// No subarrays have more ones than zeros.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1]
// Output: 1
// Explanation:
// The subarrays of size 1 that have more ones than zeros are: [1]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= nums[i] <= 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum, TLE
//
// Let pre[i] = #ones - #zeros in [0, i).
// Next loop for all possible subarrays [i, j).
// If pre[j] - pre[i] > 0, then this subarrays has more ones.
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int subarraysWithMoreOnesThanZeroes(const vector<int>& nums) {
    const int n = nums.size();

    // Prefix sum
    auto pres = vector<int>(n + 1);
    for (int i = 0; i < n; ++i) {
      pres[i + 1] = pres[i] + (nums[i] ? 1 : -1);
    }

    // Subarrays
    int count = 0;
    for (int j = 1; j <= n; ++j) {
      for (int i = 0; i < j; ++i) {
        count = (count + (pres[j] - pres[i] > 0)) % modulo;
      }
    }

    return count;
  }
};

// Prefix Sum + Tree Set
//
// Let pre[i] = #ones - #zeros in [0, i).
// We store pre[i] in a tree set.
// Now count the valid subarrays [i, j) for each fixed j.
// We need to find the number of pre[i] < pre[j] with i < j.
//
// We do insert and count together with single pass.
// For each step j,
// we first compute the number elements less than pre[j] in the tree set;
// next we put pre[j] into the tree set.
//
// However, since C++'s tree set doesn't support lower bound count, we give up this approach.
class Solution2 {};

// Prefix Sum + Fenwick Tree
//
// Let pre[i] = #ones - #zeros in [0, i).
// Note that -n <= pre[i] <= n, where n = len(nums).
// We can create a Fenwick Tree with range [-n, n].
//
// Now follows the same approach as Tree Set's.
// We maps the value range of pre[i] to the index range of the Fenwick Tree.
class Solution3 {
  constexpr static int modulo = 1e9 + 7;

  struct FenwickTree {
    const int m;
    vector<int> tree;  // tree[i] = sum [i-lowbit(i), i)

    FenwickTree(int m) : m(m), tree(m + 1, 0) {}

    // O(log n); data[i] += delta
    void update(int idx, int delta) {
      for (int i = idx + 1; i <= m; i += (i & -i)) {
        tree[i] += delta;
      }
    }

    // O(log n); sum of [0, r)
    int query(int r) {
      int sum = 0;
      for (int i = r; i >= 1; i -= (i & -i)) {
        sum += tree[i];
      }
      return sum;
    }
  };

 public:
  int subarraysWithMoreOnesThanZeroes(const vector<int>& nums) {
    const int n = nums.size();
    auto tree = FenwickTree(2 * n + 1);  // [-n, n]

    // Loop
    int count = 0;
    int pre = n;          // shift n since the original range is [-n, n]
    tree.update(pre, 1);  // sum of [0, 0)
    for (int j = 0; j < n; ++j) {
      pre += (nums[j] ? 1 : -1);  // sum of [0, j]
      count = (count + tree.query(pre)) % modulo;
      tree.update(pre, 1);
    }

    return count;
  }
};

// Prefix Sum + Frequency Array
//
// Let pre[i] = #ones - #zeros in [0, i).
// Note that -n <= pre[i] <= n, where n = len(nums).
//
// Since pre[i] only increase or decrease by one in each step,
// we don't need O(log n) to find the count in above approaches.
//
// We store the frequency pre[i] in an array freq (i.e. the underlying data of Fenwick Tree).
// freq[k] = #(pre[i]=k), k in [-n, n].
// We store the count of the pre[i] values less than pre[j] in a variable,
// and use freq[k] to update it.
class Solution4 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int subarraysWithMoreOnesThanZeroes(const vector<int>& nums) {
    const int n = nums.size();
    auto freqs = vector<int>(2 * n + 1);  // [-n, n]

    // Loop
    int count = 0;
    int pre = n;       // shift n since the original range is [-n, n]
    ++freqs[pre];      // sum of [0, 0)
    int subcount = 0;  // number of pre[i] < current `pre`
    for (int j = 0; j < n; ++j) {
      if (nums[j] == 1) {
        subcount += freqs[pre++];
      } else {
        subcount -= freqs[--pre];
      }
      count = (count + subcount) % modulo;
      ++freqs[pre];
    }
    return count;
  }
};
