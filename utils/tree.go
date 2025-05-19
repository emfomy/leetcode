package utils

import (
	"fmt"
	"math"
	"strings"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

var null = math.MinInt

func array2Tree(arr ...int) *TreeNode {
	n := len(arr)

	nodes := make([]*TreeNode, 0, n)
	for _, val := range arr {
		var node *TreeNode
		if val != null {
			node = &TreeNode{
				Val: val,
			}
		}
		nodes = append(nodes, node)
	}

	kidIdx := 1
	for _, node := range nodes {
		if node == nil {
			continue
		}
		{
			if kidIdx >= n {
				break
			}
			kid := nodes[kidIdx]
			node.Left = kid
			kidIdx++
		}
		{
			if kidIdx >= n {
				break
			}
			kid := nodes[kidIdx]
			node.Right = kid
			kidIdx++
		}
	}

	return nodes[0]
}

func printTree(node *TreeNode, depth int) {
	fmt.Printf("%s%d\n", strings.Repeat("\t", depth), node.Val)
	if node.Left != nil {
		printTree(node.Left, depth+1)
	}
	if node.Right != nil {
		printTree(node.Right, depth+1)
	}
}
