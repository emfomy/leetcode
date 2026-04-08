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
// Use 2 heaps, one for the lower half and another for the upper half.
//
// When the total size is even, both half are the same size.
// When the total size is odd, the upper have is larger by 1.
// That is, size(lower) <= size(upper) <= size(lower)+1.
//
// When adding a number number, first put it into the lower part.
// Next move the largest from lower to upper. (rebalance)
// Next maintain the sizes.
class MedianFinder {
  using LowerHeap = priority_queue<int, vector<int>, less<>>;     // max-heap
  using UpperHeap = priority_queue<int, vector<int>, greater<>>;  // min-heap

  LowerHeap lower;
  UpperHeap upper;

 public:
  MedianFinder() {}

  void addNum(int num) {
    // Push
    lower.push(num);

    // Rebalance
    upper.push(lower.top());
    lower.pop();

    // Maintain the sizes
    if (upper.size() > lower.size() + 1) {
      lower.push(upper.top());
      upper.pop();
    }
  }

  double findMedian() {
    if (upper.size() > lower.size()) {
      return static_cast<double>(upper.top());
    } else {
      return static_cast<double>(upper.top() + lower.top()) / 2;
    }
  }
};
