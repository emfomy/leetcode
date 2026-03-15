// Source: https://leetcode.com/problems/fancy-sequence
// Title: Fancy Sequence
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write an API that generates fancy sequences using the `append`, `addAll`, and `multAll` operations.
//
// Implement the `Fancy` class:
//
// - `Fancy()` Initializes the object with an empty sequence.
// - `void append(val)` Appends an integer `val` to the end of the sequence.
// - `void addAll(inc)` Increments all existing values in the sequence by an integer `inc`.
// - `void multAll(m)` Multiplies all existing values in the sequence by an integer `m`.
// - `int getIndex(idx)` Gets the current value at index `idx` (0-indexed) of the sequence **modulo** `10^9 + 7`. If the index is greater or equal than the length of the sequence, return `-1`.
//
// **Example 1:**
//
// ```
// Input
//
// ["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
// [[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
// Output
//
// [null, null, null, null, null, 10, null, null, null, 26, 34, 20]
//
// Explanation
//
// Fancy fancy = new Fancy();
// fancy.append(2);   // fancy sequence: [2]
// fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
// fancy.append(7);   // fancy sequence: [5, 7]
// fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
// fancy.getIndex(0); // return 10
// fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
// fancy.append(10);  // fancy sequence: [13, 17, 10]
// fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
// fancy.getIndex(0); // return 26
// fancy.getIndex(1); // return 34
// fancy.getIndex(2); // return 20
// ```
//
// **Constraints:**
//
// - `1 <= val, inc, m <= 100`
// - `0 <= idx <= 10^5`
// - At most `10^5` calls total will be made to `append`, `addAll`, `multAll`, and `getIndex`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// We don't update the original value x.
// Instead, we use two variables a and b. (Initially, a = 1 and b = 0).
// When getIndex, we output ax+b.
// When addAll(y), then append (y-b)/a.
// When addAll(p), then b += p.
// When multAll(q), then a *= q and b *= q.
class Fancy {
  constexpr static int64_t modulo = 1e9 + 7;

  int64_t a = 1, b = 0, invA = 1;
  vector<int64_t> data;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

  inline int64_t fastPow(int64_t x, int n) {  //
    int64_t res = 1;
    while (n > 0) {
      if (n % 2) res = mod(res * x);
      x = mod(x * x);
      n /= 2;
    }
    return res;
  }

  inline int64_t fastInv(int64_t x) {  //
    return fastPow(x, modulo - 2);
  }

 public:
  void append(int val) {  //
    data.push_back(mod((val - b) * invA));
  }

  void addAll(int inc) {  //
    b = mod(b + inc);
  }

  void multAll(int m) {  //
    a = mod(a * m);
    b = mod(b * m);
    invA = fastInv(a);
  }

  int getIndex(int idx) {  //
    if (idx < 0 || idx >= data.size()) return -1;
    return mod(data[idx] * a + b);
  }
};

// We compute inv(a) lazily.
// We reset invA to 0 after `multAll` (indicate that this value is outdated),
// and compute it on the following `append`.
class Fancy2 {
  constexpr static int64_t modulo = 1e9 + 7;

  int64_t a = 1, b = 0, invA = 1;
  vector<int64_t> data;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

  inline int64_t fastPow(int64_t x, int n) {  //
    int64_t res = 1;
    while (n > 0) {
      if (n % 2) res = mod(res * x);
      x = mod(x * x);
      n /= 2;
    }
    return res;
  }

  inline int64_t fastInv(int64_t x) {  //
    return fastPow(x, modulo - 2);
  }

 public:
  void append(int val) {  //
    if (invA == 0) invA = fastInv(a);
    data.push_back(mod((val - b) * invA));
  }

  void addAll(int inc) {  //
    b = mod(b + inc);
  }

  void multAll(int m) {  //
    a = mod(a * m);
    b = mod(b * m);
    invA = 0;  // mark outdated
  }

  int getIndex(int idx) {  //
    if (idx < 0 || idx >= data.size()) return -1;
    return mod(data[idx] * a + b);
  }
};
