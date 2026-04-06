// Source: https://leetcode.com/problems/range-module
// Title: Range Module
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A Range Module is a module that tracks ranges of numbers. Design a data structure to track the ranges represented as **half-open intervals** and query about them.
//
// A **half-open interval** `[left, right)` denotes all the real numbers `x` where `left <= x < right`.
//
// Implement the `RangeModule` class:
//
// - `RangeModule()` Initializes the object of the data structure.
// - `void addRange(int left, int right)` Adds the **half-open interval** `[left, right)`, tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval `[left, right)` that are not already tracked.
// - `boolean queryRange(int left, int right)` Returns `true` if every real number in the interval `[left, right)` is currently being tracked, and `false` otherwise.
// - `void removeRange(int left, int right)` Stops tracking every real number currently being tracked in the **half-open interval** `[left, right)`.
//
// **Example 1:**
//
// ```
// Input:
// ["RangeModule", "addRange", "removeRange", "queryRange", "queryRange", "queryRange"]
// [[], [10, 20], [14, 16], [10, 14], [13, 15], [16, 17]]
//
// Output:
// [null, null, null, true, false, true]
//
// Explanation:
// RangeModule rangeModule = new RangeModule();
// rangeModule.addRange(10, 20);
// rangeModule.removeRange(14, 16);
// rangeModule.queryRange(10, 14); // return True,(Every number in [10, 14) is being tracked)
// rangeModule.queryRange(13, 15); // return False,(Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
// rangeModule.queryRange(16, 17); // return True, (The number 16 in [16, 17) is still being tracked, despite the remove operation)
// ```
//
// **Constraints:**
//
// - `1 <= left < right <= 10^9`
// - At most `10^4` calls will be made to `addRange`, `queryRange`, and `removeRange`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <map>

using namespace std;

// Tree Map + Line Sweep
//
// Store the opening & closing points of the interval into a tree map.
// It should be always alternating between START and END.
// We put END at -INF and START to INF as sentinels.
//
// To add a range, it is equalevent to set point[left]=START and point[right]=END.
// To remove a range, it is equalevent to set point[left]=END and point[right]=START.
//
// After above operation, we need preserve the START/END alternating pattern.
// If the point left of `left` has the same label, then skip point[left].
// If the point right of `right` has the same label, then skip point[right].
// Next remove every points between (left, right).
//
// To query a range, check if left of `left` is START, right of `right` is END,
// and there is no points between (left, right).
//
// Note that each point will only insert and remove once, so the time complexity is amortized O(1).
class RangeModule {
  enum class Label { START = 1, END = -1 };
  using enum Label;

  map<int, Label> points;

 public:
  RangeModule() {
    points[INT_MIN] = END;
    points[INT_MAX] = START;
  }

  void addRange(int left, int right) {
    auto prevIt = prev(points.lower_bound(left));  // prevIt < left
    if (prevIt->second != START) {
      auto [it, _] = points.insert_or_assign(left, START);
      prevIt = it;
    }

    auto nextIt = points.upper_bound(right);  // nextIt > right
    if (nextIt->second != END) {
      auto [it, _] = points.insert_or_assign(right, END);
      nextIt = it;
    }

    points.erase(next(prevIt), nextIt);
  }

  void removeRange(int left, int right) {
    auto prevIt = prev(points.lower_bound(left));  // prevIt < left
    if (prevIt->second != END) {
      auto [it, _] = points.insert_or_assign(left, END);
      prevIt = it;
    }

    auto nextIt = points.upper_bound(right);  // nextIt > right
    if (nextIt->second != START) {
      auto [it, _] = points.insert_or_assign(right, START);
      nextIt = it;
    }

    points.erase(next(prevIt), nextIt);
  }

  bool queryRange(int left, int right) const {
    auto prevIt = prev(points.upper_bound(left));  // prevIt <= left
    auto nextIt = points.lower_bound(right);       // nextIt >= right

    return prevIt->second == START && nextIt->second == END && next(prevIt) == nextIt;
  }
};
