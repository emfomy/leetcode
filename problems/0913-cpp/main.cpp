// Source: https://leetcode.com/problems/cat-and-mouse
// Title: Cat and Mouse
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A game on an **undirected** graph is played by two players, Mouse and Cat, who alternate turns.
//
// The graph is given as follows: `graph[a]` is a list of all nodes `b` such that `ab` is an edge of the graph.
//
// The mouse starts at node `1` and goes first, the cat starts at node `2` and goes second, and there is a hole at node `0`.
//
// During each player's turn, they **must** travel along oneedge of the graph that meets where they are. For example, if the Mouse is at node 1, it **must** travel to any node in `graph[1]`.
//
// Additionally, it is not allowed for the Cat to travel to the Hole (node `0`).
//
// Then, the game can end in threeways:
//
// - If ever the Cat occupies the same node as the Mouse, the Cat wins.
// - If ever the Mouse reaches the Hole, the Mouse wins.
// - If ever a position is repeated (i.e., the players are in the same position as a previous turn, andit is the same player's turn to move), the game is a draw.
//
// Given a `graph`, and assuming both players play optimally, return
//
// - `1`if the mouse wins the game,
// - `2`if the cat wins the game, or
// - `0`if the game is a draw.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/11/17/cat1.jpg
//
// ```
// Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
// Output: 0
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/11/17/cat2.jpg
//
// ```
// Input: graph = [[1,3],[0],[3],[0,2]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `3 <= graph.length <= 50`
// - `1<= graph[i].length < graph.length`
// - `0 <= graph[i][j] < graph.length`
// - `graph[i][j] != i`
// - `graph[i]` is unique.
// - The mouse and the cat can always move.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Minimax, Retrograde
//
// Use (mouse, cat, turn) as state (turn=0/1 for mouse/cat's turn).
// We mark all states with mouse=0   as MOUSE_WIN.
// We mark all states with mouse=cat as CAT_WIN.
//
// Run BFS from these states.
// For a state in mouse's turn:
// if there is a MOUSE_WIN neighbor, then this state is also MOUSE_WIN;
// if all neighbor are CAT_WIN,       then this state is also CAT_WIN.
//
// However, in BFS, we start from the resolved states,
// and it is hard to compute all neighbor of a neighbor.
// Instead, we add a counter for each state to count the number of unresolved neighbors.
// If the counter becomes 0 and the state is not MOUSE_WIN, then it must be CAT_WIN.
//
// Similar to cat's turn.
//
// Note:
// counter is initialized with the node degree, which may include edges to node 0 (hole).
// Since the cat cannot move to the hole, we mark the state with cat=0 as INVALID,
// and push them into BFS to trigger the decrement path, canceling out over-counted moves.
class Solution {
  constexpr static int kMaxNodes = 50;

  enum Result {
    INVALID = 3,
    CAT_WIN = 2,
    MOUSE_WIN = 1,
    DRAW = 0,
  };

  enum Turn {
    MOUSE_TURN = 0,
    CAT_TURN = 1,
  };

  struct State {
    int mouse;
    int cat;
    Turn turn;
  };

 public:
  int catMouseGame(const vector<vector<int>>& graph) {
    const int n = graph.size();

    // Prepare data
    auto que = queue<State>();
    int counter[kMaxNodes][kMaxNodes][2] = {};     // (mouse, cat, turn)
    Result results[kMaxNodes][kMaxNodes][2] = {};  // (mouse, cat, turn)

    // Init counter
    for (int mouse = 0; mouse < n; ++mouse) {
      for (int cat = 1; cat < n; ++cat) {  // Cat can't be at hole
        counter[mouse][cat][MOUSE_TURN] = graph[mouse].size();
        counter[mouse][cat][CAT_TURN] = graph[cat].size();
      }
    }

    // Mouse at hole
    for (int cat = 1; cat < n; ++cat) {
      results[0][cat][MOUSE_TURN] = MOUSE_WIN;
      results[0][cat][CAT_TURN] = MOUSE_WIN;
      que.push({0, cat, MOUSE_TURN});
      que.push({0, cat, CAT_TURN});
    }

    // Cat at hole
    for (int mouse = 1; mouse < n; ++mouse) {
      results[mouse][0][MOUSE_TURN] = INVALID;
      results[mouse][0][CAT_TURN] = INVALID;
      que.push({mouse, 0, MOUSE_TURN});
      que.push({mouse, 0, CAT_TURN});
    }

    // Cat catches mouse
    for (int node = 1; node < n; ++node) {
      results[node][node][MOUSE_TURN] = CAT_WIN;
      results[node][node][CAT_TURN] = CAT_WIN;
      que.push({node, node, MOUSE_TURN});
      que.push({node, node, CAT_TURN});
    }

    // BFS
    while (!que.empty()) {
      auto [mouse, cat, turn] = que.front();
      que.pop();

      Result result = results[mouse][cat][turn];

      // Propagate
      if (turn == MOUSE_TURN) {
        for (int prev : graph[cat]) {
          if (prev == 0 || results[mouse][prev][CAT_TURN]) continue;

          if (result == CAT_WIN) {
            results[mouse][prev][CAT_TURN] = CAT_WIN;
            que.push({mouse, prev, CAT_TURN});
          } else if (--counter[mouse][prev][CAT_TURN] == 0) {  // MOUSE_WIN or INVALID
            results[mouse][prev][CAT_TURN] = MOUSE_WIN;
            que.push({mouse, prev, CAT_TURN});
          }
        }
      } else {  // CAT_TURN
        for (int prev : graph[mouse]) {
          if (results[prev][cat][MOUSE_TURN]) continue;

          if (result == MOUSE_WIN) {
            results[prev][cat][MOUSE_TURN] = MOUSE_WIN;
            que.push({prev, cat, MOUSE_TURN});
          } else if (--counter[prev][cat][MOUSE_TURN] == 0) {  // CAT_WIN or INVALID
            results[prev][cat][MOUSE_TURN] = CAT_WIN;
            que.push({prev, cat, MOUSE_TURN});
          }
        }
      }

      // Early stop
      if (results[1][2][MOUSE_TURN] != 0) break;
    }

    return results[1][2][MOUSE_TURN];
  }
};
