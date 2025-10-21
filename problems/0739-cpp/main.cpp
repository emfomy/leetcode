// Source: https: //leetcode.com/problems/daily-temperatures
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
// Store index of warmer days
class Solution {
 public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();

    auto st = stack<int>();
    auto ans = vector<int>(n);
    for (auto i = n - 1; i >= 0; --i) {
      auto temp = temperatures[i];
      while (!st.empty() && temperatures[st.top()] <= temp) st.pop();
      ans[i] = st.empty() ? 0 : (st.top() - i);
      st.push(i);
    }

    return ans;
  }
};
