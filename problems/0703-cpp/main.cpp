// Source: https://leetcode.com/problems/kth-largest-element-in-a-stream
// Title: Kth Largest Element in a Stream
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are part of a university admissions office and need to keep track of the `kth` highest test score from applicants in real-time. This helps to determine cut-off marks for interviews and admissions dynamically as new applicants submit their scores.
//
// You are tasked to implement a class which, for a given integer`k`, maintains a stream of test scores and continuously returns the`k`th highest test score**after**a new score has been submitted. More specifically, we are looking for the `k`th highest score in the sorted list of all scores.
//
// Implement the`KthLargest` class:
//
// - `KthLargest(int k, int[] nums)` Initializes the object with the integer `k` and the stream of test scores`nums`.
// - `int add(int val)` Adds a new test score`val` to the stream and returns the element representing the `k^th` largest element in the pool of test scores so far.
//
// **Example 1:**
//
// ```
// Input:
// ["KthLargest", "add", "add", "add", "add", "add"]
// [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
//
// Output: [null, 4, 5, 5, 8, 8]
//
// Explanation:
// KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
// kthLargest.add(3); // return 4
// kthLargest.add(5); // return 5
// kthLargest.add(10); // return 5
// kthLargest.add(9); // return 8
// kthLargest.add(4); // return 8
// ```
//
// **Example 2:**
//
// ```
// Input:
// ["KthLargest", "add", "add", "add", "add"]
// [[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]
//
// Output: [null, 7, 7, 7, 8]
//
// Explanation:
// KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
// kthLargest.add(2); // return 7
// kthLargest.add(10); // return 7
// kthLargest.add(9); // return 7
// kthLargest.add(9); // return 8
// ```
//
// **Constraints:**
//
// - `0 <= nums.length <= 10^4`
// - `1 <= k <= nums.length + 1`
// - `-10^4 <= nums[i] <= 10^4`
// - `-10^4 <= val <= 10^4`
// - At most `10^4` calls will be made to `add`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <vector>

using namespace std;

// Heap
class KthLargest {
  using Heap = priority_queue<int, vector<int>, greater<>>;  // min-heap

  const int k;
  Heap heap;

 public:
  KthLargest(const int k, const vector<int>& nums) : k(k) {
    for (const int val : nums) add(val);
  }

  int add(int val) {
    heap.push(val);
    while (heap.size() > k) heap.pop();
    return heap.top();
  }
};
