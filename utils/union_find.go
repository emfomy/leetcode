package utils

// Union-Find
type unionFind struct {
	parent []int
	rank   []int
	count  int // number of connected components
}

func newUnionFind(n int) *unionFind {
	count := 0
	parent := make([]int, n)
	rank := make([]int, n)

	for i := 0; i < n; i++ {
		parent[i] = i
		rank[i] = 0
		count++
	}

	return &unionFind{
		parent: parent,
		rank:   rank,
		count:  count,
	}
}

func (u *unionFind) find(i int) int { // path compression
	if i != u.parent[i] {
		u.parent[i] = u.find(u.parent[i])
	}
	return u.parent[i]
}

func (u *unionFind) union(x, y int) { // union with rank
	x = u.find(x)
	y = u.find(y)
	if x == y {
		return
	}

	if u.rank[x] > u.rank[y] {
		x, y = y, x
	}

	u.parent[x] = y
	if u.rank[x] == u.rank[y] {
		u.rank[x]++
	}

	u.count--
}
