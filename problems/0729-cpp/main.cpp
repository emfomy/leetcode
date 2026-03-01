// Source: https://leetcode.com/problems/my-calendar-i
// Title: My Calendar I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a **double booking**.
//
// A **double booking** happens when two events have some non-empty intersection (i.e., some moment is common to both events.).
//
// The event can be represented as a pair of integers `startTime` and `endTime` that represents a booking on the half-open interval `[startTime, endTime)`, the range of real numbers `x` such that `startTime <= x < endTime`.
//
// Implement the `MyCalendar` class:
//
// - `MyCalendar()` Initializes the calendar object.
// - `boolean book(int startTime, int endTime)` Returns `true` if the event can be added to the calendar successfully without causing a **double booking**. Otherwise, return `false` and do not add the event to the calendar.
//
// **Example 1:**
//
// ```
// Input:
// ["MyCalendar", "book", "book", "book"]
// [[], [10, 20], [15, 25], [20, 30]]
//
// Output:
// [null, true, false, true]
//
// Explanation:
// MyCalendar myCalendar = new MyCalendar();
// myCalendar.book(10, 20); // return True
// myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
// myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20.```
//
// **Constraints:**
//
// - `0 <= start < end <= 10^9`
// - At most `1000` calls will be made to `book`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <set>
#include <vector>

using namespace std;

// Brute-Force
class MyCalendar {
  struct Event {
    int start;
    int end;
  };

  vector<Event> events;

 public:
  MyCalendar() {}

  bool book(int startTime, int endTime) {
    // Find overlap
    for (const auto& event : events) {
      if (startTime < event.end && event.start < endTime) return false;
    }

    events.push_back({startTime, endTime});
    return true;
  }
};

// Tree Set + Binary Search
//
// Say we have a new event (newStart, newEnd).
//
// Find the next event (nextStart, nextEnd) (i.e. newStart <= nextStart).
// If the next event starts before current one ends (i.e. newStart <= nextStart < newEnd),
// then there is overlap.
//
// Find the previous event (prevStart, prevEnd) (i.e. prevStart <= newStart).
// If the previous event end after current one starts (i.e. prevStart <= newStart < prevEnd),
// then there is overlap.
class MyCalendar2 {
  using Event = pair<int, int>;  // start, end

  set<Event> events;

 public:
  MyCalendar2() {}

  bool book(int startTime, int endTime) {
    const auto event = Event{startTime, endTime};

    // Find next/previous event
    const auto nextIt = events.lower_bound(event);
    if (nextIt != events.end() && nextIt->first < endTime) return false;
    if (nextIt != events.begin() && startTime < prev(nextIt)->second) return false;

    events.insert(event);
    return true;
  }
};

// Line Sweep + Tree Map
//
// Stores the start/end time in the tree map.
//
// We first try to book the new event.
// Next loop through all data and check if there is double booking (and rollback).
//
// Note that this solution is better for k-fold booking when k is larger.
class MyCalendar3 {
  map<int, int> deltas;

 public:
  MyCalendar3() {}

  bool book(int startTime, int endTime) {
    // Try to book new event
    deltas[startTime]++;
    deltas[endTime]--;

    int eventCount = 0;
    for (const auto [time, delta] : deltas) {
      eventCount += delta;

      // Double booking. Rollback.
      if (eventCount >= 2) {
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

// Segment Tree
//
// We can use segment tree instead of tree set.
// We should use tree-based implementation (instead of array-based).
// It should support lazy flag (for range update).
// It should support lazy node creation (since the time range is too large).
class MyCalendar4 {};
