// Source: https://leetcode.com/problems/rectangle-overlap
// Title: Rectangle Overlap
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An axis-aligned rectangle is represented as a list `[x1, y1, x2, y2]`, where `(x1, y1)` is the coordinate of its bottom-left corner, and `(x2, y2)` is the coordinate of its top-right corner. Its top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the Y-axis.
//
// Two rectangles overlap if the area of their intersection is **positive**. To be clear, two rectangles that only touch at the corner or edges do not overlap.
//
// Given two axis-aligned rectangles `rec1` and `rec2`, return `true` if they overlap, otherwise return `false`.
//
// **Example 1:**
//
// ```
// Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
// Output: false
// ```
//
// **Example 3:**
//
// ```
// Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
// Output: false
// ```
//
// **Constraints:**
//
// - `rec1.length == 4`
// - `rec2.length == 4`
// - `-10^9 <= rec1[i], rec2[i] <= 10^9`
// - `rec1` and `rec2` represent a valid rectangle with a non-zero area.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Two rectangle overlaps iff. both axis overlap.
//
// Two segment overlaps iff.
// the max of left points is greater than the min of the right points.
class Solution {
 public:
  bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    int ax1 = rec1[0], ay1 = rec1[1], ax2 = rec1[2], ay2 = rec1[3];
    int bx1 = rec2[0], by1 = rec2[1], bx2 = rec2[2], by2 = rec2[3];

    return (max(ax1, bx1) < min(ax2, bx2)) && (max(ay1, by1) < min(ay2, by2));
  }
};
