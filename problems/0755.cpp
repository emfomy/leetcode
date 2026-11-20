// Source: https://leetcode.com/problems/pour-water
// Title: Pour Water
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an elevation map represents as an integer array `heights` where `heights[i]` representing the height of the terrain at index `i`. The width at each index is `1`. You are also given two integers `volume` and `k`. `volume` units of water will fall at index `k`.
//
// Water first drops at the index `k` and rests on top of the highest terrain or water at that index. Then, it flows according to the following rules:
//
// - If the droplet would eventually fall by moving left, then move left.
// - Otherwise, if the droplet would eventually fall by moving right, then move right.
// - Otherwise, rise to its current position.
//
// Here, **"eventually fall"** means that the droplet will eventually be at a lower level if it moves in that direction. Also, level means the height of the terrain plus any water in that column.
//
// We can assume there is infinitely high terrain on the two sides out of bounds of the array. Also, there could not be partial water being spread out evenly on more than one grid block, and each unit of water has to be in exactly one block.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/06/12/pour11-grid.jpg
//
// ```
// Input: heights = [2,1,1,2,1,2,2], volume = 4, k = 3
// Output: [2,2,2,3,2,2,2]
// Explanation:
// The first drop of water lands at index k = 3. When moving left or right, the water can only move to the same level or a lower level. (By level, we mean the total height of the terrain plus any water in that column.)
// Since moving left will eventually make it fall, it moves left. (A droplet "made to fall" means go to a lower height than it was at previously.) Since moving left will not make it fall, it stays in place.
// https://assets.leetcode.com/uploads/2021/06/12/pour12-grid.jpg
// The next droplet falls at index k = 3. Since the new droplet moving left will eventually make it fall, it moves left. Notice that the droplet still preferred to move left, even though it could move right (and moving right makes it fall quicker.)
// https://assets.leetcode.com/uploads/2021/06/12/pour13-grid.jpg
// The third droplet falls at index k = 3. Since moving left would not eventually make it fall, it tries to move right. Since moving right would eventually make it fall, it moves right.
// https://assets.leetcode.com/uploads/2021/06/12/pour14-grid.jpg
// Finally, the fourth droplet falls at index k = 3. Since moving left would not eventually make it fall, it tries to move right. Since moving right would not eventually make it fall, it stays in place.
// https://assets.leetcode.com/uploads/2021/06/12/pour15-grid.jpg
// ```
//
// **Example 2:**
//
// ```
// Input: heights = [1,2,3,4], volume = 2, k = 2
// Output: [2,3,3,4]
// Explanation: The last droplet settles at index 1, since moving further left would not cause it to eventually fall to a lower height.
// ```
//
// **Example 3:**
//
// ```
// Input: heights = [3,1,3], volume = 5, k = 1
// Output: [4,4,4]
// ```
//
// **Constraints:**
//
// - `1 <= heights.length <= 100`
// - `0 <= heights[i] <= 99`
// - `0 <= volume <= 2000`
// - `0 <= k < heights.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

using namespace std;

// Simulation
class Solution {
 public:
  vector<int> pourWater(vector<int>& heights, int volume, int k) {
    const int n = heights.size();

    // Loop
    for (; volume > 0; --volume) {
      // Move left
      {
        int minH = heights[k];  // current min height
        int minI = k;           // current min index
        for (int i = k - 1; i >= 0; --i) {
          if (heights[i] > minH) break;  // can't go up
          if (heights[i] < minH) {
            minI = i;
            minH = heights[i];
          }
        }
        if (minI < k) {
          ++heights[minI];
          continue;
        }
      }

      // Move right
      {
        int minH = heights[k];  // current min height
        int minI = k;           // current min index
        for (int i = k + 1; i < n; ++i) {
          if (heights[i] > minH) break;  // can't go up
          if (heights[i] < minH) {
            minI = i;
            minH = heights[i];
          }
        }
        if (minI > k) {
          ++heights[minI];
          continue;
        }
      }

      // Can't move
      ++heights[k];
    }

    return heights;
  }
};

// Two Pointer + Stack
//
// The water will fall left if the terrain to the left is decreasing.
// Let L (left boundary) be the first index that is increasing.
// The water will not fall pass this point.
//
// Use a stack for the dropping indices from left to right.
// Let i be an index in the stack,
// we have H[i] < H[i+1] and L < i
//
// For each drop, pick the leftmost index in the stack (say i) and update H[i]++.
// After the update, we need to update the stack.
// If H[i] < H[i+1], keep this index; otherwise, pop from the stack.
// If H[i-1] < H[i], push i-1 into the stack.
// If L = i-1, then we need the update L.
// We traverse left to add more index into the stack.
//
// Here is the invariant:
// H[L] > H[L+1] = ... = H[i0] < H[i0+1] = ... = H[i1] < H[i1+1] = ... <= H[k]
//
// The right side is similar.
class Solution2 {
 public:
  vector<int> pourWater(vector<int>& heights, int volume, int k) {
    const int n = heights.size();

    // Prepare
    auto lStack = stack<int>(), rStack = stack<int>();
    int l = k - 1, r = k + 1;

    // Loop
    for (; volume > 0; --volume) {
      // Update left boundary
      for (; l >= 0; --l) {
        // Check boundary
        if (heights[l] > heights[l + 1]) break;

        // Check drop
        if (heights[l] < heights[l + 1]) lStack.push(l);
      }

      // Update right boundary
      for (; r < n; ++r) {
        // Check boundary
        if (heights[r] > heights[r - 1]) break;

        // Check drop
        if (heights[r] < heights[r - 1]) rStack.push(r);
      }

      // Update left
      if (!lStack.empty()) {
        int i = lStack.top();
        ++heights[i];

        if (heights[i] == heights[i + 1]) {
          lStack.pop();
        }

        if (i - 1 > l) {
          lStack.push(i - 1);
        }

        continue;
      }

      // Update eright
      if (!rStack.empty()) {
        int i = rStack.top();
        ++heights[i];

        if (heights[i] == heights[i - 1]) {
          rStack.pop();
        }

        if (i + 1 < r) {
          rStack.push(i + 1);
        }

        continue;
      }

      // Update center
      ++heights[k];
      if (k - 1 > l) {
        lStack.push(k - 1);
      }
      if (k + 1 < r) {
        rStack.push(k + 1);
      }
    }

    return heights;
  }
};
