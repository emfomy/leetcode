// Source: https://leetcode.com/problems/maximum-number-of-balloons
// Title: Maximum Number of Balloons
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `text`, you want to use the characters of `text` to form as many instances of the word **"balloon"** as possible.
//
// You can use each character in `text` **at most once**. Return the maximum number of instances that can be formed.
//
// **Example 1:**
//
// **https://assets.leetcode.com/uploads/2019/09/05/1536_ex1_upd.JPG**
//
// ```
// Input: text = "nlaebolko"
// Output: 1
// ```
//
// **Example 2:**
//
// **https://assets.leetcode.com/uploads/2019/09/05/1536_ex2_upd.JPG**
//
// ```
// Input: text = "loonbalxballpoon"
// Output: 2
// ```
//
// **Example 3:**
//
// ```
// Input: text = "leetcode"
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= text.length <= 10^4`
// - `text` consists of lower case English letters only.
//
// **Note:** This question is the same as 2287: Rearrange Characters to Make Target String.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <string>

using namespace std;

// Count
class Solution {
 public:
  int maxNumberOfBalloons(const string &text) {
    auto freqs = array<int, 128>();
    for (char ch : text) {
      ++freqs[ch];
    }

    return min({freqs['b'], freqs['a'], freqs['l'] / 2, freqs['o'] / 2, freqs['n']});
  }
};
