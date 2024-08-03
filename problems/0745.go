// Source: https://leetcode.com/problems/prefix-and-suffix-search
// Title: Prefix and Suffix Search
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a special dictionary with some words that searchs the words in it by a prefix and a suffix.
//
// Implement the WordFilter class:
//
//   WordFilter(string[] words) Initializes the object with the words in the dictionary.
//   f(string prefix, string suffix) Returns the index of the word in the dictionary, which has the prefix prefix and the suffix suffix. If there is more than one valid index, return the largest of them. If there is no such word in the dictionary, return -1.
//
// Example 1:
//
//   Input
//     ["WordFilter", "f"]
//     [[["apple"]], ["a", "e"]]
//   Output
//     [null, 0]
//   Explanation
//     WordFilter wordFilter = new WordFilter(["apple"]);
//     wordFilter.f("a", "e"); // return 0, because the word at index 0 has prefix = "a" and suffix = 'e".
//
// Constraints:
//
//   1 <= words.length <= 15000
//   1 <= words[i].length <= 10
//   1 <= prefix.length, suffix.length <= 10
//   words[i], prefix and suffix consist of lower-case English letters only.
//   At most 15000 calls will be made to the function f.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

/**
 * Your WordFilter object will be instantiated and called as such:
 * obj := Constructor(words);
 * param_1 := obj.F(prefix,suffix);
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use Trie
//
// For each word (e.g. apple), insert #apple, e#apple, le#apple, ..., apple#apple to the trie
// To query, search <suffix>#<prefix> in the trie

type WordFilter struct {
	root *trieNode
}

func Constructor(words []string) WordFilter {
	root := newTrieNode()
	root.val = -1

	for idx, word := range words {
		lWord := len(word)
		for j := 0; j <= lWord; j++ {
			root.insert(word[lWord-j:]+"#"+word, idx)
		}
	}

	return WordFilter{
		root: root,
	}
}

func (this *WordFilter) F(prefix string, suffix string) int {
	return this.root.search(suffix + "#" + prefix)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

type trieNode struct {
	children map[rune]*trieNode
	val      int
}

func newTrieNode() *trieNode {
	return &trieNode{
		children: make(map[rune]*trieNode),
	}
}

func (node *trieNode) insert(word string, val int) {
	for _, ch := range word {
		nextNode := node.children[ch]
		if nextNode == nil {
			nextNode = newTrieNode()
			node.children[ch] = nextNode
		}
		nextNode.val = val
		node = nextNode
	}
}

func (node *trieNode) search(word string) int {
	for _, ch := range word {
		nextNode := node.children[ch]
		if nextNode == nil {
			return -1
		}
		node = nextNode
	}
	return node.val
}
