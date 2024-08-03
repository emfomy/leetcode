// Source: https://leetcode.com/problems/insert-delete-getrandom-o1
// Title: Insert Delete GetRandom O(1)
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implement the RandomizedSet class:
//
// * RandomizedSet() Initializes the RandomizedSet object.
// * bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
// * bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
// * int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
//
// You must implement the functions of the class such that each function works in average O(1) time complexity.
//
// Example 1:
//
//   Input
//     ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
//     [[], [1], [2], [2], [], [1], [2], []]
//   Output
//     [null, true, false, true, 2, true, false, 2]
//   Explanation
//     RandomizedSet randomizedSet = new RandomizedSet();
//     randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
//     randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
//     randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
//     randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
//     randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
//     randomizedSet.insert(2); // 2 was already in the set, so return false.
//     randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
//
// Constraints:
//
//   -2^31 <= val <= 2^31-1
//   At most 2 * 10^5 calls will be made to insert, remove, and getRandom.s
//   There will be at least one element in the data structure when getRandom is called.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math/rand"
)

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * obj := Constructor();
 * param_1 := obj.Insert(val);
 * param_2 := obj.Remove(val);
 * param_3 := obj.GetRandom();
 */

type RandomizedSet struct {
	keys []int
	idxs map[int]int // map key to its index
}

func Constructor() RandomizedSet {
	return RandomizedSet{
		keys: make([]int, 0),
		idxs: make(map[int]int),
	}
}

func (this *RandomizedSet) Insert(val int) bool {
	_, exist := this.idxs[val]
	if exist {
		return false
	}

	this.keys = append(this.keys, val)
	this.idxs[val] = len(this.keys) - 1
	return true
}

func (this *RandomizedSet) Remove(val int) bool {
	idx, exist := this.idxs[val]
	if !exist {
		return false
	}

	// Swap with last element
	lastVal := this.keys[len(this.keys)-1]
	this.keys[idx] = lastVal
	this.idxs[lastVal] = idx
	delete(this.idxs, val)
	this.keys = this.keys[:len(this.keys)-1]
	return true
}

func (this *RandomizedSet) GetRandom() int {
	idx := rand.Intn(len(this.keys))
	return this.keys[idx]
}
