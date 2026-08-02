// Source: https://leetcode.com/problems/maximize-active-section-with-trade-ii
// Title: Maximize Active Section with Trade II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary string `s` of length `n`, where:
//
// - `'1'` represents an **active** section.
// - `'0'` represents an **inactive** section.
//
// You can perform **at most one trade** to maximize the number of active sections in `s`. In a trade, you:
//
// - Convert a contiguous block of `'1'`s that is surrounded by `'0'`s to all `'0'`s.
// - Afterward, convert a contiguous block of `'0'`s that is surrounded by `'1'`s to all `'1'`s.
//
// Additionally, you are given a **2D array** `queries`, where `queries[i] = [l_i, r_i]` represents a <button>substring</button> `s[l_i...r_i]`.
//
// For each query, determine the **maximum** possible number of active sections in `s` after making the optimal trade on the substring `s[l_i...r_i]`.
//
// Return an array `answer`, where `answer[i]` is the result for `queries[i]`.
//
// **Note**
//
// - For each query, treat `s[l_i...r_i]` as if it is **augmented** with a `'1'` at both ends, forming `t = '1' + s[l_i...r_i] + '1'`. The augmented `'1'`s **do not** contribute to the final count.
// - The queries are independent of each other.
//
// **Example 1:**
//
// ```
// Input: s = "01", queries = [[0,1]]
// Output: [1]
// Explanation:
// Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "0100", queries = [[0,3],[0,2],[1,3],[2,3]]
// Output: [4,3,1,1]
// Explanation:
// - Query `[0, 3]` → Substring `"0100"` → Augmented to `"101001"`
//   Choose `"0100"`, convert `"0100"` → `"0000"` → `"1111"`.
//   The final string without augmentation is `"1111"`. The maximum number of active sections is 4.
// - Query `[0, 2]` → Substring `"010"` → Augmented to `"10101"`
//   Choose `"010"`, convert `"010"` → `"000"` → `"111"`.
//   The final string without augmentation is `"1110"`. The maximum number of active sections is 3.
// - Query `[1, 3]` → Substring `"100"` → Augmented to `"11001"`
//   Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
// - Query `[2, 3]` → Substring `"00"` → Augmented to `"1001"`
//   Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "1000100", queries = [[1,5],[0,6],[0,4]]
// Output: [6,7,2]
// Explanation:
// - Query `[1, 5]` → Substring `"00010"` → Augmented to `"1000101"`
//   Choose `"00010"`, convert `"00010"` → `"00000"` → `"11111"`.
//   The final string without augmentation is `"1111110"`. The maximum number of active sections is 6.
// - Query `[0, 6]` → Substring `"1000100"` → Augmented to `"110001001"`
//   Choose `"000100"`, convert `"000100"` → `"000000"` → `"111111"`.
//   The final string without augmentation is `"1111111"`. The maximum number of active sections is 7.
// - Query `[0, 4]` → Substring `"10001"` → Augmented to `"1100011"`
//   Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 2.
// ```
//
// **Example 4:**
//
// ```
// Input: s = "01010", queries = [[0,3],[1,4],[1,3]]
// Output: [4,4,2]
// Explanation:
// - Query `[0, 3]` → Substring `"0101"` → Augmented to `"101011"`
//   Choose `"010"`, convert `"010"` → `"000"` → `"111"`.
//   The final string without augmentation is `"11110"`. The maximum number of active sections is 4.
// - Query `[1, 4]` → Substring `"1010"` → Augmented to `"110101"`
//   Choose `"010"`, convert `"010"` → `"000"` → `"111"`.
//   The final string without augmentation is `"01111"`. The maximum number of active sections is 4.
// - Query `[1, 3]` → Substring `"101"` → Augmented to `"11011"`
//   Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 2.
// ```
//
// **Constraints:**
//
// - `1 <= n == s.length <= 10^5`
// - `1 <= queries.length <= 10^5`
// - `s[i]` is either `'0'` or `'1'`.
// - `queries[i] = [l_i, r_i]`
// - `0 <= l_i <= r_i < n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sliding Window + Segment Tree
//
// First count the number of ones.
// Next convert the string into blocks.
//
// For each query, we need to find the maximum sum of any two contiguous blocks in the query range.
// To do so, we use a Segment tree to store the these sums by the starting index.
//
// For each query [l, r],
// we first find the sum that is fully contained by the range.
// Next, we compute the sum with left block overlapped by l (if existed).
// Do the same for the sum with right block overlapped by r (if existed).
// The maximum sum if the max of above three values.
class Solution {
  class SegmentTree {
    int n;
    vector<int> tree;  // parent i -> child 2i & 2i+1

