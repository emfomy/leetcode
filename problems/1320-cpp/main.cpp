// Source: https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers
// Title: Minimum Distance to Type a Word Using Two Fingers
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// https://assets.leetcode.com/uploads/2020/01/02/leetcode_keyboard.png
//
// You have a keyboard layout as shown above in the **X-Y** plane, where each English uppercase letter is located at some coordinate.
//
// - For example, the letter `'A'` is located at coordinate `(0, 0)`, the letter `'B'` is located at coordinate `(0, 1)`, the letter `'P'` is located at coordinate `(2, 3)` and the letter `'Z'` is located at coordinate `(4, 1)`.
//
// Given the string `word`, return the minimum total **distance** to type such string using only two fingers.
//
// The **distance** between coordinates `(x_1, y_1)` and `(x_2, y_2)` is `|x_1 - x_2| + |y_1 - y_2|`.
//
// **Note** that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.
//
// **Example 1:**
//
// ```
// Input: word = "CAKE"
// Output: 3
// Explanation: Using two fingers, one optimal way to type "CAKE" is:
// Finger 1 on letter 'C' -> cost = 0
// Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2
// Finger 2 on letter 'K' -> cost = 0
// Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1
// Total distance = 3
// ```
//
// **Example 2:**
//
// ```
// Input: word = "HAPPY"
// Output: 6
// Explanation: Using two fingers, one optimal way to type "HAPPY" is:
// Finger 1 on letter 'H' -> cost = 0
// Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
// Finger 2 on letter 'P' -> cost = 0
// Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
// Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
// Total distance = 6
// ```
//
// **Constraints:**
//
// - `2 <= word.length <= 300`
// - `word` consists of uppercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <climits>
#include <string>

using namespace std;

// DP
//
// Use the position of the two finger as DP state. (Total 26x26 states)
// For each letter, try to use both finger to get the new state. (Total 26x26x2 possibility).
class Solution {
  constexpr static int kKeys = 26;
  constexpr static int kStates = kKeys * kKeys;
  constexpr static int kCols = 6;

  using State = array<int, kStates>;

  static int getDist(int key1, int key2) {
    int row1 = key1 / kCols, col1 = key1 % kCols;
    int row2 = key2 / kCols, col2 = key2 % kCols;
    return abs(row1 - row2) + abs(col1 - col2);
  }

 public:
  int minimumDistance(const string &word) {
    State prevCosts = {};
    State currCosts = {};  // initialized as all zero since the finger can be anywhere at first.

    for (const char ch : word) {
      int currKey = ch - 'A';
      swap(currCosts, prevCosts);
      fill(currCosts.begin(), currCosts.end(), INT_MAX);

      for (int prevState = 0; prevState < kStates; ++prevState) {
        if (prevCosts[prevState] == INT_MAX) continue;
        int leftKey = prevState / kKeys, rightKey = prevState % kKeys;

        // Move left
        int leftState = currKey * kKeys + rightKey;
        currCosts[leftState] = min(currCosts[leftState], prevCosts[prevState] + getDist(currKey, leftKey));

        // Move right
        int rightState = leftKey * kKeys + currKey;
        currCosts[rightState] = min(currCosts[rightState], prevCosts[prevState] + getDist(currKey, rightKey));
      }
    }

    return *min_element(currCosts.cbegin(), currCosts.cend());
  }
};

// DP
//
// We can improve the DP State.
// For each step i, one of the finger must be placed at word[i].
// Therefore, we only need to store the state for another finger.
class Solution2 {
  constexpr static int kInf = INT_MAX / 2;  // avoid overflow

  constexpr static int kKeys = 26;
  constexpr static int kCols = 6;

  using State = array<int, kKeys>;

  static int getDist(int key1, int key2) {
    int row1 = key1 / kCols, col1 = key1 % kCols;
    int row2 = key2 / kCols, col2 = key2 % kCols;
    return abs(row1 - row2) + abs(col1 - col2);
  }

 public:
  int minimumDistance(const string &word) {
    const int n = word.size();

    State prevCosts = {};
    State currCosts = {};

    // Initialize for the first key
    fill(currCosts.begin(), currCosts.end(), 0);

    for (int i = 1; i < n; ++i) {
      swap(currCosts, prevCosts);
      fill(currCosts.begin(), currCosts.end(), kInf);

      int curr = word[i] - 'A';            // current key
      int prev = word[i - 1] - 'A';        // previous key
      int distPrev = getDist(curr, prev);  // distance from prev key

      for (int other = 0; other < kKeys; ++other) {
        // Previous state is either (prev x other) or (other x prev)

        // distance from other key
        int distOther = getDist(curr, other);

        // (curr x other) <- (prev x other)
        currCosts[other] = min(currCosts[other], prevCosts[other] + distPrev);

        // (curr x prev) <- (other x prev)
        currCosts[prev] = min(currCosts[prev], prevCosts[other] + distOther);
      }
    }

    return *min_element(currCosts.cbegin(), currCosts.cend());
  }
};
