// Source: https://leetcode.com/problems/zigzag-iterator
// Title: Zigzag Iterator
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two vectors of integers `v1` and `v2`, implement an iterator to return their elements alternately.
//
// Implement the `ZigzagIterator` class:
//
// - `ZigzagIterator(List<int> v1, List<int> v2)` initializes the object with the two vectors `v1` and `v2`.
// - `boolean hasNext()` returns `true` if the iterator still has elements, and `false` otherwise.
// - `int next()` returns the current element of the iterator and moves the iterator to the next element.
//
// **Example 1:**
//
// ```
// Input: v1 = [1,2], v2 = [3,4,5,6]
// Output: [1,3,2,4,5,6]
// Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,3,2,4,5,6].
// ```
//
// **Example 2:**
//
// ```
// Input: v1 = [1], v2 = []
// Output: [1]
// ```
//
// **Example 3:**
//
// ```
// Input: v1 = [], v2 = [1]
// Output: [1]
// ```
//
// **Constraints:**
//
// - `0 <= v1.length, v2.length <= 1000`
// - `1 <= v1.length + v2.length <= 2000`
// - `-2^31 <= v1[i], v2[i] <= 2^31 - 1`
//
// **Follow up:** What if you are given `k` vectors? How well can your code be extended to such cases?
//
// **Clarification for the follow-up question:**
// The "Zigzag" order is not clearly defined and is ambiguous for `k > 2` cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic".
//
// **Follow-up Example:**
// ```
// Input: v1 = [1,2,3], v2 = [4,5,6,7], v3 = [8,9]
// Output: [1,4,8,2,5,9,3,6,7]
// ```
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Queue + Iterator
class ZigzagIterator {
  struct Iter {
    vector<int>::const_iterator curr;
    const vector<int>::const_iterator end;
  };

  queue<Iter> iters;

 public:
  ZigzagIterator(const vector<int>& v1, const vector<int>& v2) {
    if (!v1.empty()) iters.push({v1.cbegin(), v1.cend()});
    if (!v2.empty()) iters.push({v2.cbegin(), v2.cend()});
  }

  int next() {
    // Pop
    auto iter = iters.front();
    iters.pop();

    // Move
    int ret = *iter.curr;
    ++iter.curr;

    // Push
    if (iter.curr != iter.end) {
      iters.push(iter);
    }

    return ret;
  }

  bool hasNext() {  //
    return !iters.empty();
  }
};
