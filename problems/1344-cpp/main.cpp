// Source: https://leetcode.com/problems/angle-between-hands-of-a-clock
// Title: Angle Between Hands of a Clock
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two numbers, `hour` and `minutes`, return the smaller angle (in degrees) formed between the `hour` and the `minute` hand.
//
// Answers within `10^-5` of the actual value will be accepted as correct.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/12/26/sample_1_1673.png
//
// ```
// Input: hour = 12, minutes = 30
// Output: 165
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2019/12/26/sample_2_1673.png
//
// ```
// Input: hour = 3, minutes = 30
// Output: 75
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2019/12/26/sample_3_1673.png
//
// ```
// Input: hour = 3, minutes = 15
// Output: 7.5
// ```
//
// **Constraints:**
//
// - `1 <= hour <= 12`
// - `0 <= minutes <= 59`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>

using namespace std;

class Solution {
 public:
  double angleClock(int hour, int minutes) {
    double angle1 = ((hour % 12) + minutes / 60.0) * (360.0 / 12.0);
    double angle2 = minutes * (360.0 / 60.0);

    double diff = fabs(angle1 - angle2);

    return fmin(diff, 360 - diff);
  }
};

// Math
//
// Let h be the hours (zero indexed), m be the minutes.
// Let x = h + m/60 be the total hour after 00:00.
//
// These hands meets 11 times in 12 hours.
// That is, they meets each 12/11 hour.
// The hands runs r = x / (12/11) rounds.
// Let d be the decimal part of r.
// The angle is 360d.
class Solution2 {
 public:
  double angleClock(int h, int m) {
    double x = h + m / 60.0;
    double diff = fmod(11.0 * x, 12.0);  // diff = 12d
    return fmin(diff, 12.0 - diff) * 30.0;
  }
};

// Math (Trigonometry)
//
// Use cos and arccos instead of modulo.
// Note that acos(cos(θ)) is always in [0°, 180°].
// We can put 360d into this to normalize the degree.
// 360d = (h+m/60)/(12/11)*360 = 330h + 5.5m
class Solution3 {
  constexpr static double deg2rad = M_PI / 180;
  constexpr static double rad2deg = 180 / M_PI;

 public:
  double angleClock(int h, int m) {  //
    return acos(cos((330 * h + 5.5 * m) * deg2rad)) * rad2deg;
  }
};
