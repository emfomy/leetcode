// Source: https://leetcode.com/problems/search-suggestions-system/
// Title: Search Suggestions System
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of strings products and a string searchWord.
//
// Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
//
// Return a list of lists of the suggested products after each character of searchWord is typed.
//
// Example 1:
//
//   Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
//   Output: [
//     ["mobile","moneypot","monitor"],
//     ["mobile","moneypot","monitor"],
//     ["mouse","mousepad"],
//     ["mouse","mousepad"],
//     ["mouse","mousepad"]
//   ]
//   Explanation:
//     products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
//     After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
//     After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
//
// Example 2:
//
//   Input: products = ["havana"], searchWord = "havana"
//   Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
//
// Example 3:
//
//   Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
//   Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
//
// Constraints:
//
//   1 <= products.length <= 1000
//   1 <= products[i].length <= 3000
//   1 <= sum(products[i].length) <= 2 * 10^4
//   All the strings of products are unique.
//   products[i] consists of lowercase English letters.
//   1 <= searchWord.length <= 1000
//   searchWord consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"sort"
)

type prodNode struct {
	name string
	next *prodNode
}

// Use linked list
// Each word (character) will only be visited once
func suggestedProducts(products []string, searchWord string) [][]string {
	sort.Strings(products)
	root := &prodNode{}

	prodIdx := 0

	res := make([][]string, len(searchWord))
	for i := 0; i < len(searchWord); i++ {
		res[i] = make([]string, 0, 3)
		ch := searchWord[i]

		node := root
		for node.next != nil && len(res[i]) < 3 {
			if len(node.next.name) > i && node.next.name[i] == ch {
				res[i] = append(res[i], node.next.name)
				node = node.next
			} else {
				node.next = node.next.next
			}
		}

		for ; prodIdx < len(products) && len(res[i]) < 3; prodIdx++ {
			product := products[prodIdx]
			if len(product) > i && product[:i+1] == searchWord[:i+1] {
				res[i] = append(res[i], product)
				node.next = &prodNode{name: product}
				node = node.next
			}
		}
	}

	return res
}
