// Source: https://leetcode.com/problems/design-most-recently-used-queue
// Title: Design Most Recently Used Queue
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a queue-like data structure that moves the most recently used element to the end of the queue.
//
// Implement the `MRUQueue` class:
//
// - `MRUQueue(int n)` constructs the `MRUQueue` with `n` elements: `[1,2,3,...,n]`.
// - `int fetch(int k)` moves the `k^th` element **(1-indexed)** to the end of the queue and returns it.
//
// **Example 1:**
//
// ```
// Input:
// ["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
// [[8], [3], [5], [2], [8]]
// Output:
// [null, 3, 6, 2, 2]
//
// Explanation:
// MRUQueue mRUQueue = new MRUQueue(8); // Initializes the queue to [1,2,3,4,5,6,7,8].
// mRUQueue.fetch(3); // Moves the 3^rd element (3) to the end of the queue to become [1,2,4,5,6,7,8,3] and returns it.
// mRUQueue.fetch(5); // Moves the 5^th element (6) to the end of the queue to become [1,2,4,5,7,8,3,6] and returns it.
// mRUQueue.fetch(2); // Moves the 2^nd element (2) to the end of the queue to become [1,4,5,7,8,3,6,2] and returns it.
// mRUQueue.fetch(8); // The 8^th element (2) is already at the end of the queue so just return it.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2000`
// - `1 <= k <= n`
// - At most `2000` calls will be made to `fetch`.
//
// **Follow up:** Finding an `O(n)` algorithm per `fetch` is a bit easy. Can you find an algorithm with a better complexity for each `fetch` call?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

using namespace std;

// Use array
class MRUQueue {
  vector<int> data;

 public:
  MRUQueue(int n) : data(n) {  //
    iota(data.begin(), data.end(), 1);
  }

  int fetch(int k) {
    --k;
    auto val = data[k];
    data.erase(data.begin() + k);
    data.push_back(val);
    return val;
  }
};

// Use array of linked list
// Each list has size sqrt(n) (total sqrt(n) lists)
//
// To fetch, we first find the list containing k-th element. O(sqrt(n))
// Next pop that value. O(sqrt(n))
// Next for each list after that element, move the head to the tail of previous list. O(sqrt(n))
// Finally push the value at the end. O(1)
class MRUQueue2 {
  vector<list<int>> data;
  int m;

 public:
  MRUQueue2(int n) : m(sqrt(n)) {
    for (auto i = 0; i < n; ++i) {
      if (i % m == 0) data.push_back(list<int>());
      data.back().push_back(i + 1);
    }
  }

  int fetch(int k) {
    int mm = data.size();
    --k;
    auto i = k / m, j = k % m;

    // Find element
    auto it = data[i].begin();
    advance(it, j);
    auto val = *it;
    data[i].erase(it);

    // Shift
    for (auto ii = i + 1; ii < mm; ++ii) {
      data[ii - 1].push_back(data[ii].front());
      data[ii].pop_front();
    }

    // Pop tail
    data.back().push_back(val);

    return val;
  }
};
