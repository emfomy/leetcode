// Source: https://leetcode.com/problems/minimum-number-of-people-to-teach
// Title: Minimum Number of People to Teach
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// On a social network consisting of `m` users and some friendships between users, two users can communicate with each other if they know a common language.
//
// You are given an integer `n`, an array `languages`, and an array `friendships` where:
//
// - There are `n` languages numbered `1` through `n`,
// - `languages[i]` is the set of languages the `i^​​​​​​th`​​​​ user knows, and
// - `friendships[i] = [u_​​​​​​i​​​, v_​​​​​​i]` denotes a friendship between the users `u^​​​​​_​​​​​​i`​​​​​ and `v_i`.
//
// You can choose **one** language and teach it to some users so that all friends can communicate with each other. Return the **minimum** number of users you need to teach.
// Note that friendships are not transitive, meaning if `x` is a friend of `y` and `y` is a friend of `z`, this doesn't guarantee that `x` is a friend of `z`.
//
// **Example 1:**
//
// ```
// Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
// Output: 1
// Explanation: You can either teach user 1 the second language or user 2 the first language.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
// Output: 2
// Explanation: Teach the third language to users 1 and 3, yielding two users to teach.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 500`
// - `languages.length == m`
// - `1 <= m <= 500`
// - `1 <= languages[i].length <= n`
// - `1 <= languages[i][j] <= n`
// - `1 <= u_​​​​​​i < v_​​​​​​i <= languages.length`
// - `1 <= friendships.length <= 500`
// - All tuples `(u_​​​​​i, v_​​​​​​i)` are unique
// - `languages[i]` contains only unique values
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bitset>
#include <vector>

using namespace std;

// We first find the use who has incommunicable friend.
// Next loop for all languages and try to teach them.
class Solution {
 public:
  int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
    int m = languages.size();

    // Language sets
    auto langSets = vector<bitset<500>>(m);
    for (auto user = 0; user < m; ++user) {
      for (auto lang : languages[user]) {
        langSets[user][lang - 1] = true;
      }
    }

    // Find longly users
    auto longlyUsers = vector<bool>(m);  // has incommunicable friend
    for (auto& friendship : friendships) {
      auto u = friendship[0] - 1, v = friendship[1] - 1;
      if ((langSets[u] & langSets[v]).any()) continue;
      longlyUsers[u] = true;
      longlyUsers[v] = true;
    }
    if ((longlyUsers.size() == 0)) return 0;

    // Find answer
    auto ans = m;
    for (auto lang = 0; lang < n; ++lang) {
      auto count = 0;
      for (auto user = 0; user < m; ++user) {
        if (longlyUsers[user] & !langSets[user][lang]) count++;
      }
      ans = min(ans, count);
    }

    return ans;
  }
};
