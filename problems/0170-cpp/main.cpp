// Source: https://leetcode.com/problems/two-sum-iii-data-structure-design
// Title: Two Sum III - Data structure design
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a data structure that accepts a stream of integers and checks if it has a pair of integers that sum up to a particular value.
//
// Implement the `TwoSum` class:
//
// - `TwoSum()` Initializes the `TwoSum` object, with an empty array initially.
// - `void add(int number)` Adds `number` to the data structure.
// - `boolean find(int value)` Returns `true` if there exists any pair of numbers whose sum is equal to `value`, otherwise, it returns `false`.
//
// **Example 1:**
//
// ```
// Input
//
// ["TwoSum", "add", "add", "add", "find", "find"]
// [[], [1], [3], [5], [4], [7]]
// Output
//
// [null, null, null, null, true, false]
//
// Explanation
//
// TwoSum twoSum = new TwoSum();
// twoSum.add(1);   // [] --> [1]
// twoSum.add(3);   // [1] --> [1,3]
// twoSum.add(5);   // [1,3] --> [1,3,5]
// twoSum.find(4);  // 1 + 3 = 4, return true
// twoSum.find(7);  // No two integers sum up to 7, return false
// ```
//
// **Constraints:**
//
// - `-10^5 <= number <= 10^5`
// - `-2^31 <= value <= 2^31 - 1`
// - At most `10^4` calls will be made to `add` and `find`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <map>
using namespace std;

// Hash Set + Two Pointer
class TwoSum {
  map<int64_t, bool> data;  // number -> is duplicated

 public:
  TwoSum() {}

  void add(int number) {  //
    auto it = data.find(number);
    if (it == data.cend()) {
      data[number] = false;
    } else {
      it->second = true;
    }
  }

  bool find(int value) {
    for (auto [num, dup] : data) {
      auto it = data.find(value - num);
      if (it != data.cend() && (it->first != num || it->second)) return true;
    }
    return false;
  }
};
