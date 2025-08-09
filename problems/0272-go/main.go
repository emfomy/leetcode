// Source: https://leetcode.com/problems/closest-binary-search-tree-value-ii
// Title: Closest Binary Search Tree Value II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary search tree, a `target` value, and an integer `k`, return the `k` values in the BST that are closest to the `target`. You may return the answer in **any order**.
//
// You are **guaranteed** to have only one unique set of `k` values in the BST that are closest to the `target`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/12/closest1-1-tree.jpg
//
// ```
// Input: root = [4,2,5,1,3], target = 3.714286, k = 2
// Output: [4,3]
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1], target = 0.000000, k = 1
// Output: [1]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is `n`.
// - `1 <= k <= n <= 10^4`.
// - `0 <= Node.val <= 10^9`
// - `-10^9 <= target <= 10^9`
//
// **Follow up:** Assume that the BST is balanced. Could you solve it in less than `O(n)` runtime (where `n = total nodes`)?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"

	"github.com/emirpasic/gods/v2/trees/binaryheap"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// Use Heap
func closestKValues(root *TreeNode, target float64, k int) []int {
	_abs := func(x float64) float64 {
		if x < 0 {
			return -x
		}
		return x
	}

	heap := binaryheap.NewWith(func(a, b int) int { // max heap
		diff := _abs(target-float64(a)) - _abs(target-float64(b))
		if diff > 0 {
			return -1
		}
		if diff < 0 {
			return 1
		}
		return 0
	})

	// DFS
	var dfs func(node *TreeNode)
	dfs = func(node *TreeNode) {
		if node == nil {
			return
		}

		heap.Push(node.Val)
		if heap.Size() > k {
			heap.Pop()
		}

		dfs(node.Left)
		dfs(node.Right)
	}
	dfs(root)

	return heap.Values()
}

// Convert tree to array
func closestKValues2(root *TreeNode, target float64, k int) []int {
	_abs := func(x float64) float64 {
		if x < 0 {
			return -x
		}
		return x
	}

	// DFS
	var nums []int
	var dfs func(node *TreeNode)
	dfs = func(node *TreeNode) {
		if node == nil {
			return
		}

		dfs(node.Left)
		nums = append(nums, node.Val)
		dfs(node.Right)
	}
	dfs(root)

	// Find
	n := len(nums)
	idx := sort.Search(n, func(i int) bool {
		return float64(nums[i]) >= target
	})

	// Answer
	ans := make([]int, 0, k)
	i, j := idx-1, idx
	for range k {
		if i < 0 {
			ans = append(ans, nums[j])
			j++
			continue
		}
		if j >= n {
			ans = append(ans, nums[i])
			i--
			continue
		}

		diffI := _abs(target - float64(nums[i]))
		diffJ := _abs(target - float64(nums[j]))
		if diffI < diffJ {
			ans = append(ans, nums[i])
			i--
		} else {
			ans = append(ans, nums[j])
			j++
		}
	}

	return ans
}
