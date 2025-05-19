// Source: https://leetcode.com/problems/design-a-number-container-system
// Title: Design a Number Container System
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a number container system that can do the following:
//
// - **Insert** or **Replace** a number at the given index in the system.
// - **Return** the smallest index for the given number in the system.
//
// Implement the `NumberContainers` class:
//
// - `NumberContainers()` Initializes the number container system.
// - `void change(int index, int number)` Fills the container at `index` with the `number`. If there is already a number at that `index`, replace it.
// - `int find(int number)` Returns the smallest index for the given `number`, or `-1` if there is no index that is filled by `number` in the system.
//
// **Example 1:**
//
// ```
// Input
//
// ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
// [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
// Output
//
// [null, -1, null, null, null, null, 1, null, 2]
//
// Explanation
//
// NumberContainers nc = new NumberContainers();
// nc.find(10); // There is no index that is filled with number 10. Therefore, we return -1.
// nc.change(2, 10); // Your container at index 2 will be filled with number 10.
// nc.change(1, 10); // Your container at index 1 will be filled with number 10.
// nc.change(3, 10); // Your container at index 3 will be filled with number 10.
// nc.change(5, 10); // Your container at index 5 will be filled with number 10.
// nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5. Since the smallest index that is filled with 10 is 1, we return 1.
// nc.change(1, 20); // Your container at index 1 will be filled with number 20. Note that index 1 was filled with 10 and then replaced with 20.
// nc.find(10); // Number 10 is at the indices 2, 3, and 5. The smallest index that is filled with 10 is 2. Therefore, we return 2.
// ```
//
// **Constraints:**
//
// - `1 <= index, number <= 10^9`
// - At most `10^5` calls will be made **in total** to `change` and `find`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// Sort at change
type NumberContainers struct {
	idx2num  map[int]int
	num2idxs map[int][]int
}

func Constructor() NumberContainers {
	return NumberContainers{
		idx2num:  make(map[int]int),
		num2idxs: make(map[int][]int),
	}
}

func (this *NumberContainers) Change(index int, number int) {
	oldNumber, ok := this.idx2num[index]
	if ok {
		if oldNumber == number {
			return
		}
		this._remove(index, oldNumber)
	}
	this._insert(index, number)
	this.idx2num[index] = number
}

func (this *NumberContainers) Find(number int) int {
	if len(this.num2idxs[number]) == 0 {
		return -1
	}
	return this.num2idxs[number][0]
}

func (this *NumberContainers) _remove(index int, number int) {
	pos, _ := slices.BinarySearch(this.num2idxs[number], index)
	this.num2idxs[number] = slices.Delete(this.num2idxs[number], pos, pos+1)
}

func (this *NumberContainers) _insert(index int, number int) {
	pos, _ := slices.BinarySearch(this.num2idxs[number], index)
	this.num2idxs[number] = slices.Insert(this.num2idxs[number], pos, index)
}

// Sort at find
type NumberContainers2 struct {
	idx2num   map[int]int
	num2idxs  map[int][]int
	numSorted map[int]bool
}

func Constructor2() NumberContainers2 {
	return NumberContainers2{
		idx2num:   make(map[int]int),
		num2idxs:  make(map[int][]int),
		numSorted: make(map[int]bool),
	}
}

func (this *NumberContainers2) Change(index int, number int) {
	oldNumber, ok := this.idx2num[index]
	if ok {
		if oldNumber == number {
			return
		}
		this._remove(index, oldNumber)
	}
	this._insert(index, number)
	this.idx2num[index] = number
}

func (this *NumberContainers2) Find(number int) int {
	if len(this.num2idxs[number]) == 0 {
		return -1
	}
	if !this.numSorted[number] {
		this.numSorted[number] = true
		slices.Sort(this.num2idxs[number])
	}
	return this.num2idxs[number][0]
}

func (this *NumberContainers2) _remove(index int, number int) {
	n := len(this.num2idxs[number])
	pos := 0
	for ; pos < n; pos++ {
		if this.num2idxs[number][pos] == index {
			break
		}
	}
	this.num2idxs[number][pos] = this.num2idxs[number][n-1]
	this.num2idxs[number] = this.num2idxs[number][:n-1]
	this.numSorted[number] = false
}

func (this *NumberContainers2) _insert(index int, number int) {
	this.num2idxs[number] = append(this.num2idxs[number], index)
	this.numSorted[number] = false
}
