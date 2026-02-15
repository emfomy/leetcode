// Source: https://leetcode.com/problems/4-keys-keyboard
// Title: 4 Keys Keyboard
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Imagine you have a special keyboard with the following keys:
//
// - A: Print one `'A'` on the screen.
// - Ctrl-A: Select the whole screen.
// - Ctrl-C: Copy selection to buffer.
// - Ctrl-V: Print buffer on screen appending it after what has already been printed.
//
// Given an integer n, return the maximum number of `'A'` you can print on the screen with **at most** `n` presses on the keys.
//
// **Example 1:**
//
// ```
// Input: n = 3
// Output: 3
// Explanation: We can at most get 3 A's on screen by pressing the following key sequence:
// A, A, A
// ```
//
// **Example 2:**
//
// ```
// Input: n = 7
// Output: 9
// Explanation: We can at most get 9 A's on screen by pressing following key sequence:
// A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
// ```
//
// **Constraints:**
//
// - `1 <= n <= 50`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

// DP
//
// Claim: CtrlA should always followed by CtrlC, and followed by several CtrlV
// If no CtrlC or CtrlV, then the key press is meaningless.
// If some A between above Ctrls, moving A before CtrlA is always better.
//
// Now we only have two kind of operations:
// press A, increase the length by 1 (cost 1).
// press CtrlA+CtrlC+CtrlV*k, multiply the length by (k+1) (cost k+2).
class Solution {
 public:
  int maxA(int n) {
    auto dp = vector<int>(n + 1);  // max length after i keys

    for (int i = 1; i <= n; ++i) {
      dp[i] = dp[i - 1] + 1;  // press A
      for (int k = 1; k + 2 <= i; ++k) {
        dp[i] = max(dp[i], dp[i - k - 2] * (k + 1));
      }
    }

    return dp[n];
  }
};

// DP
//
// Claim: CtrlA should always followed by CtrlC, and followed by several CtrlV
// If no CtrlC or CtrlV, then the key press is meaningless.
// If some A between above Ctrls, moving A before CtrlA is always better.
//
// Now we only have two kind of operations:
// press A, increase the length by 1 (cost 1).
// press CtrlA+CtrlC+CtrlV*k, multiply the length by (k+1) (cost k+2).
//
// k=1, multiply 2, cost 3
// k=2, multiply 3, cost 4
// k=3, multiply 4, cost 5
// k=4, multiply 5, cost 6
// k=5, multiply 6, cost 7
// k=6, multiply 7, cost 8
//
// We found that, instead of do k=5 (x6, len7), we can do k=2 & k=3 (x6, len7)
// Also, instead of do k=6 (x7, len8), we can do k=3 & k=3 (x9, len8)
// It is easy to conclude that k>4 is meaningless.
//
// Therefore we only need to try k=1~4
class Solution2 {
 public:
  int maxA(int n) {
    auto dp = vector<int>(n + 1);  // max length after i keys

    for (int i = 1; i <= n; ++i) {
      dp[i] = dp[i - 1] + 1;  // press A
      for (int k = 1; k <= 4 && k + 2 <= i; ++k) {
        dp[i] = max(dp[i], dp[i - k - 2] * (k + 1));
      }
    }

    return dp[n];
  }
};
