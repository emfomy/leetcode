// Source: https://leetcode.com/problems/insert-delete-getrandom-o1
// Title: Insert Delete GetRandom O(1)
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implement the `RandomizedSet` class:
//
// - `RandomizedSet()` Initializes the `RandomizedSet` object.
// - `bool insert(int val)` Inserts an item `val` into the set if not present. Returns `true` if the item was not present, `false` otherwise.
// - `bool remove(int val)` Removes an item `val` from the set if present. Returns `true` if the item was present, `false` otherwise.
// - `int getRandom()` Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the **same probability** of being returned.
//
// You must implement the functions of the class such that each function works in**average**`O(1)`time complexity.
//
// **Example 1:**
//
// ```
// Input
//
// ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
// [[], [1], [2], [2], [], [1], [2], []]
// Output
//
// [null, true, false, true, 2, true, false, 2]
//
// Explanation
//
// RandomizedSet randomizedSet = new RandomizedSet();
// randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
// randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
// randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
// randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
// randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
// randomizedSet.insert(2); // 2 was already in the set, so return false.
// randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
// ```
//
// **Constraints:**
//
// - `-2^31 <= val <= 2^31 - 1`
// - At most `2 *``10^5` calls will be made to `insert`, `remove`, and `getRandom`.
// - There will be **at least one** element in the data structure when `getRandom` is called.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Hash Map + Array
//
// Use array for random get. Stores the values.
// Use hash map for fast insert/remove. Stores value to index mapping.
//
// When insert, push at the end of the array.
// When remove, swap the value to the end of the array and then pop it.
class RandomizedSet {
  vector<int> vals;
  unordered_map<int, int> val2idx;

 public:
  RandomizedSet() {}

  bool insert(int val) {
    // Check existence
    if (val2idx.contains(val)) return false;

    // Insert
    val2idx[val] = vals.size();
    vals.push_back(val);
    return true;
  }

  bool remove(int val) {
    // Check existence
    const auto it = val2idx.find(val);
    if (it == val2idx.cend()) return false;

    // Get values
    const int idx = it->second;
    const int lastVal = vals.back();

    // Remove
    val2idx.erase(it);
    vals.pop_back();

    // Move last to here
    if (val != lastVal) {
      val2idx[lastVal] = idx;
      vals[idx] = lastVal;
    }
    return true;
  }

  int getRandom() {  //
    return vals[rand() % vals.size()];
  }
};
