// Source: https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree
// Title: Find Elements in a Contaminated Binary Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary tree with the following rules:
//
// - `root.val == 0`
// - For any `treeNode`:
//   - If `treeNode.val` has a value `x` and `treeNode.left != null`, then `treeNode.left.val == 2 * x + 1`
//   - If `treeNode.val` has a value `x` and `treeNode.right != null`, then `treeNode.right.val == 2 * x + 2`
//
// Now the binary tree is contaminated, which means all `treeNode.val` have been changed to `-1`.
//
// Implement the `FindElements` class:
//
// - `FindElements(TreeNode* root)` Initializes the object with a contaminated binary tree and recovers it.
// - `bool find(int target)` Returns `true` if the `target` value exists in the recovered binary tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/11/06/untitled-diagram-4-1.jpg
//
// ```
// Input
//
// ["FindElements","find","find"]
// [[[-1,null,-1]],[1],[2]]
// Output
//
// [null,false,true]
// Explanation
//
// FindElements findElements = new FindElements([-1,null,-1]);
// findElements.find(1); // return False
// findElements.find(2); // return True ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2019/11/06/untitled-diagram-4.jpg
//
// ```
// Input
//
// ["FindElements","find","find","find"]
// [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
// Output
//
// [null,true,true,false]
// Explanation
//
// FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
// findElements.find(1); // return True
// findElements.find(3); // return True
// findElements.find(5); // return False```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2019/11/07/untitled-diagram-4-1-1.jpg
//
// ```
// Input
//
// ["FindElements","find","find","find","find"]
// [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
// Output
//
// [null,true,false,false,true]
// Explanation
//
// FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
// findElements.find(2); // return True
// findElements.find(3); // return False
// findElements.find(4); // return False
// findElements.find(5); // return True
// ```
//
// **Constraints:**
//
// - `TreeNode.val == -1`
// - The height of the binary tree is less than or equal to `20`
// - The total number of nodes is between `[1, 10^4]`
// - Total calls of `find()` is between `[1, 10^4]`
// - `0 <= target <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type FindElements struct {
	Values map[int]bool
}

func Constructor(root *TreeNode) FindElements {
	this := FindElements{
		Values: make(map[int]bool),
	}
	root.Val = 0
	this.recovered(root)
	return this
}

func (this *FindElements) recovered(root *TreeNode) {
	this.Values[root.Val] = true
	if root.Left != nil {
		root.Left.Val = root.Val*2 + 1
		this.recovered(root.Left)
	}
	if root.Right != nil {
		root.Right.Val = root.Val*2 + 2
		this.recovered(root.Right)
	}
}

func (this *FindElements) Find(target int) bool {
	return this.Values[target]
}
