// Source: https://leetcode.com/problems/delete-duplicate-folders-in-system
// Title: Delete Duplicate Folders in System
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Due to a bug, there are many duplicate folders in a file system. You are given a 2D array `paths`, where `paths[i]` is an array representing an absolute path to the `i^th` folder in the file system.
//
// - For example, `["one", "two", "three"]` represents the path `"/one/two/three"`.
//
// Two folders (not necessarily on the same level) are **identical** if they contain the **same non-empty** set of identical subfolders and underlying subfolder structure. The folders **do not** need to be at the root level to be identical. If two or more folders are **identical**, then **mark** the folders as well as all their subfolders.
//
// - For example, folders `"/a"` and `"/b"` in the file structure below are identical. They (as well as their subfolders) should **all** be marked:
//
// - `/a`
// - `/a/x`
// - `/a/x/y`
// - `/a/z`
// - `/b`
// - `/b/x`
// - `/b/x/y`
// - `/b/z`
//
// - However, if the file structure also included the path `"/b/w"`, then the folders `"/a"` and `"/b"` would not be identical. Note that `"/a/x"` and `"/b/x"` would still be considered identical even with the added folder.
//
// Once all the identical folders and their subfolders have been marked, the file system will **delete** all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.
//
// Return the 2D array `ans` containing the paths of the **remaining** folders after deleting all the marked folders. The paths may be returned in **any** order.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/07/19/lc-dupfolder1.jpg
//
// ```
// Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
// Output: [["d"],["d","a"]]
// Explanation: The file structure is as shown.
// Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
// folder named "b".
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/07/19/lc-dupfolder2.jpg
//
// ```
// Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
// Output: [["c"],["c","b"],["a"],["a","b"]]
// Explanation: The file structure is as shown.
// Folders "/a/b/x" and "/w" (and their subfolders) are marked for deletion because they both contain an empty folder named "y".
// Note that folders "/a" and "/c" are identical after the deletion, but they are not deleted because they were not marked beforehand.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/07/19/lc-dupfolder3.jpg
//
// ```
// Input: paths = [["a","b"],["c","d"],["c"],["a"]]
// Output: [["c"],["c","d"],["a"],["a","b"]]
// Explanation: All folders are unique in the file system.
// Note that the returned array can be in a different order as the order does not matter.
// ```
//
// **Constraints:**
//
// - `1 <= paths.length <= 2 * 10^4`
// - `1 <= paths[i].length <= 500`
// - `1 <= paths[i][j].length <= 10`
// - `1 <= sum(paths[i][j].length) <= 2 * 10^5`
// - `path[i][j]` consists of lowercase English letters.
// - No two paths lead to the same folder.
// - For any folder not at the root level, its parent folder will also be in the input.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
	"strings"
)

// Use Hash for subfolder structure
//
// Use a naive hash.
// We sort the subfolder and concat them using parenthesis
// Say node `r` has two subfolders `a` and `b`,
// we define hash(r) as `a(hash(a))b(hash(b))`
func deleteDuplicateFolder(paths [][]string) [][]string {
	type trieNode struct {
		id       int
		hash     string
		children map[string]*trieNode
	}

	newTrieNode := func() *trieNode {
		return &trieNode{
			id:       -1,
			children: make(map[string]*trieNode),
		}
	}

	// Build trie
	root := newTrieNode()
	for id, path := range paths {
		node := root
		for _, sub := range path {
			next, ok := node.children[sub]
			if !ok {
				next = newTrieNode()
				node.children[sub] = next
			}
			node = next
		}
		node.id = id
	}

	// DFS for hashing
	hashFreq := make(map[string]int)
	var dfsHash func(node *trieNode)
	dfsHash = func(node *trieNode) {
		if len(node.children) == 0 {
			return
		}

		hashs := make([]string, 0, len(node.children))
		for dir, child := range node.children {
			dfsHash(child)
			hashs = append(hashs, dir+"("+child.hash+")")
		}

		slices.Sort(hashs)
		node.hash = strings.Join(hashs, "")
		hashFreq[node.hash]++
	}
	dfsHash(root)

	// Get answer
	ans := make([][]string, 0)
	var dfsAns func(node *trieNode)
	dfsAns = func(node *trieNode) {
		if hashFreq[node.hash] > 1 {
			return
		}

		if node.id >= 0 {
			ans = append(ans, paths[node.id])
		}

		for _, child := range node.children {
			dfsAns(child)
		}
	}
	dfsAns(root)

	return ans
}
