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
// We store the day which has not been processed in the stack.
class Solution {
 public:
  vector<int> dailyTemperatures(const vector<int>& temperatures) {
    const int n = temperatures.size();

    auto ans = vector<int>(n);
    auto st = stack<pair<int, int>>();  // (temp, day)

    for (int i = 0; i < n; ++i) {
      int temp = temperatures[i];

      while (!st.empty() && temp > st.top().first) {
        ans[st.top().second] = i - st.top().second;
        st.pop();
      }

      st.emplace(temp, i);
    }

    return ans;
  }
};

// Monotonic Stack
//
// We store the day which has not been processed in the stack.
class Solution2 {
 public:
  vector<int> dailyTemperatures(const vector<int>& temperatures) {
    const int n = temperatures.size();

    auto ans = vector<int>(n);
    auto st = stack<int>();  // day

    for (int i = 0; i < n; ++i) {
      int temp = temperatures[i];

      while (!st.empty() && temp > temperatures[st.top()]) {
        ans[st.top()] = i - st.top();
        st.pop();
      }

      st.emplace(i);
    }

    return ans;
  }
};
