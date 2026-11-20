// Source: https://leetcode.com/problems/daily-temperatures
// Title: Daily Temperatures
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `temperatures` represents the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `i^th` day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.
//
// **Example 1:**
//
// ```
// Input: temperatures = [73,74,75,71,69,72,76,73]
// Output: [1,1,4,2,1,1,0,0]
// ```
//
// **Example 2:**
//
// ```
// Input: temperatures = [30,40,50,60]
// Output: [1,1,1,0]
// ```
//
// **Example 3:**
//
// ```
// Input: temperatures = [30,60,90]
// Output: [1,1,0]
// ```
//
// **Constraints:**
//
// - `1 <=temperatures.length <= 10^5`
// - `30 <=temperatures[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

using namespace std;

// Monotonic Stack
//
// We put unprocessed days in the stack.
// The top is the lowest.
class Solution {
 public:
  vector<int> dailyTemperatures(const vector<int>& temperatures) {
    const int n = temperatures.size();

    // Prepare data
    auto ans = vector<int>(n, 0);
    auto st = stack<int>();  // unprocessed indices

    // Loop
    for (int i = 0; i < n; ++i) {
      while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
        ans[st.top()] = i - st.top();
        st.pop();
      }
      st.push(i);
    }

    return ans;
  }
};

// Monotonic Stack
//
// Loop from the last day.
// We put warmer candidate in the stack.
// The top is the lowest.
class Solution2 {
 public:
  vector<int> dailyTemperatures(const vector<int>& temperatures) {
    const int n = temperatures.size();

    // Prepare data
    auto ans = vector<int>(n, 0);
    auto st = stack<int>();  // candidate indices

    // Loop
    for (int i = n - 1; i >= 0; --i) {
      while (!st.empty() && temperatures[st.top()] <= temperatures[i]) {
        st.pop();
      }
      if (!st.empty()) {
        ans[i] = st.top() - i;
      }
      st.push(i);
    }

    return ans;
  }
};
