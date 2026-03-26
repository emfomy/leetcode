// Source: https://leetcode.com/problems/bag-of-tokens
// Title: Bag of Tokens
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You start with an initial **power** of `power`, an initial **score** of `0`, and a bag of tokens given as an integer array `tokens`, where each`tokens[i]` denotes the value of token_i.
//
// Your goal is to **maximize** the total **score** by strategically playing these tokens. In one move, you can play an **unplayed** token in one of the two ways (but not both for the same token):
//
// - **Face-up**: If your current power is **at least** `tokens[i]`, you may play token_i, losing `tokens[i]` power and gaining `1` score.
// - **Face-down**: If your current score is **at least** `1`, you may play token_i, gaining `tokens[i]` power and losing `1` score.
//
// Return the **maximum** possible score you can achieve after playing **any** number of tokens.
//
// **Example 1:**
//
// ```
// Input: tokens = [100], power = 50
// Output: 0
// Explanation
// **:** Since your score is `0` initially, you cannot play the token face-down. You also cannot play it face-up since your power (`50`) is less than `tokens[0]`(`100`).
// ```
//
// **Example 2:**
//
// ```
// Input: tokens = [200,100], power = 150
// Output: 1
// Explanation: Play token_1 (`100`) face-up, reducing your power to`50` and increasing your score to`1`.
// There is no need to play token_0, since you cannot play it face-up to add to your score. The maximum score achievable is `1`.
// ```
//
// **Example 3:**
//
// ```
// Input: tokens = [100,200,300,400], power = 200
// Output: 2
// Explanation: Play the tokens in this order to get a score of `2`:
// - Play token_0 (`100`) face-up, reducing power to `100` and increasing score to `1`.
// - Play token_3 (`400`) face-down, increasing power to `500` and reducing score to `0`.
// - Play token_1 (`200`) face-up, reducing power to `300` and increasing score to `1`.
// - Play token_2 (`300`) face-up, reducing power to `0` and increasing score to `2`.
// The maximum score achievable is `2`.
// ```
//
// **Constraints:**
//
// - `0 <= tokens.length <= 1000`
// - `0 <= tokens[i], power < 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Greedy + Sort + Two Pointer
//
// It is better to play the higher tokens face-down and lower tokens face-up.
//
// We first sort the tokens.
// Next use all power to gain as must score as you can.
// If there is no enough power, play the highest possible tokens faced-down.
//
// We return the highest score we can get during above process.
class Solution {
 public:
  int bagOfTokensScore(vector<int>& tokens, int power) {
    const int n = tokens.size();

    // Sort
    sort(tokens.begin(), tokens.end());

    // Greedy
    int maxScore = 0;
    int score = 0;
    int i = 0, j = n;  // [i, j) is the range of unplayed token
    while (i < j) {
      if (power >= tokens[i]) {
        power -= tokens[i++];
        ++score;
      } else if (score > 0) {
        --score;
        power += tokens[--j];
      } else {
        break;
      }
      maxScore = max(maxScore, score);
    }

    return maxScore;
  }
};
