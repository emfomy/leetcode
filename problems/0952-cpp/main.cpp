// Source: https://leetcode.com/problems/largest-component-size-by-common-factor
// Title: Largest Component Size by Common Factor
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array of unique positive integers `nums`. Consider the following graph:
//
// - There are `nums.length` nodes, labeled `nums[0]` to `nums[nums.length - 1]`,
// - There is an undirected edge between `nums[i]` and `nums[j]` if `nums[i]` and `nums[j]` share a common factor greater than `1`.
//
// Return the size of the largest connected component in the graph.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/01/ex1.png
//
// ```
// Input: nums = [4,6,15,35]
// Output: 4
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/01/ex2.png
//
// ```
// Input: nums = [20,50,9,63]
// Output: 2
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2018/12/01/ex3.png
//
// ```
// Input: nums = [2,3,6,7,4,12,21,39]
// Output: 8
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^4`
// - `1 <= nums[i] <= 10^5`
// - All the values of `nums` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <concepts>
#include <functional>
#include <numeric>
#include <vector>

using namespace std;

// Union Find + GCD
//
// Loop through all pairs of numbers.
// For each pair, skip if the they already in the same group.
// Otherwise, compute the GCD to check if they need to merge.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;  // rank is faster, but we need size here.

    UnionFind(const int n) : parents(n), sizes(n, 1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(const int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    bool isConnected(const int x, const int y) {  //
      return find(x) == find(y);
    }

    void uniteRoot(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure size(x) >= size(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into x
      sizes[x] += sizes[y];
      parents[y] = x;
    }
  };

 public:
  int largestComponentSize(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // Union Find
    auto uf = UnionFind(n);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (uf.isConnected(i, j)) continue;

        if (gcd(nums[i], nums[j]) == 1) continue;

        uf.uniteRoot(i, j);
      }
    }

    auto maxIt = max_element(uf.sizes.cbegin(), uf.sizes.cend());
    return *maxIt;  // uf.sizes is not empty
  }
};

// Union Find + Prime Factorization
//
// Find the prime factors of each number. (O(sqrt(M)), M is maximum number)
// Create a set of each prime, and put the numbers into the sets of its prime factors.
//
// For each prime, union all numbers inside its set using union find.
class Solution2 {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;  // rank is faster, but we need size here.

    UnionFind(const int n) : parents(n), sizes(n, 1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(const int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure size(x) >= size(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into x
      sizes[x] += sizes[y];
      parents[y] = x;
    }
  };

  // TODO: use generator instead of vector
  vector<int> getPrimeFactors(const int num) {
    auto factors = vector<int>();
    int quotient = num;

    // p = 2
    if (quotient % 2 == 0) {
      factors.push_back(2);
      do {
        quotient /= 2;
      } while (quotient % 2 == 0);
    }

    // try all odd number
    for (int p = 3; p * p <= quotient; p += 2) {
      if (quotient % p == 0) {
        factors.push_back(p);
        do {
          quotient /= p;
        } while (quotient % p == 0);
      }
    }

    if (quotient > 1) factors.push_back(quotient);

    return factors;
  }

 public:
  int largestComponentSize(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // Group numbers by its factors
    auto primeSets = unordered_map<int, vector<int>>();  // prime -> ID of multiples
    for (int i = 0; i < n; ++i) {
      for (auto p : getPrimeFactors(nums[i])) {
        primeSets[p].push_back(i);
      }
    }

    // Union Find
    auto uf = UnionFind(n);
    for (auto& [_, ids] : primeSets) {
      for (auto id : ids) {
        uf.unite(ids[0], id);
      }
    }

    auto maxIt = max_element(uf.sizes.cbegin(), uf.sizes.cend());
    return *maxIt;  // uf.sizes is not empty
  }
};

// Union Find + Prime Factorization + Iterator
//
// Find the prime factors of each number. (O(sqrt(M)), M is maximum number)
// Create a set of each prime, and put the numbers into the sets of its prime factors.
//
// For each prime, union all numbers inside its set using union find.
class Solution3 {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;  // rank is faster, but we need size here.

    UnionFind(const int n) : parents(n), sizes(n, 1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(const int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure size(x) >= size(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into x
      sizes[x] += sizes[y];
      parents[y] = x;
    }
  };

  // yield is void(int)
  void getPrimeFactors(const int num, invocable<int> auto yield) {
    int quotient = num;

    // p = 2
    if (quotient % 2 == 0) {
      yield(2);
      do {
        quotient /= 2;
      } while (quotient % 2 == 0);
    }

    // try all odd number
    for (int p = 3; p * p <= quotient; p += 2) {
      if (quotient % p == 0) {
        yield(p);
        do {
          quotient /= p;
        } while (quotient % p == 0);
      }
    }

    if (quotient > 1) {
      yield(quotient);
    }
  }

 public:
  int largestComponentSize(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // Group numbers by its factors
    auto primeSets = unordered_map<int, vector<int>>();  // prime -> ID of multiples
    for (int i = 0; i < n; ++i) {
      getPrimeFactors(nums[i], [&](int p) {  //
        primeSets[p].push_back(i);
      });
    }

    // Union Find
    auto uf = UnionFind(n);
    for (auto& [_, ids] : primeSets) {
      for (auto id : ids) {
        uf.unite(ids[0], id);
      }
    }

    auto maxIt = max_element(uf.sizes.cbegin(), uf.sizes.cend());
    return *maxIt;  // uf.sizes is not empty
  }
};
