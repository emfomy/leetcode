// Source: https://leetcode.com/problems/determine-if-string-halves-are-alike
// Title: Determine if String Halves Are Alike
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.
//
// Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
//
// Return true if a and b are alike. Otherwise, return false.
//
// Example 1:
//
//   Input: s = "book"
//   Output: true
//   Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
//
// Example 2:
//
//   Input: s = "textbook"
//   Output: false
//   Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
//     Notice that the vowel o is counted twice.
//
// Constraints:
//
//   2 <= s.length <= 1000
//   s.length is even.
//   s consists of uppercase and lowercase letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

var vowelSet = map[rune]int{
	'a': 1,
	'e': 1,
	'i': 1,
	'o': 1,
	'u': 1,
	'A': 1,
	'E': 1,
	'I': 1,
	'O': 1,
	'U': 1,
}

func halvesAreAlike(s string) bool {
	a := s[:len(s)/2]
	b := s[len(s)/2:]

	// Count vowel
	count := 0
	for _, ch := range a {
		count += vowelSet[ch]
	}
	for _, ch := range b {
		count -= vowelSet[ch]
	}

	return count == 0
}
