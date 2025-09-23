// Source: https://leetcode.com/problems/find-median-from-data-stream
// Title: Find Median from Data Stream
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
//
// - For example, for `arr = [2,3,4]`, the median is `3`.
// - For example, for `arr = [2,3]`, the median is `(2 + 3) / 2 = 2.5`.
//
// Implement the MedianFinder class:
//
// - `MedianFinder()` initializes the `MedianFinder` object.
// - `void addNum(int num)` adds the integer `num` from the data stream to the data structure.
// - `double findMedian()` returns the median of all elements so far. Answers within `10^-5` of the actual answer will be accepted.
//
// **Example 1:**
//
// ```
// Input
//
// ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
// [[], [1], [2], [], [3], []]
// Output
//
// [null, null, null, 1.5, null, 2.0]
//
// Explanation
//
// MedianFinder medianFinder = new MedianFinder();
// medianFinder.addNum(1);    // arr = [1]
// medianFinder.addNum(2);    // arr = [1, 2]
// medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
// medianFinder.addNum(3);    // arr[1, 2, 3]
// medianFinder.findMedian(); // return 2.0
// ```
//
// **Constraints:**
//
// - `-10^5 <= num <= 10^5`
// - There will be at least one element in the data structure before calling `findMedian`.
// - At most `5 * 10^4` calls will be made to `addNum` and `findMedian`.
//
// **Follow up:**
//
// - If all integer numbers from the stream are in the range `[0, 100]`, how would you optimize your solution?
// - If `99%` of all integer numbers from the stream are in the range `[0, 100]`, how would you optimize your solution?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>

using namespace std;

// Use Heap
//
// Use 2 heaps, one for the smaller numbers and another for the larger numbers.
//
// If size is odd, we put medium on both heap.
//
// Let x be the new number, S / L be the smaller / larger heaps, s / l be the top numbers.
//
// For size is even:
// * If s <= x <= l, then x is the medium; put x in both heaps.
// * If x < s,       then s is the medium; put x in S and s in L.
// * If l < x,       then l is the medium; put l in S and x in L.
//
// For size is odd (s = l):
// * If s = l = x, then (x, s) is the medium pair; do nothing.
// * If x < s = l, then push x in S and pop S.
// * If s = l < x, then push x in L and pop L.
class MedianFinder {
  int size;
  priority_queue<int, vector<int>, less<int>> smalls;     // max-heap
  priority_queue<int, vector<int>, greater<int>> larges;  // min-heap

 public:
  MedianFinder() : size(0) {}

  void addNum(int num) {
    if (size == 0) {
      size = 1;
      smalls.push(num);
      larges.push(num);
      return;
    }

    auto s = smalls.top();
    auto l = larges.top();
    if (size % 2 == 0) {  // even size
      if (num < s) {
        l = s;
        s = num;
      } else if (l < num) {
        s = l;
        l = num;
      } else {
        s = num;
        l = num;
      }
      smalls.push(s);
      larges.push(l);
    } else {  // odd size
      if (num < s) {
        smalls.push(num);
        smalls.pop();
      } else if (l < num) {
        larges.push(num);
        larges.pop();
      } else {
        // do nothing
      }
    }
    ++size;
  }

  double findMedian() {  //
    return double(smalls.top() + larges.top()) / 2;
  }
};
