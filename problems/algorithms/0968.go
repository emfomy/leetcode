// Source: https://leetcode.com/problems/binary-tree-cameras/
// Title: Binary Tree Cameras
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.
//
// Return the minimum number of cameras needed to monitor all nodes of the tree.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2018/12/29/bst_cameras_01.png
//   Input: root = [0,0,null,0,0]
//   Output: 1
//   Explanation: One camera is enough to monitor all nodes if placed as shown.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2018/12/29/bst_cameras_02.png
//   Input: root = [0,0,null,0,null,0,null,null,0]
//   Output: 2
//   Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
//
// Constraints:
//
//   The number of nodes in the tree is in the range [1, 1000].
//   Node.val == 0
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use DP

type dpTreeNode struct {
	dpCamera int // Number of cameras in subtree with a camera in this node
	dpNear   int // Number of cameras in subtree with a camera in either one child
	dpEmpty  int // Number of cameras in subtree with no camera in both children
}

func minCameraCover(root *TreeNode) int {
	dpRoot := _minCameraCover(root)
	return _min(dpRoot.dpCamera, dpRoot.dpNear)
}

func _minCameraCover(node *TreeNode) *dpTreeNode {
	if node == nil {
		return &dpTreeNode{
			dpCamera: 10_000,
			dpNear:   0,
			dpEmpty:  0,
		}
	}

	// Recursion
	dpLeft := _minCameraCover(node.Left)
	dpRight := _minCameraCover(node.Right)

	// DP
	return &dpTreeNode{
		dpCamera: _min3(
			dpLeft.dpCamera, dpLeft.dpNear, dpLeft.dpEmpty,
		) + _min3(
			dpRight.dpCamera, dpRight.dpNear, dpRight.dpEmpty,
		) + 1,
		dpNear: _min3(
			dpLeft.dpCamera+dpRight.dpCamera,
			dpLeft.dpCamera+dpRight.dpNear,
			dpLeft.dpNear+dpRight.dpCamera,
		),
		dpEmpty: dpLeft.dpNear + dpRight.dpNear,
	}
}

func _min3(a, b, c int) int {
	return _min(_min(a, b), c)
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use Greedy + DFS
//
// Idea: It is always better to put a camera at the parent of a leaf node.
// - If a node has an uncovered child, we must put a camera here.
// - If a node is not covered but has not parent, we must put a camera here.
//

func minCameraCover2(root *TreeNode) int {
	coverMap := make(map[*TreeNode]bool)
	coverMap[nil] = true
	return _minCameraCover2(root, nil, coverMap)
}

func _minCameraCover2(node *TreeNode, parent *TreeNode, coverMap map[*TreeNode]bool) int {
	if node == nil {
		return 0
	}

	res := 0
	res += _minCameraCover2(node.Left, node, coverMap)
	res += _minCameraCover2(node.Right, node, coverMap)

	if !coverMap[node.Left] || !coverMap[node.Right] || (parent == nil && !coverMap[node]) {
		res += 1
		coverMap[node] = true
		coverMap[parent] = true
		coverMap[node.Left] = true
		coverMap[node.Right] = true
	}
	return res
}
