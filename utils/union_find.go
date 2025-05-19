package utils

// Union-Find
type unionFind struct {
	parent []int
	rank   []int
	count  int // number of connected components
}

func newUnionFind(n int) *unionFind {
	parent := make([]int, n)
	rank := make([]int, n)

	for x := range n {
		parent[x] = x
		rank[x] = 0
	}

	return &unionFind{
		parent: parent,
		rank:   rank,
		count:  n,
	}
}

func (uf *unionFind) find(x int) int { // path compression
	if uf.parent[x] != x {
		uf.parent[x] = uf.find(uf.parent[x])
	}
	return uf.parent[x]
}

func (uf *unionFind) union(x, y int) { // union with rank
	x = uf.find(x)
	y = uf.find(y)
	if x == y {
		return
	}

	// Ensure rank(x) >= rank(y)
	if uf.rank[x] < uf.rank[y] {
		x, y = y, x
	}

	// Marge y into x
	uf.parent[y] = x
	if uf.rank[x] == uf.rank[y] {
		uf.rank[x]++
	}

	uf.count--
}
