// Source: https://leetcode.com/problems/process-restricted-friend-requests
// Title: Process Restricted Friend Requests
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` indicating the number of people in a network. Each person is labeled from `0` to `n - 1`.
//
// You are also given a **0-indexed** 2D integer array `restrictions`, where `restrictions[i] = [x_i, y_i]` means that person `x_i` and person `y_i` **cannot **become **friends**,** **either **directly** or **indirectly** through other people.
//
// Initially, no one is friends with each other. You are given a list of friend requests as a **0-indexed** 2D integer array `requests`, where `requests[j] = [u_j, v_j]` is a friend request between person `u_j` and person `v_j`.
//
// A friend request is **successful **if `u_j` and `v_j` can be **friends**. Each friend request is processed in the given order (i.e., `requests[j]` occurs before `requests[j + 1]`), and upon a successful request, `u_j` and `v_j` **become direct friends** for all future friend requests.
//
// Return a **boolean array** `result`, where each `result[j]` is `true` if the `j^th` friend request is **successful** or `false` if it is not.
//
// **Note:** If `u_j` and `v_j` are already direct friends, the request is still **successful**.
//
// **Example 1:**
//
// ```
// Input: n = 3, restrictions = [[0,1]], requests = [[0,2],[2,1]]
// Output: [true,false]
// **Explanation:
// **Request 0: Person 0 and person 2 can be friends, so they become direct friends.
// Request 1: Person 2 and person 1 cannot be friends since person 0 and person 1 would be indirect friends (1--2--0).
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, restrictions = [[0,1]], requests = [[1,2],[0,2]]
// Output: [true,false]
// **Explanation:
// **Request 0: Person 1 and person 2 can be friends, so they become direct friends.
// Request 1: Person 0 and person 2 cannot be friends since person 0 and person 1 would be indirect friends (0--2--1).
// ```
//
// **Example 3:**
//
// ```
// Input: n = 5, restrictions = [[0,1],[1,2],[2,3]], requests = [[0,4],[1,2],[3,1],[3,4]]
// Output: [true,false,true,false]
// **Explanation:
// **Request 0: Person 0 and person 4 can be friends, so they become direct friends.
// Request 1: Person 1 and person 2 cannot be friends since they are directly restricted.
// Request 2: Person 3 and person 1 can be friends, so they become direct friends.
// Request 3: Person 3 and person 4 cannot be friends since person 0 and person 1 would be indirect friends (0--4--3--1).
// ```
//
// **Constraints:**
//
// - `2 <= n <= 1000`
// - `0 <= restrictions.length <= 1000`
// - `restrictions[i].length == 2`
// - `0 <= x_i, y_i <= n - 1`
// - `x_i != y_i`
// - `1 <= requests.length <= 1000`
// - `requests[j].length == 2`
// - `0 <= u_j, v_j <= n - 1`
// - `u_j != v_j`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

// Union-Find
//
// For each requests (u, v), check if it violate the any restriction (x, y).
// If not, merge these two groups.
//
// To check the violation, we find the parent of u, v, x, y,
// and check if p(u) == p(x) && p(v) == p(y) or p(u) == p(y) && p(v) == p(x).
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;

    UnionFind(const int n) : parents(n), ranks(n, 1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(const int x) {
      if (parents[x] != x) parents[x] = find(parents[x]);
      return parents[x];
    }

    // x, y must be root
    void uniteRoot(int x, int y) {
      if (x == y) return;

      // Ensure rank(x) > rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
    }
  };

 public:
  vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
    int l = requests.size();

    // Union Find
    auto uf = UnionFind(n);

    // Restriction helper
    // u, v must be root
    auto checkSuccess = [&](const int u, const int v) {
      // Edge case
      if (u == v) return true;

      for (auto& restriction : restrictions) {
        const int x = uf.find(restriction[0]), y = uf.find(restriction[1]);
        if ((u == x && v == y) || (u == y && v == x)) return false;
      }
      return true;
    };

    // Loop
    auto successes = vector<bool>();
    successes.reserve(l);
    for (auto& request : requests) {
      const int u = uf.find(request[0]), v = uf.find(request[1]);

      // Check restriction
      bool success = checkSuccess(u, v);
      successes.push_back(success);

      // Union u and v
      if (success) {
        uf.uniteRoot(u, v);
      }
    }

    return successes;
  }
};
