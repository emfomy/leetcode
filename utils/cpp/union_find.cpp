#include <numeric>
#include <vector>

using namespace std;

class UnionFind {
  int n;
  vector<int> parents;
  vector<int> ranks;

  UnionFind(int n) : n(n), parents(n), ranks(n) {  //
    iota(parents.begin(), parents.end(), 0);
  }

  int find(int x) {
    if (parents[x] != x) parents[x] = find(parents[x]);
    return parents[x];
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;

    // Ensure rank(x) >= rank(y)
    if (ranks[x] < ranks[y]) swap(x, y);

    // Merge y into x
    if (ranks[x] == ranks[y]) ++ranks[x];
    parents[y] = x;
  }
};
