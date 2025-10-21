// Source: https://leetcode.com/problems/serialize-and-deserialize-binary-tree
// Title: Serialize and Deserialize Binary Tree
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
//
// Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
//
// **Clarification:** The input/output format is the same as **how LeetCode serializes a binary tree** (https://support.leetcode.com/hc/en-us/articles/32442719377939-How-to-create-test-cases-on-LeetCode#h_01J5EGREAW3NAEJ14XC07GRW1A). You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/09/15/serdeser.jpg
//
// ```
// Input: root = [1,2,3,null,null,4,5]
// Output: [1,2,3,null,null,4,5]
// ```
//
// **Example 2:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 10^4]`.
// - `-1000 <= Node.val <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "encoding/json"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// Use JSON serializer
type Codec struct {
}

func Constructor() Codec {
	return Codec{}
}

// Serializes a tree to a single string.
func (this *Codec) serialize(root *TreeNode) string {
	if root == nil {
		return ""
	}

	str, _ := json.Marshal(root)
	return string(str)
}

// Deserializes your encoded data to tree.
func (this *Codec) deserialize(data string) *TreeNode {
	if data == "" {
		return nil
	}

	obj := &TreeNode{}
	_ = json.Unmarshal([]byte(data), obj)
	return obj
}
