// Source: https://leetcode.com/problems/short-encoding-of-words/
// Title: Short Encoding of Words
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A valid encoding of an array of words is any reference string s and array of indices indices such that:
//
//   words.length == indices.length
//   The reference string s ends with the '#' character.
//   For each index indices[i], the substring of s starting from indices[i] and up to (but not including) the next '#' character is equal to words[i].
//
// Given an array of words, return the length of the shortest reference string s possible of any valid encoding of words.
//
// Example 1:
//
//   Input: words = ["time", "me", "bell"]
//   Output: 10
//   Explanation:
//     A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
//     words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
//     words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
//     words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"
//
// Example 2:
//
//   Input: words = ["t"]
//   Output: 2
//   Explanation: A valid encoding would be s = "t#" and indices = [0].
//
// Constraints:
//
//   1 <= words.length <= 2000
//   1 <= words[i].length <= 7
//   words[i] consists of only lowercase letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// Use Suffix Trie

type void struct{}

func minimumLengthEncoding(words []string) int {
	root := newTrieNode()
	nodes := make(map[*trieNode]void, len(words))

	// Insert words into trie
	for _, word := range words {
		node := root
		for i := len(word) - 1; i >= 0; i-- {
			ch := word[i]
			nextNode := node.children[ch]
			if nextNode == nil {
				nextNode = newTrieNode()
				node.children[ch] = nextNode
			}
			node = nextNode
		}

		node.depth = len(word) + 1
		nodes[node] = void{}
	}

	// Get length of leaves
	res := 0
	for node := range nodes {
		if len(node.children) == 0 {
			res += node.depth
		}
	}

	return res
}

type trieNode struct {
	children map[byte]*trieNode
	depth    int
}

func newTrieNode() *trieNode {
	return &trieNode{
		children: make(map[byte]*trieNode),
	}
}

func main() {
	res := minimumLengthEncoding([]string{"time", "atime", "btime"})
	fmt.Println(res)
}
