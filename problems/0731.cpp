// Source: https://leetcode.com/problems/my-calendar-ii
// Title: My Calendar II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a **triple booking**.
//
// A **triple booking** happens when three events have some non-empty intersection (i.e., some moment is common to all the three events.).
//
// The event can be represented as a pair of integers `startTime` and `endTime` that represents a booking on the half-open interval `[startTime, endTime)`, the range of real numbers `x` such that `startTime <= x < endTime`.
//
// Implement the `MyCalendarTwo` class:
//
// - `MyCalendarTwo()` Initializes the calendar object.
// - `boolean book(int startTime, int endTime)` Returns `true` if the event can be added to the calendar successfully without causing a **triple booking**. Otherwise, return `false` and do not add the event to the calendar.
//
// **Example 1:**
//
// ```
// Input:
// ["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
// [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
//
// Output:
// [null, true, true, true, false, true, true]
//
// Explanation:
// MyCalendarTwo myCalendarTwo = new MyCalendarTwo();
// myCalendarTwo.book(10, 20); // return True, The event can be booked.
// myCalendarTwo.book(50, 60); // return True, The event can be booked.
// myCalendarTwo.book(10, 40); // return True, The event can be double booked.
// myCalendarTwo.book(5, 15);  // return False, The event cannot be booked, because it would result in a triple booking.
// myCalendarTwo.book(5, 10); // return True, The event can be booked, as it does not use time 10 which is already double booked.
// myCalendarTwo.book(25, 55); // return True, The event can be booked, as the time in [25, 40) will be double booked with the third event, the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
// ```
//
// **Constraints:**
//
// - `0 <= start < end <= 10^9`
// - At most `1000` calls will be made to `book`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

// Brute-Force
class MyCalendarTwo {
  using Range = pair<int, int>;  // start, end

  vector<Range> events;

 public:
  MyCalendarTwo() {}

  bool book(int newStart, int newEnd) {
    // Find overlapping events
    auto overlaps = vector<Range>();
    for (const auto [oldStart, oldEnd] : events) {
      if (newStart < oldEnd && oldStart < newEnd) {
        overlaps.push_back(Range{max(newStart, oldStart), min(newEnd, oldEnd)});
      }
    }

    // Sort the overlaps and check double booking
    sort(overlaps.begin(), overlaps.end());
    for (int i = 1; i < overlaps.size(); ++i) {
      const auto [prevStart, prevEnd] = overlaps[i - 1];
      const auto [currStart, currEnd] = overlaps[i];
      if (prevEnd > currStart) return false;
    }

    events.push_back(Range{newStart, newEnd});
    return true;
  }
};

// Brute-Force (Optimized)
//
// Instead of finding overlaps in on booking,
// we can also store the overlaps in an array.
class MyCalendarTwo2 {
  struct Range {
    int start;
    int end;
  };

  vector<Range> events;
  vector<Range> overlaps;

 public:
  MyCalendarTwo2() {}

  bool book(int newStart, int newEnd) {
    // Find overlap to with existing overlaps
    for (const auto [overlapStart, overlapEnd] : overlaps) {
      if (newStart < overlapEnd && overlapStart < newEnd) return false;
    }

    // Insert new overlaps
    for (const auto [eventStart, eventEnd] : events) {
      if (newStart < eventEnd && eventStart < newEnd) {
        overlaps.push_back(Range{max(newStart, eventStart), min(newEnd, eventEnd)});
      }
    }

    // Insert new event
    events.push_back(Range{newStart, newEnd});

    return true;
  }
};

// Line Sweep + Tree Map
//
// Stores the start/end time in the tree map.
//
// We first try to book the new event.
// Next loop through all data and check if there is triple booking (and rollback).
//
// Note that this solution is better for k-fold booking when k is larger.
class MyCalendarTwo3 {
  map<int, int> deltas;  // time -> event count delta

 public:
  MyCalendarTwo3() {}

  bool book(int startTime, int endTime) {
    // Try to book new event
    deltas[startTime]++;
    deltas[endTime]--;

    // Loop
    int eventCount = 0;
    for (const auto [time, delta] : deltas) {
      eventCount += delta;

      // Triple booking. Rollback.
      if (eventCount >= 3) {
        deltas[startTime]--;
        deltas[endTime]++;
        if (deltas[startTime] == 0) deltas.erase(startTime);
        return false;
      }

      // Early stop
      if (time >= endTime) break;
    }

    return true;
  }
};
