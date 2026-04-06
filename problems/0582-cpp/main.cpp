// Source: https://leetcode.com/problems/kill-process
// Title: Kill Process
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `n` processes forming a rooted tree structure. You are given two integer arrays `pid` and `ppid`, where `pid[i]` is the ID of the `i^th` process and `ppid[i]` is the ID of the `i^th` process's parent process.
//
// Each process has only **one parent process** but may have multiple children processes. Only one process has `ppid[i] = 0`, which means this process has **no parent process** (the root of the tree).
//
// When a process is **killed**, all of its children processes will also be killed.
//
// Given an integer `kill` representing the ID of a process you want to kill, return a list of the IDs of the processes that will be killed. You may return the answer in **any order**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/02/24/ptree.jpg
//
// ```
// Input: pid = [1,3,10,5], ppid = [3,0,5,3], kill = 5
// Output: [5,10]
// Explanation:The processes colored in red are the processes that should be killed.
// ```
//
// **Example 2:**
//
// ```
// Input: pid = [1], ppid = [0], kill = 1
// Output: [1]
// ```
//
// **Constraints:**
//
// - `n == pid.length`
// - `n == ppid.length`
// - `1 <= n <= 5 * 10^4`
// - `1 <= pid[i] <= 5 * 10^4`
// - `0 <= ppid[i] <= 5 * 10^4`
// - Only one process has no parent.
// - All the values of `pid` are **unique**.
// - `kill` is **guaranteed** to be in `pid`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// BFS
class Solution {
 public:
  vector<int> killProcess(      //
      const vector<int>& pid,   //
      const vector<int>& ppid,  //
      const int kill            //
  ) {
    const int n = pid.size();

    // Build graph
    auto graph = unordered_map<int, vector<int>>();  // parent -> children
    for (int i = 0; i < n; ++i) {
      if (ppid[i] != 0) graph[ppid[i]].push_back(pid[i]);
    }

    // BFS
    auto ans = vector<int>();  // also as BFS queue
    ans.reserve(n);
    ans.push_back(kill);
    for (int i = 0; i < ans.size(); ++i) {
      int p = ans[i];
      if (graph.contains(p)) {
        ans.insert(ans.cend(), graph.at(p).cbegin(), graph.at(p).cend());
      }
    }

    return ans;
  }
};
