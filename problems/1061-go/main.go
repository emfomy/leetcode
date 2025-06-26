// Source: https://leetcode.com/problems/lexicographically-smallest-equivalent-string
// Title: Lexicographically Smallest Equivalent String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings of the same length `s1` and `s2` and a string `baseStr`.
//
// We say `s1[i]` and `s2[i]` are equivalent characters.
//
// - For example, if `s1 = "abc"` and `s2 = "cde"`, then we have `'a' == 'c'`, `'b' == 'd'`, and `'c' == 'e'`.
//
// Equivalent characters follow the usual rules of any equivalence relation:
//
// - **Reflexivity:** `'a' == 'a'`.
// - **Symmetry:** `'a' == 'b'` implies `'b' == 'a'`.
// - **Transitivity:** `'a' == 'b'` and `'b' == 'c'` implies `'a' == 'c'`.
//
// For example, given the equivalency information from `s1 = "abc"` and `s2 = "cde"`, `"acd"` and `"aab"` are equivalent strings of `baseStr = "eed"`, and `"aab"` is the lexicographically smallest equivalent string of `baseStr`.
//
// Return the lexicographically smallest equivalent string of `baseStr` by using the equivalency information from `s1` and `s2`.
//
// **Example 1:**
//
// ```
// Input: s1 = "parker", s2 = "morris", baseStr = "parser"
// Output: "makkek"
// Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [m,p], [a,o], [k,r,s], [e,i].
// The characters in each group are equivalent and sorted in lexicographical order.
// So the answer is "makkek".
// ```
//
// **Example 2:**
//
// ```
// Input: s1 = "hello", s2 = "world", baseStr = "hold"
// Output: "hdld"
// Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [h,w], [d,e,o], [l,r].
// So only the second letter 'o' in baseStr is changed to 'd', the answer is "hdld".
// ```
//
// **Example 3:**
//
// ```
// Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
// Output: "aauaaaaada"
// Explanation: We group the equivalent characters in s1 and s2 as [a,o,e,r,s,c], [l,p], [g,t] and [d,m], thus all letters in baseStr except 'u' and 'd' are transformed to 'a', the answer is "aauaaaaada".
// ```
//
// **Constraints:**
//
// - `1 <= s1.length, s2.length, baseStr <= 1000`
// - `s1.length == s2.length`
// - `s1`, `s2`, and `baseStr` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func smallestEquivalentString(s1 string, s2 string, baseStr string) string {
	uf := newUnionFind()

	n := len(s1)
	for i := range n {
		x, y := int(s1[i]-'a'), int(s2[i]-'a')
		uf.union(x, y)
	}

	m := len(baseStr)
	ans := make([]byte, m)
	for i := range m {
		x := int(baseStr[i] - 'a')
		x = uf.find(x)
		ans[i] = uf.label[x]
	}

	return string(ans)
}

type unionFind struct {
	parent []int
	rank   []int
	label  []byte
}

func newUnionFind() *unionFind {
	parent := make([]int, 26)
	rank := make([]int, 26)
	label := make([]byte, 26)
	for i := range 26 {
		parent[i] = i
		rank[i] = 0
		label[i] = 'a' + byte(i)
	}
	return &unionFind{
		parent: parent,
		rank:   rank,
		label:  label,
	}
}

func (uf *unionFind) find(x int) int {
	if uf.parent[x] != x {
		uf.parent[x] = uf.find(uf.parent[x])
	}
	return uf.parent[x]
}

func (uf *unionFind) union(x, y int) {
	x = uf.find(x)
	y = uf.find(y)
	if x == y {
		return
	}

	// Ensure rank(x) >= rank(y)
	if uf.rank[x] > uf.rank[y] {
		x, y = y, x
	}

	// Merge y into x
	uf.parent[y] = x
	if uf.rank[x] == uf.rank[y] {
		uf.rank[x]++
	}
	uf.label[x] = min(uf.label[x], uf.label[y])
}
