// Source: https://leetcode.com/problems/moving-average-from-data-stream
// Title: Moving Average from Data Stream
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.
//
// Implement the`MovingAverage` class:
//
// - `MovingAverage(int size)` Initializesthe object with the size of the window `size`.
// - `double next(int val)` Returns the moving average of the last `size` values of the stream.
//
// **Example 1:**
//
// ```
// Input
//
// ["MovingAverage", "next", "next", "next", "next"]
// [[3], [1], [10], [3], [5]]
// Output
//
// [null, 1.0, 5.5, 4.66667, 6.0]
//
// Explanation
//
// MovingAverage movingAverage = new MovingAverage(3);
// movingAverage.next(1); // return 1.0 = 1 / 1
// movingAverage.next(10); // return 5.5 = (1 + 10) / 2
// movingAverage.next(3); // return 4.66667 = (1 + 10 + 3) / 3
// movingAverage.next(5); // return 6.0 = (10 + 3 + 5) / 3
// ```
//
// **Constraints:**
//
// - `1 <= size <= 1000`
// - `-10^5 <= val <= 10^5`
// - At most `10^4` calls will be made to `next`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>

using namespace std;

class MovingAverage {
  int size;
  int sum;
  queue<int> data;

 public:
  MovingAverage(int size) : size(size), sum(0) {}

  double next(int val) {
    sum += val;
    data.push(val);

    if (data.size() > size) {
      sum -= data.front();
      data.pop();
    }

    return double(sum) / data.size();
  }
};
