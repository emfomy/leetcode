// Source: https://leetcode.com/problems/largest-rectangle-in-histogram
// Title: Largest Rectangle in Histogram
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return the area of the largest rectangle in the histogram.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/04/histogram.jpg
//
// ```
// Input: heights = [2,1,5,6,2,3]
// Output: 10
// Explanation: The above is a histogram where width of each bar is 1.
// The largest rectangle is shown in the red area, which has an area = 10 units.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/01/04/histogram-1.jpg
//
// ```
// Input: heights = [2,4]
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= heights.length <= 10^5`
// - `0 <= heights[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

using namespace std;

// Monotonic Stack
//
// We first discover that the height of every rectangle is always the height of a bar.
// Therefore, for each bar, we only need to know the how far it can reach to the left/right.
//
// For right part, we use a increasing monotonic stack.
// If the top bar in the stack is taller than current bar,
// which means the top bar can only extend to the bar left of current bar.
// Note that is a bar is never popped, then it can extend to the right end (i.e. n);
//
// Same algorithm also works for the left part.
class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();

    // Right
    auto rights = vector<int>(n, n);  // rightmost is n
    {
      auto st = stack<int>();
      for (auto i = 0; i < n; ++i) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
          rights[st.top()] = i;  // right of the bar at the left is current index
          st.pop();
        }
        st.push(i);
      }
    }

    // Left
    auto lefts = vector<int>(n, 0);  // leftmost is 0
    {
      auto st = stack<int>();
      for (auto i = n - 1; i >= 0; --i) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
          lefts[st.top()] = i + 1;  // left of the bar at the right is current index + 1
          st.pop();
        }
        st.push(i);
      }
    }

    // Answer
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      ans = max(ans, heights[i] * (rights[i] - lefts[i]));
    }

    return ans;
  }
};
