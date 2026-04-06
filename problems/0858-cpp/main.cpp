// Source: https://leetcode.com/problems/mirror-reflection
// Title: Mirror Reflection
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a special square room with mirrors on each of the four walls. Except for the southwest corner, there are receptors on each of the remaining corners, numbered `0`, `1`, and `2`.
//
// The square room has walls of length `p`and a laser ray from the southwest corner first meets the east wall at a distance `q` from the `0^th` receptor.
//
// Given the two integers `p` and `q`, return the number of the receptor that the ray meets first.
//
// The test cases are guaranteed so that the ray will meet a receptor eventually.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/06/18/reflection.png
//
// ```
// Input: p = 2, q = 1
// Output: 2
// Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.
// ```
//
// **Example 2:**
//
// ```
// Input: p = 3, q = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= q <= p <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Treat the room as an infinite grid with size p.
//
// Let d = gcd(p, q). Let x = p/d, y = q/d
// The first lattice point that the laser ray meet is (x, y),
// Note that py = pq/d = xq is a multiple of q.
//
// The lattice points labeled 0 are (odd, even) points.
// The lattice points labeled 1 are (odd, odd) points.
// The lattice points labeled 2 are (even, odd) points.
// Just check the parity of (x, y).
// Note that since x & y are co-prime, they can't be both even.
class Solution {
 public:
  int mirrorReflection(int p, int q) {
    int d = gcd(p, q);
    int x = p / d, y = q / d;

    if (x % 2 == 0) return 2;
    if (y % 2 == 0) return 0;
    return 1;
  }
};
