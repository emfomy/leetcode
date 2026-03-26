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

#include <algorithm>
#include <bit>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// Linked List
class MRUQueue {
  list<int> data;

 public:
  MRUQueue(int n) : data(n) {  //
    iota(data.begin(), data.end(), 1);
  }

  int fetch(int k) {
    auto it = data.cbegin();             // 1-th item
    advance(it, k - 1);                  // k-th item
    data.splice(data.cend(), data, it);  // move to end
    return *it;
  }
};

// Array + Tree Set
//
// Use a incremental id as timestamp.
//
// Use an array to store item -> timestamp.
// Use a treemap to store timestamp -> item.
//
// After any operation, increate the timestamp.
class MRUQueue2 {
  int now;

  vector<int> val2ts;    // value -> timestamp
  map<int, int> ts2val;  // timestamp -> value

 public:
  MRUQueue2(int n) : val2ts(n + 1) {
    for (int i = 1; i <= n; ++i) {
      val2ts[i] = i;
      ts2val[i] = i;
    }
    now = n;
  }

  int fetch(int k) {
    // Find k-th item
    auto it = ts2val.cbegin();  // 1-th item
    advance(it, k - 1);         // k-th item
    const int val = it->second;

    // Move to end
    ++now;
    val2ts[val] = now;
    ts2val.erase(it);
    ts2val[now] = val;

    return val;
  }
};

// Array + Fenwick Tree + Binary Search
//
// Consider the count of item on timestamp.
// Let B[t] = 1 if there is an item at t,
// Since there are at most 2000 calls on this queue,
// we can preallocate B with size n+2000.
//
// Use Fenwick Tree on B to find the k-th item.
// We can use binary search, and apply Fenwick's query to do prefix count.
class MRUQueue3 {
  constexpr static int kMaxFetch = 2000;
  struct FenwickTree {
    int m;
    vector<int> tree;  // sum of [i-lowbit(i), i)

    FenwickTree(int m) : m(m), tree(m + 1, 0) {}

    // Update: O(logM); nums[idx] += delta
    void update(int idx, int delta) {
      for (int i = idx + 1; i <= m; i += (i & -i)) {
        tree[i] += delta;
      }
    }

    // Query: O(logM); sum of [0, r]
    int query(int r) {
      int sum = 0;
      for (int i = r + 1; i >= 1; i -= (i & -i)) {
        sum += tree[i];
      }
      return sum;
    }
  };

  int now;
  vector<int> val2ts;  // value -> timestamp
  vector<int> ts2val;  // timestamp -> value
  FenwickTree tsTree;  // prefix count of ts2val

 public:
  MRUQueue3(int n) : val2ts(n + 1), ts2val(n + 1 + kMaxFetch), tsTree(n + 1 + kMaxFetch) {
    for (int i = 1; i <= n; ++i) {
      val2ts[i] = i;
      ts2val[i] = i;
      tsTree.update(i, 1);
    }
    now = n;
  }

  int fetch(int k) {
    // Binary search to find k-th item
    // query(lo-1) < k, query(hi) >=k
    int lo = 0, hi = now;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (tsTree.query(mid) >= k) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    const int val = ts2val[hi];

    // Move to end
    ++now;
    val2ts[val] = now;
    ts2val[hi] = 0;
    ts2val[now] = val;
    tsTree.update(hi, -1);
    tsTree.update(now, 1);

    return val;
  }
};

// Array + Fenwick Tree
//
// Consider the count of item on timestamp.
// Let B[t] = 1 if there is an item at t,
// Since there are at most 2000 calls on this queue,
// we can preallocate B with size n+2000.
//
// Use Fenwick Tree on B to find the k-th item.
class MRUQueue4 {
  constexpr static int kMaxFetch = 2000;
  struct FenwickTree {
    int m;
    vector<int> tree;  // sum of [i-lowbit(i), i)

    FenwickTree(int m) : m(m), tree(m + 1, 0) {}

    // Update: O(logM); nums[idx] += delta
    void update(int idx, int delta) {
      for (int i = idx + 1; i <= m; i += (i & -i)) {
        tree[i] += delta;
      }
    }

    // Query: O(logM); find first r with sum [0, r) < k i.e. sum [0, r] >= k
    int queryFirst(int k) {
      int r = 0;
      int highbit = 1 << bit_width(static_cast<unsigned int>(m - 1));
      for (int b = highbit; b > 0 && k > 0; b >>= 1) {
        if (r + b <= m && tree[r + b] < k) {
          r += b;
          k -= tree[r];
        }
      }
      return r;
    }
  };

  int now;
  vector<int> val2ts;  // value -> timestamp
  vector<int> ts2val;  // timestamp -> value
  FenwickTree tsTree;  // prefix count of ts2val

 public:
  MRUQueue4(int n) : val2ts(n + 1), ts2val(n + 1 + kMaxFetch), tsTree(n + 1 + kMaxFetch) {
    for (int i = 1; i <= n; ++i) {
      val2ts[i] = i;
      ts2val[i] = i;
      tsTree.update(i, 1);
    }
    now = n;
  }

  int fetch(int k) {
    // Find k-th item
    int ts = tsTree.queryFirst(k);
    const int val = ts2val[ts];

    // Move to end
    ++now;
    val2ts[val] = now;
    ts2val[ts] = 0;
    ts2val[now] = val;
    tsTree.update(ts, -1);
    tsTree.update(now, 1);

    return val;
  }
};
