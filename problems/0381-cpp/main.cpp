// Source: https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed
// Title: Insert Delete GetRandom O(1) - Duplicates allowed
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// `RandomizedCollection` is a data structure that contains a collection of numbers, possibly duplicates (i.e., a multiset). It should support inserting and removing specific elements and also reporting a random element.
//
// Implement the `RandomizedCollection` class:
//
// - `RandomizedCollection()` Initializes the empty `RandomizedCollection` object.
// - `bool insert(int val)` Inserts an item `val` into the multiset, even if the item is already present. Returns `true` if the item is not present, `false` otherwise.
// - `bool remove(int val)` Removes an item `val` from the multiset if present. Returns `true` if the item is present, `false` otherwise. Note that if `val` has multiple occurrences in the multiset, we only remove one of them.
// - `int getRandom()` Returns a random element from the current multiset of elements. The probability of each element being returned is **linearly related** to the number of the same values the multiset contains.
//
// You must implement the functions of the class such that each function works on **average** `O(1)` time complexity.
//
// **Note:** The test cases are generated such that `getRandom` will only be called if there is **at least one** item in the `RandomizedCollection`.
//
// **Example 1:**
//
// ```
// Input
//
// ["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
// [[], [1], [1], [2], [], [1], []]
// Output
//
// [null, true, false, true, 2, true, 1]
//
// Explanation
//
// RandomizedCollection randomizedCollection = new RandomizedCollection();
// randomizedCollection.insert(1);   // return true since the collection does not contain 1.
//                                   // Inserts 1 into the collection.
// randomizedCollection.insert(1);   // return false since the collection contains 1.
//                                   // Inserts another 1 into the collection. Collection now contains [1,1].
// randomizedCollection.insert(2);   // return true since the collection does not contain 2.
//                                   // Inserts 2 into the collection. Collection now contains [1,1,2].
// randomizedCollection.getRandom(); // getRandom should:
//                                   // - return 1 with probability 2/3, or
//                                   // - return 2 with probability 1/3.
// randomizedCollection.remove(1);   // return true since the collection contains 1.
//                                   // Removes 1 from the collection. Collection now contains [1,2].
// randomizedCollection.getRandom(); // getRandom should return 1 or 2, both equally likely.
// ```
//
// **Constraints:**
//
// - `-2^31 <= val <= 2^31 - 1`
// - At most `2 * 10^5` calls **in total** will be made to `insert`, `remove`, and `getRandom`.
// - There will be **at least one** element in the data structure when `getRandom` is called.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Multi Hash Map + Array + Key Map
//
// Assign each value a PK (auto increment, unique).
// Use RandomizedSet (previous problem) on PK.
class RandomizedCollection {
  vector<int> vals;
  vector<int> pks;
  unordered_map<int, int> pk2idx;
  unordered_multimap<int, int> val2pks;
  int lastPk = 10;

 public:
  RandomizedCollection() {}

  bool insert(int val) {
    auto pk = lastPk;
    lastPk++;

    val2pks.insert({val, pk});
    pk2idx[pk] = pks.size();
    vals.push_back(val);
    pks.push_back(pk);

    return (val2pks.count(val) == 1);
  }

  bool remove(int val) {
    auto it = val2pks.find(val);
    if (it == val2pks.cend()) return false;
    auto pk = it->second;

    int n = pks.size();
    auto idx = pk2idx[pk];
    if (idx != n - 1) {  // swap with last
      vals[idx] = vals[n - 1];
      pks[idx] = pks[n - 1];
      pk2idx[pks[idx]] = idx;
    }

    vals.pop_back();
    pks.pop_back();
    pk2idx.erase(pk);
    val2pks.erase(it);
    return true;
  }

  int getRandom() {
    int idx = rand() % vals.size();
    return vals[idx];
  }
};
