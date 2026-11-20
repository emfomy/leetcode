// Source: https://leetcode.com/problems/data-stream-as-disjoint-intervals
// Title: Data Stream as Disjoint Intervals
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a data stream input of non-negative integers `a_1, a_2, ..., a_n`, summarize the numbers seen so far as a list of disjoint intervals.
//
// Implement the `SummaryRanges` class:
//
// - `SummaryRanges()` Initializes the object with an empty stream.
// - `void addNum(int value)` Adds the integer `value` to the stream.
// - `int[][] getIntervals()` Returns a summary of the integers in the stream currently as a list of disjoint intervals `[start_i, end_i]`. The answer should be sorted by `start_i`.
//
// **Example 1:**
//
// ```
// Input
//
// ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
// [[], [1], [], [3], [], [7], [], [2], [], [6], []]
// Output
//
// [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
//
// Explanation
//
// SummaryRanges summaryRanges = new SummaryRanges();
// summaryRanges.addNum(1);      // arr = [1]
// summaryRanges.getIntervals(); // return [[1, 1]]
// summaryRanges.addNum(3);      // arr = [1, 3]
// summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
// summaryRanges.addNum(7);      // arr = [1, 3, 7]
// summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
// summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
// summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
// summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
// summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
// ```
//
// **Constraints:**
//
// - `0 <= value <= 10^4`
// - At most `3 * 10^4` calls will be made to `addNum` and `getIntervals`.
// - At most `10^2`calls will be made to`getIntervals`.
//
// **Follow up:** What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <map>
#include <vector>

using namespace std;

// Line Sweep + Tree Map
//
// Store value -> label in a tree map, where label represent the start/end of a interval.
//
// For each new value, check if it is in an interval looking at its left and right point.
// If the new value is in an interval, then no-op.
// If the new value is near the start/end of an interval, extend that interval.
class SummaryRanges {
  enum class Label { START, END };
  using enum Label;

  map<int, Label> points;  // must be alternating START, END, START, END, ...

 public:
  SummaryRanges() {}

  // Insert: O(log N)
  void addNum(int value) {
    // This is equal as inserting [value, value+1) interval

    // Find smaller point to check if is inside an interval
    // value+1 <= *nextIt
    auto nextIt = points.lower_bound(value + 1);
    if (nextIt != points.cend() && nextIt->second == END) return;

    // Try merge left
    // prevIt must be END since nextIt is not END
    auto prevIt = (nextIt != points.cbegin()) ? prev(nextIt) : points.cend();
    if (prevIt != points.cend() && prevIt->first == value) {
      points.erase(prevIt);
    } else {
      points[value] = START;
    }

    // Try merge right
    // nextIt must be START since it is not END
    if (nextIt != points.cend() && nextIt->first == value + 1) {
      points.erase(nextIt);
    } else {
      points[value + 1] = END;
    }
  }

  // Get: O(N)
  vector<vector<int>> getIntervals() {
    auto intervals = vector<vector<int>>();
    intervals.reserve(points.size() / 2);
    for (auto [value, label] : points) {
      if (label == START) {
        intervals.push_back(vector<int>({value, 0}));
      } else {
        intervals.back().back() = value - 1;
      }
    }
    return intervals;
  }
};
