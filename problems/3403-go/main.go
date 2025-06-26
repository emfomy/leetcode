// Source: https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i
// Title: Find the Lexicographically Largest String From the Box I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `word`, and an integer `numFriends`.
//
// Alice is organizing a game for her `numFriends` friends. There are multiple rounds in the game, where in each round:
//
// - `word` is split into `numFriends` **non-empty** strings, such that no previous round has had the **exact** same split.
// - All the split words are put into a box.
//
// Find the **lexicographically largest** string from the box after all the rounds are finished.
//
// A string a is **lexicographically smaller** than a string b if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
// If the first min(a.length, b.length) characters do not differ, then the shorter string is the lexicographically smaller one.
//
// **Example 1:**
//
// ```
// Input: word = "dbca", numFriends = 2
// Output: "dbc"
// Explanation:
// All possible splits are:
// - `"d"` and `"bca"`.
// - `"db"` and `"ca"`.
// - `"dbc"` and `"a"`.
// ```
//
// **Example 2:**
//
// ```
// Input: word = "gggg", numFriends = 4
// Output: "g"
// Explanation:
// The only possible split is: `"g"`, `"g"`, `"g"`, and `"g"`.
// ```
//
// **Constraints:**
//
// - `1 <= word.length <= 5* 10^3`
// - `word` consists only of lowercase English letters.
// - `1 <= numFriends <= word.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// The output must be as long as possible
//
// If the length of the word is `w` and the number of friends is `f`,
// then the largest split is `w-f+1`.
func answerString(word string, numFriends int) string {
	if numFriends == 1 {
		return word
	}

	w, f := len(word), numFriends
	s := w - f + 1

	chars := []byte(word)

	lexCmp := func(a []byte, b []byte) int {
		la, lb := len(a), len(b)
		for i := range min(la, lb) {
			if a[i] != b[i] {
				return int(a[i]) - int(b[i])
			}
		}
		return la - lb
	}

	ans := []byte{}
	for i := range w {
		split := chars[i:min(i+s, w)]
		if lexCmp(ans, split) < 0 {
			ans = split
		}
	}

	return string(ans)
}

// The output must be as long as possible
//
// If the length of the word is `w` and the number of friends is `f`,
// then the largest split is `w-f+1`.
func answerString2(word string, numFriends int) string {
	if numFriends == 1 {
		return word
	}

	w, f := len(word), numFriends
	s := w - f + 1

	ans := ""
	for i := range w {
		ans = max(ans, word[i:min(i+s, w)])
	}

	return ans
}
