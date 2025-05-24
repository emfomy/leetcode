// Source: https://leetcode.com/problems/number-of-islands
// Title: Number of Islands
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
//
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//
// Example 1:
//
//   Input: grid = [
//     ["1","1","1","1","0"],
//     ["1","1","0","1","0"],
//     ["1","1","0","0","0"],
//     ["0","0","0","0","0"]
//   ]
//   Output: 1
//
// Example 2:
//
//   Input: grid = [
//     ["1","1","0","0","0"],
//     ["1","1","0","0","0"],
//     ["0","0","1","0","0"],
//     ["0","0","0","1","1"]
//   ]
//   Output: 3
//
// Constraints:
//
//   m == grid.length
//   n == grid[i].length
//   1 <= m, n <= 300
//   grid[i][j] is '0' or '1'.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Union-Find
type unionFind struct {
	parent []int
	rank   []int
	count  int // number of connected components
}

func newUnionFind(grid [][]byte) *unionFind {
	m := len(grid)
	n := len(grid[0])

	count := 0
	parent := make([]int, m*n)
	rank := make([]int, m*n)

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			k := i*n + j
			if grid[i][j] == '1' {
				parent[k] = k
				count++
			} else {
				parent[k] = -1
			}
			rank[k] = 0
		}
	}

	return &unionFind{
		parent: parent,
		rank:   rank,
		count:  count,
	}
}

func (uf *unionFind) find(i int) int { // path compression
	if i != uf.parent[i] {
		uf.parent[i] = uf.find(uf.parent[i])
	}
	return uf.parent[i]
}

func (uf *unionFind) union(x, y int) { // union with rank
	x = uf.find(x)
	y = uf.find(y)
	if x == y {
		return
	}

	if uf.rank[x] > uf.rank[y] {
		x, y = y, x
	}

	uf.parent[x] = y
	if uf.rank[x] == uf.rank[y] {
		uf.rank[y]++
	}

	uf.count--
}

func numIslands(grid [][]byte) int {
	m := len(grid)
	n := len(grid[0])

	uf := newUnionFind(grid)
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			k := i*n + j
			if grid[i][j] == '1' {
				grid[i][j] = '0'
				if i-1 >= 0 && grid[i-1][j] == '1' {
					uf.union(k, (i-1)*n+j)
				}
				if i+1 < m && grid[i+1][j] == '1' {
					uf.union(k, (i+1)*n+j)
				}
				if j-1 >= 0 && grid[i][j-1] == '1' {
					uf.union(k, i*n+(j-1))
				}
				if j+1 < n && grid[i][j+1] == '1' {
					uf.union(k, i*n+(j+1))
				}
			}
		}
	}

	return uf.count
}
