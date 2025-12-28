// Source: https://leetcode.com/problems/count-collisions-on-a-road
// Title: Count Collisions on a Road
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` cars on an infinitely long road. The cars are numbered from `0` to `n - 1` from left to right and each car is present at a **unique** point.
//
// You are given a **0-indexed** string `directions` of length `n`. `directions[i]` can be either `'L'`, `'R'`, or `'S'` denoting whether the `i^th` car is moving towards the **left**, towards the **right**, or **staying** at its current point respectively. Each moving car has the **same speed**.
//
// The number of collisions can be calculated as follows:
//
// - When two cars moving in **opposite** directions collide with each other, the number of collisions increases by `2`.
// - When a moving car collides with a stationary car, the number of collisions increases by `1`.
//
// After a collision, the cars involved can no longer move and will stay at the point where they collided. Other than that, cars cannot change their state or direction of motion.
//
// Return the **total number of collisions** that will happen on the road.
//
// **Example 1:**
//
// ```
// Input: directions = "RLRSLL"
// Output: 5
// Explanation:
// The collisions that will happen on the road are:
// - Cars 0 and 1 will collide with each other. Since they are moving in opposite directions, the number of collisions becomes 0 + 2 = 2.
// - Cars 2 and 3 will collide with each other. Since car 3 is stationary, the number of collisions becomes 2 + 1 = 3.
// - Cars 3 and 4 will collide with each other. Since car 3 is stationary, the number of collisions becomes 3 + 1 = 4.
// - Cars 4 and 5 will collide with each other. After car 4 collides with car 3, it will stay at the point of collision and get hit by car 5. The number of collisions becomes 4 + 1 = 5.
// Thus, the total number of collisions that will happen on the road is 5.
// ```
//
// **Example 2:**
//
// ```
// Input: directions = "LLRR"
// Output: 0
// Explanation:
// No cars will collide with each other. Thus, the total number of collisions that will happen on the road is 0.```
//
// **Constraints:**
//
// - `1 <= directions.length <= 10^5`
// - `directions[i]` is either `'L'`, `'R'`, or `'S'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>

using namespace std;

// Count
//
// Each car will only collide once.
// We only need to count the cars won't collide,
// that is, left-most cars moving left, and right-most cars moving right, and all staying cars.
class Solution {
 public:
  int countCollisions(string directions) {
    int n = directions.size();

    auto ans = n;

    // Left-most moving left
    for (auto i = 0; i < n; ++i) {
      if (directions[i] == 'L') {
        --ans;
      } else {
        break;
      }
    }

    // Right-most moving left
    for (auto i = n - 1; i >= 0; --i) {
      if (directions[i] == 'R') {
        --ans;
      } else {
        break;
      }
    }

    // Staying
    for (auto i = 0; i < n; ++i) {
      if (directions[i] == 'S') --ans;
    }

    return ans;
  }
};

// Count
class Solution2 {
 public:
  int countCollisions(string dirs) {
    int n = dirs.size();

    auto ans = n;

    int lefts = find_if_not(dirs.cbegin(), dirs.cend(), [](char c) -> bool { return c == 'L'; }) - dirs.cbegin();
    int rights = find_if_not(dirs.crbegin(), dirs.crend(), [](char c) -> bool { return c == 'R'; }) - dirs.crbegin();
    int stayings = count_if(dirs.cbegin(), dirs.cend(), [](char c) -> bool { return c == 'S'; });

    return ans - rights - lefts - stayings;
  }
};