   public:
    // Build: O(N)
    SegmentTree(const vector<int>& nums) {
      n = nums.size();
      tree.resize(2 * n);  // only need 2n for iteration version

      for (int i = 0; i < n; ++i) tree[i + n] = nums[i];  // leaves
      for (int i = n - 1; i >= 1; --i) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }

    // Query: O(logN); Max in [l, r)
    int query(int l, int r) const {
      int val = 0;
      for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) val = max(val, tree[l++]);  // l is odd, should add tree[l]; then move l
        if (r & 1) val = max(val, tree[--r]);  // r is odd, should add tree[r-1]; then move r
      }
      return val;
    }
  };

 public:
  vector<int> maxActiveSectionsAfterTrade(const string& s, const vector<vector<int>>& queries) {
    const int n = s.size();

    // Total ones
    int ones = count(s.cbegin(), s.cend(), '1');

    // Convert to block
    auto begins = vector<int>();  // begin of each 0-blocks
    auto ends = vector<int>();    // end of each 0-blocks
    auto pairs = vector<int>();   // sum of contiguous pairs
    pairs.reserve(s.size());
    begins.reserve(s.size());
    ends.reserve(s.size());

    int prevBlock = 0;
    auto it0 = find(s.cbegin(), s.cend(), '0');  // find first 0
    while (it0 != s.cend()) {
      auto it1 = find(it0, s.cend(), '1');  // find next 1
      begins.push_back(it0 - s.begin());
      ends.push_back(it1 - s.begin());

      int currBlock = it1 - it0;
      if (prevBlock > 0) {  // previous block exist
        pairs.push_back(prevBlock + currBlock);
      }
      prevBlock = currBlock;

      it0 = find(it1, s.cend(), '0');  // find next 0
    }
    const int m = begins.size();

    // Segment Tree
    auto tree = SegmentTree(pairs);

    // Loop
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      const int l = query[0], r = query[1] + 1;  // [l, r)

      // Find contiguous sum
      int maxZeros = 0;
      int lIdx = lower_bound(begins.cbegin(), begins.cend(), l) - begins.cbegin();  // first block after l
      int rIdx = upper_bound(ends.cbegin(), ends.cend(), r) - ends.cbegin();        // last block before r
      if (lIdx < m && rIdx > 0) {
        maxZeros = tree.query(lIdx, rIdx - 1);
      }

      // Check if previous block is overlapped
      if (lIdx > 0 && lIdx < m) {
        int lSize = ends[lIdx - 1] - l;
        int rSize = min(r, ends[lIdx]) - begins[lIdx];
        if (lSize > 0 && rSize > 0) {
          maxZeros = max(maxZeros, lSize + rSize);
        }
      }

      // Check if next block is overlapped
      if (rIdx > 0 && rIdx < m && rIdx - 1 >= lIdx) {
        int lSize = ends[rIdx - 1] - max(l, begins[rIdx - 1]);
        int rSize = r - begins[rIdx];
        if (lSize > 0 && rSize > 0) {
          maxZeros = max(maxZeros, lSize + rSize);
        }
      }

      ans.push_back(ones + maxZeros);
    }

    return ans;
  }
};
