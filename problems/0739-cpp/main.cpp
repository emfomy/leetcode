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
// If day j is farther (i.e. j > i) and cooler than day i, then it will never be a candidate.
// Then the monotonic stack should be decreasing from right to left.
// We store the day index in the stack.
class Solution {
 public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();

    auto st = stack<int>();
    auto ans = vector<int>(n);
    for (auto day = n - 1; day >= 0; --day) {
      auto temp = temperatures[day];
      while (!st.empty() && temperatures[st.top()] <= temp) st.pop();  // pop cooler days
      ans[day] = st.empty() ? 0 : (st.top() - day);
      st.push(day);
    }

    return ans;
  }
};
