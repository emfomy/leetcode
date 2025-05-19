// Source: https://leetcode.com/problems/regions-cut-by-slashes
// Title: Regions Cut By Slashes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
//
// Given the grid grid represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a '\' is represented as '\\'.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2018/12/15/1.png
//
//   Input: grid = [" /","/ "]
//   Output: 2
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2018/12/15/2.png
//
//   Input: grid = [" /","  "]
//   Output: 1
//
// Example 3:
//
//   https://assets.leetcode.com/uploads/2018/12/15/4.png
//
//   Input: grid = ["/\\","\\/"]
//   Output: 5
//   Explanation: Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.
//
// Constraints:
//
//   n == grid.length == grid[i].length
//   1 <= n <= 30
//   grid[i][j] is either '/', '\', or ' '.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// store the color in the edge of each grid blocks
func regionsBySlashes(grid []string) int {
	n := len(grid)

	horEdge := make([][]int, n+1) // horizontal edges, n+1 x n
	vrtEdge := make([][]int, n)   // vertical edges,   n x n+1
	for i := 0; i < n; i++ {
		horEdge[i] = make([]int, n)
		vrtEdge[i] = make([]int, n+1)
	}
	horEdge[n] = make([]int, n)

	colors := 0
	colorMap := make(map[int]int, n) // merge color map

	var mergeColor func(from, to int)
	mergeColor = func(from, to int) {
		if from == to {
			return
		}
		if from < to {
			from, to = to, from
		}
		if oldTo, ok := colorMap[from]; ok {
			mergeColor(oldTo, to)
		}
		colorMap[from] = to
	}

	// Top-left corner
	{
		switch grid[0][0] {
		case '/':
			colors = 2
			horEdge[0][0] = 1
			horEdge[1][0] = 2
			vrtEdge[0][0] = 1
			vrtEdge[0][1] = 2
		case '\\':
			colors = 2
			horEdge[0][0] = 1
			horEdge[1][0] = 2
			vrtEdge[0][0] = 2
			vrtEdge[0][1] = 1
		case ' ':
			colors = 1
			horEdge[0][0] = 1
			horEdge[1][0] = 1
			vrtEdge[0][0] = 1
			vrtEdge[0][1] = 1
		}
	}

	// First row
	{
		for j := 1; j < n; j++ {
			leftColor := vrtEdge[0][j]
			switch grid[0][j] {
			case '/':
				colors++
				horEdge[0][j+0] = leftColor
				horEdge[1][j+0] = colors
				vrtEdge[0][j+1] = colors
			case '\\':
				colors++
				horEdge[0][j+0] = colors
				horEdge[1][j+0] = leftColor
				vrtEdge[0][j+1] = colors
			case ' ':
				horEdge[0][j+0] = leftColor
				horEdge[1][j+0] = leftColor
				vrtEdge[0][j+1] = leftColor
			}
		}
	}

	// Other rows
	{
		for i := 1; i < n; i++ {
			{
				topColor := horEdge[i][0]
				switch grid[i][0] {
				case '/':
					colors++
					horEdge[i+1][0] = colors
					vrtEdge[i+0][0] = topColor
					vrtEdge[i+0][1] = colors
				case '\\':
					colors++
					horEdge[i+1][0] = colors
					vrtEdge[i+0][0] = colors
					vrtEdge[i+0][1] = topColor
				case ' ':
					horEdge[i+0][0] = topColor
					horEdge[i+1][0] = topColor
					vrtEdge[i+0][0] = topColor
					vrtEdge[i+0][1] = topColor
				}
			}

			for j := 1; j < n; j++ {
				topColor := horEdge[i][j]
				leftColor := vrtEdge[i][j]
				switch grid[i][j] {
				case '/':
					mergeColor(leftColor, topColor)
					colors++
					horEdge[i+1][j+0] = colors
					vrtEdge[i+0][j+1] = colors
				case '\\':
					horEdge[i+1][j+0] = leftColor
					vrtEdge[i+0][j+1] = topColor
				case ' ':
					mergeColor(leftColor, topColor)
					horEdge[i+1][j+0] = topColor
					vrtEdge[i+0][j+1] = topColor
				}
			}
		}
	}

	return colors - len(colorMap)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use Euler's polyhedral formula
// 1 = V - E + F => F = E - V + 1
// Note that we can ignore counting the outter box, since the number of edges & vertices are the same
//
// However, if the graph is disconnected, we need to adject the result to
// F = E - V + C, C = #component
// Here we use union find to count the components

// Union-Find
type unionFind struct {
	parent []int
	size   []int
	count  int // number of connected components
}

func newUnionFind(n int) *unionFind {
	parent := make([]int, n)
	rank := make([]int, n)

	for i := 0; i < n; i++ {
		parent[i] = i
		rank[i] = 0
	}

	return &unionFind{
		parent: parent,
		size:   rank,
		count:  n,
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

	if uf.size[x] < uf.size[y] {
		x, y = y, x
	}

	uf.parent[y] = x
	uf.size[x] += uf.size[y]
	uf.count--
}

func regionsBySlashes2(grid []string) int {
	n := len(grid)
	m := n + 1
	idx := func(i, j int) int {
		return i*m + j
	}

	numEdge := 0
	uf := newUnionFind(m * m)

	for i := 0; i < n; i++ {
		uf.union(idx(0, i), idx(0, i+1)) // top border
		uf.union(idx(n, i), idx(n, i+1)) // bottom border
		uf.union(idx(i, 0), idx(i+1, 0)) // left border
		uf.union(idx(i, n), idx(i+1, n)) // right border
	}

	for i, row := range grid {
		for j, block := range row {
			x, y := -1, -1

			switch block {
			case ' ':
				continue
			case '/':
				x = idx(i, j+1)
				y = idx(i+1, j)
			case '\\':
				x = idx(i, j)
				y = idx(i+1, j+1)
			}
			uf.union(x, y)
			numEdge++
		}
	}

	numVertex := (n - 1) * (n - 1)
	numComponent := uf.count
	return numEdge - numVertex + numComponent
}
