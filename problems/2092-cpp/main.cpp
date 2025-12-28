// Source: https://leetcode.com/problems/find-all-people-with-secret
// Title: Find All People With Secret
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` indicating there are `n` people numbered from `0` to `n - 1`. You are also given a **0-indexed** 2D integer array `meetings` where `meetings[i] = [x_i, y_i, time_i]` indicates that person `x_i` and person `y_i` have a meeting at `time_i`. A person may attend **multiple meetings** at the same time. Finally, you are given an integer `firstPerson`.
//
// Person `0` has a **secret** and initially shares the secret with a person `firstPerson` at time `0`. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person `x_i` has the secret at `time_i`, then they will share the secret with person `y_i`, and vice versa.
//
// The secrets are shared **instantaneously**. That is, a person may receive the secret and share it with people in other meetings within the same time frame.
//
// Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in **any order**.
//
// **Example 1:**
//
// ```
// Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
// Output: [0,1,2,3,5]
// **Explanation:
// **At time 0, person 0 shares the secret with person 1.
// At time 5, person 1 shares the secret with person 2.
// At time 8, person 2 shares the secret with person 3.
// At time 10, person 1 shares the secret with person 5.​​​​
// Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
// Output: [0,1,3]
// Explanation:
// At time 0, person 0 shares the secret with person 3.
// At time 2, neither person 1 nor person 2 know the secret.
// At time 3, person 3 shares the secret with person 0 and person 1.
// Thus, people 0, 1, and 3 know the secret after all the meetings.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
// Output: [0,1,2,3,4]
// Explanation:
// At time 0, person 0 shares the secret with person 1.
// At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
// Note that person 2 can share the secret at the same time as receiving it.
// At time 2, person 3 shares the secret with person 4.
// Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `1 <= meetings.length <= 10^5`
// - `meetings[i].length == 3`
// - `0 <= x_i, y_i <= n - 1`
// - `x_i != y_i`
// - `1 <= time_i <= 10^5`
// - `1 <= firstPerson <= n - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

// Sort + Union-Find
//
// First sort the meetings by time.
// For each time, use union-find to group the people.
class Solution {
  struct UnionFind {
    vector<int> parent;
    vector<int> rank;

    UnionFind(int n) : parent(n), rank(n) { reset(); }

    void reset() {
      iota(parent.begin(), parent.end(), 0);
      fill(rank.begin(), rank.end(), 0);
    }

    int find(int x) {
      if (parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    }

    void merge(int x, int y) {
      x = find(x);
      y = find(y);

      // Skip
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (rank[x] < rank[y]) swap(x, y);

      // Merge y into x
      if (rank[x] == rank[y]) ++rank[x];
      parent[y] = x;
    }
  };

 public:
  vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    // Init
    auto knowns = vector<char>(n);  // use char as bool
    knowns[0] = true;
    knowns[firstPerson] = true;

    // Sort meetings by time
    sort(meetings.begin(), meetings.end(), [](vector<int>& a, vector<int>& b) -> bool { return a[2] < b[2]; });

    // Simulation
    auto uf = UnionFind(n);
    auto prevTime = 0;
    auto room = vector<int>();  // people in the room
    for (auto& meeting : meetings) {
      auto x = meeting[0], y = meeting[1], time = meeting[2];

      if (time != prevTime) {  // clear the room
        for (auto p : room) knowns[uf.find(p)] |= knowns[p];
        for (auto p : room) knowns[p] |= knowns[uf.parent[p]];
        room.clear();
        uf.reset();
      }

      room.push_back(x);
      room.push_back(y);
      uf.merge(x, y);
      prevTime = time;
    }

    // Clear final room
    for (auto p : room) knowns[uf.find(p)] |= knowns[p];
    for (auto p : room) knowns[p] |= knowns[uf.parent[p]];

    // Answer
    auto ans = vector<int>();
    for (auto i = 0; i < n; ++i) {
      if (knowns[i]) ans.push_back(i);
    }

    return ans;
  }
};

// Sort + Union-Find
//
// First sort the meetings by time.
// For each time, use union-find to group the people.
//
// After time change, only keep the group with person 0, and reset other people
class Solution2 {
  struct UnionFind {
    vector<int> parent;
    vector<int> rank;

    UnionFind(int n) : parent(n), rank(n) {
      iota(parent.begin(), parent.end(), 0);
      fill(rank.begin(), rank.end(), 0);
    }

    void reset(int x) {
      parent[x] = x;
      rank[x] = 0;
    }

    bool connected(int x, int y) {  //
      return find(x) == find(y);
    }

    int find(int x) {
      if (parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    }

    void merge(int x, int y) {
      x = find(x);
      y = find(y);

      // Skip
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (rank[x] < rank[y]) swap(x, y);

      // Merge y into x
      if (rank[x] == rank[y]) ++rank[x];
      parent[y] = x;
    }
  };

 public:
  vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    // Sort meetings by time
    sort(meetings.begin(), meetings.end(), [](vector<int>& a, vector<int>& b) -> bool { return a[2] < b[2]; });

    // Group meetings by time
    auto rooms = vector<vector<pair<int, int>>>();  // each room are list of meetings
    rooms.push_back({{0, firstPerson}});

    auto prevTime = 0;
    for (auto& meeting : meetings) {
      auto x = meeting[0], y = meeting[1], time = meeting[2];

      if (time != prevTime) {
        rooms.push_back({{x, y}});
      } else {
        rooms.back().push_back({x, y});
      }

      prevTime = time;
    }

    // Init
    auto uf = UnionFind(n);
    for (auto& room : rooms) {
      for (auto [x, y] : room) uf.merge(x, y);
      for (auto [x, y] : room) {
        if (!uf.connected(x, 0)) {  // no need to check y since they are connected
          uf.reset(x);
          uf.reset(y);
        }
      }
    }

    // Answer
    auto ans = vector<int>();
    for (auto i = 0; i < n; ++i) {
      if (uf.connected(i, 0)) ans.push_back(i);
    }

    return ans;
  }
};
