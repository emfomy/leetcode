// Source: https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations
// Title: Count the Number of Computer Unlocking Permutations
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `complexity` of length `n`.
//
// There are `n` **locked** computers in a room with labels from 0 to `n - 1`, each with its own **unique** password. The password of the computer `i` has a complexity `complexity[i]`.
//
// The password for the computer labeled 0 is **already** decrypted and serves as the root. All other computers must be unlocked using it or another previously unlocked computer, following this information:
//
// - You can decrypt the password for the computer `i` using the password for computer `j`, where `j` is **any** integer less than `i` with a lower complexity. (i.e. `j < i` and `complexity[j] < complexity[i]`)
// - To decrypt the password for computer `i`, you must have already unlocked a computer `j` such that `j < i` and `complexity[j] < complexity[i]`.
//
// Find the number of **permutation** of `[0, 1, 2, ..., (n - 1)]` that represent a valid order in which the computers can be unlocked, starting from computer 0 as the only initially unlocked one.
//
// A **permutation** is a rearrangement of all the elements of an array.
//
// Since the answer may be large, return it **modulo** 10^9 + 7.
//
// **Note** that the password for the computer **with label** 0 is decrypted, and not the computer with the first position in the permutation.
//
// **Example 1:**
//
// ```
// Input: complexity = [1,2,3]
// Output: 2
// Explanation:
// The valid permutations are:
//
// - [0, 1, 2]
//   - Unlock computer 0 first with root password.
//   - Unlock computer 1 with password of computer 0 since `complexity[0] < complexity[1]`.
//   - Unlock computer 2 with password of computer 1 since `complexity[1] < complexity[2]`.
//
// - [0, 2, 1]
//   - Unlock computer 0 first with root password.
//   - Unlock computer 2 with password of computer 0 since `complexity[0] < complexity[2]`.
//   - Unlock computer 1 with password of computer 0 since `complexity[0] < complexity[1]`.
// ```
//
// **Example 2:**
//
// ```
// Input: complexity = [3,3,3,4,4,4]
// Output: 0
// Explanation:
// There are no possible permutations which can unlock all computers.
// ```
//
// **Constraints:**
//
// - `2 <= complexity.length <= 10^5`
// - `1 <= complexity[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Use Math
//
// If any computer has complexity less than the 0th one, than it is impossible to decrypt.
// Therefore, computer-0 must be the minimal, and its complexity should be unique.
//
// Since all computer can be decrypted by computer-0,
// the permutation of the rest computer is irrelevant.
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countPermutations(vector<int>& complexity) {
    int n = complexity.size();

    // Check availability
    auto comp0 = complexity[0];
    if (find_if(complexity.cbegin() + 1, complexity.cend(), [=](auto comp) -> bool { return comp <= comp0; }) !=
        complexity.cend()) {
      return 0;
    }

    auto ans = 1ll;
    for (auto i = 2; i < n; ++i) {
      ans = (ans * i) % modulo;
    }

    return ans;
  }
};
