// Source: https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level
// Title: Minimum Number of Operations to Sort a Binary Tree by Level
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `root` of a binary tree with **unique values**.
//
// In one operation, you can choose any two nodes **at the same level** and swap their values.
//
// Return the minimum number of operations needed to make the values at each level sorted in a **strictly increasing order**.
//
// The **level** of a node is the number of edges along the path between it and the root node.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/09/18/image-20220918174006-2.png
//
// ```
// Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
// Output: 3
// Explanation:
// - Swap 4 and 3. The 2^nd level becomes [3,4].
// - Swap 7 and 5. The 3^rd level becomes [5,6,8,7].
// - Swap 8 and 7. The 3^rd level becomes [5,6,7,8].
// We used 3 operations so return 3.
// It can be proven that 3 is the minimum number of operations needed.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/09/18/image-20220918174026-3.png
//
// ```
// Input: root = [1,3,2,7,6,5,4]
// Output: 3
// Explanation:
// - Swap 3 and 2. The 2^nd level becomes [2,3].
// - Swap 7 and 4. The 3^rd level becomes [4,6,5,7].
// - Swap 6 and 5. The 3^rd level becomes [4,5,6,7].
// We used 3 operations so return 3.
// It can be proven that 3 is the minimum number of operations needed.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2022/09/18/image-20220918174052-4.png
//
// ```
// Input: root = [1,2,3,4,5,6]
// Output: 0
// Explanation: Each level is already sorted in increasing order so return 0.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^5]`.
// - `1 <= Node.val <= 10^5`
// - All the values of the tree are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func minimumOperations(root *TreeNode) int {
	swaps := 0

	var currLevel []*TreeNode
	var nextLevel []*TreeNode
	currLevel = append(currLevel, root)

	for len(currLevel) > 0 {
		n := len(currLevel)
		srcVals := make([]int, 0, n)
		dstVals := make([]int, 0, n)
		posMap := make(map[int]int, n)

		for idx, node := range currLevel {
			srcVals = append(srcVals, node.Val)
			dstVals = append(dstVals, node.Val)
			posMap[node.Val] = idx

			if node.Left != nil {
				nextLevel = append(nextLevel, node.Left)
			}
			if node.Right != nil {
				nextLevel = append(nextLevel, node.Right)
			}
		}

		sort.Ints(dstVals)

		for i := 0; i < n; i++ {
			if srcVals[i] != dstVals[i] {
				swaps++

				pos := posMap[dstVals[i]]
				posMap[srcVals[i]] = pos
				srcVals[pos] = srcVals[i]
				// srcVals[pos], srcVals[i] = srcVals[i], srcVals[pos]
			}
		}

		currLevel = nextLevel
		nextLevel = nil
	}

	return swaps
}
