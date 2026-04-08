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
// We put (height, position) in the stack, both of them are increasing.
// It represent the leftmost possible rectangle of each height.
//
// We loop the bars from the left.
// If the new bar is shorter than the top height,
// then pop it and compute the maximum rectangle,
// and then push the new bar height with the previous top position.
// Next push the new bar if it is taller than the top height.
class Solution {
  struct State {
    int height;
    int pos;
  };

 public:
  int largestRectangleArea(const vector<int>& heights) {
    const int n = heights.size();
    int maxArea = 0;

    auto st = stack<State>();
    st.push(State{0, 0});  // first sentinel
    for (int i = 0; i <= n; ++i) {
      int height = i < n ? heights[i] : 0;  // sentinel at i=n
      int pos = i;

      // Pop
      while (st.top().height > height) {
        maxArea = max(maxArea, st.top().height * (i - st.top().pos));
        pos = st.top().pos;
        st.pop();
      }

      // Push
      if (st.top().height < height) {
        st.push(State{height, pos});
      }
    }

    return maxArea;
  }
};
