// Source: https://leetcode.com/problems/n-ary-tree-preorder-traversal/
// Title: N-ary Tree Preorder Traversal
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the root of an n-ary tree, return the preorder traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png
//   Input: root = [1,null,3,2,4,null,5,6]
//   Output: [1,3,5,6,2,4]
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png
//   Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
//   Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
//
// Constraints:
//
//   The number of nodes in the tree is in the range [0, 10^4].
//   0 <= Node.val <= 10^4
//   The height of the n-ary tree is less than or equal to 1000.
//
// Follow up: Recursive solution is trivial, could you do it iteratively?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type Node struct {
	Val      int
	Children []*Node
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Recursion
func preorder(root *Node) []int {
	if root == nil {
		return nil
	}

	res := make([]int, 0)

	_preorder(root, &res)

	return res
}

func _preorder(root *Node, res *[]int) {
	*res = append(*res, root.Val)
	for _, child := range root.Children {
		_preorder(child, res)
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Iteration
func preorder2(root *Node) []int {
	if root == nil {
		return nil
	}

	res := make([]int, 0)

	stack := newStackType()
	stack.push(root)

	// Push
	for stack.len > 0 { // stack no empty
		node := stack.pop() // pop top
		res = append(res, node.Val)

		for i := len(node.Children) - 1; i >= 0; i-- { // push children
			stack.push(node.Children[i])
		}
	}

	return res
}

type stackType struct {
	arr []*Node
	len int
}

func newStackType() *stackType {
	return &stackType{
		arr: make([]*Node, 0),
		len: 0,
	}
}

func (s *stackType) pop() *Node {
	s.len--
	return s.arr[s.len]
}

func (s *stackType) push(v *Node) {
	if s.len < len(s.arr) {
		s.arr[s.len] = v
	} else {
		s.arr = append(s.arr, v)
	}
	s.len++
}
