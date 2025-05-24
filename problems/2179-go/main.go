// Source: https://leetcode.com/problems/count-good-triplets-in-an-array
// Title: Count Good Triplets in an Array
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **0-indexed** arrays `nums1` and `nums2` of length `n`, both of which are **permutations** of `[0, 1, ..., n - 1]`.
//
// A **good triplet** is a set of `3` **distinct** values which are present in **increasing order** by position both in `nums1` and `nums2`. In other words, if we consider `pos1_v` as the index of the value `v` in `nums1` and `pos2)v` as the index of the value `v` in `nums2`, then a good triplet will be a set `(x, y, z)` where `0 <= x, y, z <= n - 1`, such that `pos1_x < pos1_y < pos1_z` and `pos2_x < pos2_y < pos2_z`.
//
// Return the **total number** of good triplets.
//
// **Example 1:**
//
// ```
// Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
// Output: 1
// Explanation:
// There are 4 triplets (x,y,z) such that pos1_x < pos1_y < pos1_z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3).
// Out of those triplets, only the triplet (0,1,3) satisfies pos2_x < pos2_y < pos2_z. Hence, there is only 1 good triplet.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
// Output: 4
// Explanation: The 4 good triplets are (4,0,3), (4,0,2), (4,1,3), and (4,1,2).
// ```
//
// **Constraints:**
//
// - `n == nums1.length == nums2.length`
// - `3 <= n <= 10^5`
// - `0 <= nums1[i], nums2[i] <= n - 1`
// - `nums1` and `nums2` are permutations of `[0, 1, ..., n - 1]`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// O(n^3)
func goodTriplets(nums1 []int, nums2 []int) int64 {
	n := len(nums1)

	idx2 := make([]int, n)
	for i, v := range nums2 {
		idx2[v] = i
	}

	map12 := make([]int, n) // map nums1 to nums2
	for i, v := range nums1 {
		map12[i] = idx2[v]
	}

	count := int64(0)
	for k := range n {
		for j := range k {
			if map12[j] > map12[k] {
				continue
			}
			for i := range j {
				if map12[i] > map12[j] {
					continue
				}
				count++
			}
		}
	}

	return count
}

// O(n^2)
func goodTriplets2(nums1 []int, nums2 []int) int64 {
	n := len(nums1)

	// Find mapping
	idx2 := make([]int, n)
	for i, v := range nums2 {
		idx2[v] = i
	}

	map12 := make([]int, n) // map nums1 to nums2
	for i, v := range nums1 {
		map12[i] = idx2[v]
	}

	// Find good pairs
	pairs := make(map[int][]int, n)
	for j := range n {
		for i := range j {
			if map12[i] < map12[j] {
				pairs[i] = append(pairs[i], j)
			}
		}
	}

	count := int64(0)
	for _, js := range pairs {
		for _, j := range js {
			count += int64(len(pairs[j]))
		}
	}

	return count
}

// O(nlogn), Binary Index Tree
func goodTriplets3(nums1 []int, nums2 []int) int64 {
	n := len(nums1)

	// Find mapping
	idx2 := make([]int, n)
	for i, v := range nums2 {
		idx2[v] = i
	}

	map12 := make([]int, n) // map nums1 to nums2
	for i, v := range nums1 {
		map12[i] = idx2[v]
	}

	ft := newFenwickTree(n)
	var res int64
	for value := 0; value < n; value++ {
		pos := map12[value]
		left := ft.query(pos)
		ft.update(pos, 1)
		right := (n - 1 - pos) - (value - left)
		res += int64(left * right)
	}
	return res
}

func lowbit(x int) int {
	return x & (-x)
}

type fenwickTree struct {
	tree []int
}

func newFenwickTree(n int) *fenwickTree {
	return &fenwickTree{
		tree: make([]int, n+1),
	}
}

func (ft *fenwickTree) update(index, delta int) {
	index++
	for index < len(ft.tree) {
		ft.tree[index] += delta
		index += index & -index
	}
}

func (ft *fenwickTree) query(index int) int {
	index++
	res := 0
	for index > 0 {
		res += ft.tree[index]
		index -= index & -index
	}
	return res
}
