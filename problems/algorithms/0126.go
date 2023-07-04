// Source: https://leetcode.com/problems/word-ladder-ii/
// Title: Word Ladder II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
//
//   Every adjacent pair of words differs by a single letter.
//   Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
//   sk == endWord
//
//   Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
//
// Example 1:
//
//   Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
//   Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
//   Explanation:
//     There are 2 shortest transformation sequences:
//     "hit" -> "hot" -> "dot" -> "dog" -> "cog"
//     "hit" -> "hot" -> "lot" -> "log" -> "cog"
//
// Example 2:
//
//   Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
//   Output: []
//   Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
//
// Constraints:
//
//   1 <= beginWord.length <= 5
//   endWord.length == beginWord.length
//   1 <= wordList.length <= 500
//   wordList[i].length == beginWord.length
//   beginWord, endWord, and wordList[i] consist of lowercase English letters.
//   beginWord != endWord
//   All the words in wordList are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func findLadders(beginWord string, endWord string, wordList []string) [][]string {
	n := len(wordList)

	// Adjacency matrix
	adj := make(map[string][]string, n)
	for _, word := range wordList {
		if _isAdj(beginWord, word) {
			adj[beginWord] = append(adj[beginWord], word)
		}
	}
	for _, word1 := range wordList {
		adj[word1] = make([]string, 0, n)
		for _, word2 := range wordList {
			if _isAdj(word1, word2) {
				adj[word1] = append(adj[word1], word2)
			}
		}
	}

	// BFS
	prevList := [][]string{{beginWord}}
	nextList := make([][]string, 0)
	res := make([][]string, 0)

	for k := 0; k < n; k++ {
		found := false
		for _, prevSeq := range prevList {
			prevWord := prevSeq[len(prevSeq)-1]
			for _, nextWord := range adj[prevWord] {
				nextSeq := _copy(prevSeq, nextWord)
				if nextWord == endWord {
					found = true
					res = append(res, nextSeq)
				}
				nextList = append(nextList, nextSeq)
			}
		}
		if found {
			break
		}
		prevList = nextList
		nextList = make([][]string, 0)
	}

	return res
}

func _isAdj(word1, word2 string) bool {
	cnt := 0
	for i := 0; i < len(word1); i++ {
		c1 := word1[i]
		c2 := word2[i]
		if c1 != c2 {
			cnt++
		}
	}
	return cnt == 1
}

func _copy(src []string, last string) []string {
	dst := make([]string, 0, len(src)+1)
	for _, word := range src {
		dst = append(dst, word)
	}
	dst = append(dst, last)
	return dst
}
