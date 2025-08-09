// Source: https://leetcode.com/problems/word-abbreviation/
// Title: Word Abbreviation
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of **distinct** strings `words`, return the minimal possible **abbreviations** for every word.
//
// The following are the rules for a string abbreviation:
//
// - The **initial** abbreviation for each word is: the first character, then the number of characters in between, followed by the last character.
// - If more than one word shares the **same** abbreviation, then perform the following operation:
//
// - **Increase** the prefix (characters in the first part) of each of their abbreviations by `1`.
//
// - For example, say you start with the words `["abcdef","abndef"]` both initially abbreviated as `"a4f"`. Then, a sequence of operations would be `["a4f","a4f"]` -> `["ab3f","ab3f"]` -> `["abc2f","abn2f"]`.
//
// - This operation is repeated until every abbreviation is **unique**.
//
// - At the end, if an abbreviation did not make a word shorter, then keep it as the original word.
//
// **Example 1:**
//
// ```
// Input: words = ["like","god","internal","me","internet","interval","intension","face","intrusion"]
// Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["aa","aaa"]
// Output: ["aa","aaa"]
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 400`
// - `2 <= words[i].length <= 400`
// - `words[i]` consists of lowercase English letters.
// - All the strings of `words` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"strconv"
)

// DFS + Trie
func wordsAbbreviation(words []string) []string {
	n := len(words)
	abbrs := make([]string, n)

	type trieKey struct {
		start byte
		end   byte
		size  int
	}

	type trieNode struct {
		children map[byte]*trieNode
		ids      []int
	}

	newTrieNode := func() *trieNode {
		return &trieNode{
			children: make(map[byte]*trieNode),
		}
	}

	tries := make(map[trieKey]*trieNode)

	// Create trie
	for id, word := range words {
		l := len(word)
		if l < 2 {
			abbrs[id] = word
			continue
		}

		// Root
		key := trieKey{word[0], word[l-1], l}
		if _, ok := tries[key]; !ok {
			tries[key] = newTrieNode()
		}
		node := tries[key]
		node.ids = append(node.ids, id)

		// Trie
		for i := 1; i < l-1; i++ {
			ch := word[i]
			if _, ok := node.children[ch]; !ok {
				node.children[ch] = newTrieNode()
			}
			node = node.children[ch]
			node.ids = append(node.ids, id)
		}
	}

	// DFS
	var dfs func(key trieKey, node *trieNode, depth int)
	dfs = func(key trieKey, node *trieNode, depth int) {
		if depth == key.size {
			return
		}

		if len(node.ids) == 1 {
			id := node.ids[0]
			word := words[id]
			l := len(word)
			abbr := word[:depth] + strconv.Itoa(l-1-depth) + string(word[l-1])
			if len(abbr) >= l {
				abbr = word
			}
			abbrs[id] = abbr
			return
		}
		for _, child := range node.children {
			dfs(key, child, depth+1)
		}
	}

	for key, trie := range tries {
		dfs(key, trie, 1)
	}

	return abbrs
}

// Greedy, Two Loop
func wordsAbbreviation2(words []string) []string {
	n := len(words)
	abbrs := make([]string, n)

	makeAbbr := func(word string, i int) string {
		l := len(word)
		if l-i <= 3 {
			return word
		}

		return word[:i+1] + strconv.Itoa(l-i-2) + word[l-1:]
	}

	for i := range n {
		abbrs[i] = makeAbbr(words[i], 0)
	}

	for i := range n {
		for l := 1; ; l++ {
			dupes := map[int]bool{}
			for j := i + 1; j < n; j++ {
				if abbrs[i] == abbrs[j] {
					dupes[j] = true
				}
			}

			if len(dupes) == 0 {
				break
			}

			dupes[i] = true
			for j := range dupes {
				abbrs[j] = makeAbbr(words[j], l)
			}
		}
	}

	return abbrs
}
