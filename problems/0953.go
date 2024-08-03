// Source: https://leetcode.com/problems/verifying-an-alien-dictionary
// Title: Verifying an Alien Dictionary
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.
//
// Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographically in this alien language.
//
// Example 1:
//
//   Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
//   Output: true
//   Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
//
// Example 2:
//
//   Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
//   Output: false
//   Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
//
// Example 3:
//
//   Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
//   Output: false
//   Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
//
// Constraints:
//
//   1 <= words.length <= 100
//   1 <= words[i].length <= 20
//   order.length == 26
//   All characters in words[i] and order are English lowercase letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func isAlienSorted(words []string, order string) bool {
	dict := make(map[byte]int, 26)
	for i, c := range order {
		dict[byte(c)] = i
	}

	for i := 0; i < len(words)-1; i++ {
		if !_compare(words[i], words[i+1], dict) {
			return false
		}
	}
	return true
}

func _compare(word1 string, word2 string, dict map[byte]int) bool {
	l1 := len(word1)
	l2 := len(word2)
	l := _min(l1, l2)
	for i := 0; i < l; i++ {
		d1 := dict[word1[i]]
		d2 := dict[word2[i]]
		if d1 != d2 {
			return d1 < d2
		}
	}
	return l1 <= l2
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
