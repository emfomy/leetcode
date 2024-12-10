// Source: https://leetcode.com/problems/implement-trie-prefix-tree
// Title: Implement Trie (Prefix Tree)
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **trie** (https://en.wikipedia.org/wiki/Trie) (pronounced as "try") or **prefix tree**  is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
//
// Implement the Trie class:
//
// - `Trie()` Initializes the trie object.
// - `void insert(String word)` Inserts the string `word` into the trie.
// - `boolean search(String word)` Returns `true` if the string `word` is in the trie (i.e., was inserted before), and `false` otherwise.
// - `boolean startsWith(String prefix)` Returns `true` if there is a previously inserted string `word` that has the prefix `prefix`, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input
//
// ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
// Output
//
// [null, null, true, false, true, null, true]
//
// Explanation
//
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple");   // return True
// trie.search("app");     // return False
// trie.startsWith("app"); // return True
// trie.insert("app");
// trie.search("app");     // return True
// ```
//
// **Constraints:**
//
// - `1 <= word.length, prefix.length <= 2000`
// - `word` and `prefix` consist only of lowercase English letters.
// - At most `3 * 10^4` calls **in total**  will be made to `insert`, `search`, and `startsWith`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

/**
 * Your Trie object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Insert(word);
 * param_2 := obj.Search(word);
 * param_3 := obj.StartsWith(prefix);
 */

type Trie struct {
	children map[rune]*Trie // child nodes
	isWord   bool           // whether this node represent a word
}

func Constructor() Trie {
	return Trie{
		children: make(map[rune]*Trie),
	}
}

func (this *Trie) Insert(word string) {
	node := this
	for _, ch := range word {
		nextNode := node.children[ch]
		if nextNode == nil {
			newNode := Constructor()
			nextNode = &newNode
			node.children[ch] = nextNode
		}
		node = nextNode
	}
	node.isWord = true
}

func (this *Trie) Search(word string) bool {
	node := this
	for _, ch := range word {
		nextNode := node.children[ch]
		if nextNode == nil {
			return false
		}
		node = nextNode
	}
	return node.isWord
}

func (this *Trie) StartsWith(prefix string) bool {
	node := this
	for _, ch := range prefix {
		nextNode := node.children[ch]
		if nextNode == nil {
			return false
		}
		node = nextNode
	}
	return true
}
