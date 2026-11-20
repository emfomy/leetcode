// Source: https://leetcode.com/problems/gcd-sort-of-an-array
// Title: GCD Sort of an Array
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`, and you can perform the following operation **any** number of times on `nums`:
//
// - Swap the positions of two elements `nums[i]` and `nums[j]` if `gcd(nums[i], nums[j]) > 1` where `gcd(nums[i], nums[j])` is the **greatest common divisor** of `nums[i]` and `nums[j]`.
//
// Return `true` if it is possible to sort `nums` in **non-decreasing** order using the above swap method, or `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: nums = [7,21,3]
// Output: true
// Explanation: We can sort [7,21,3] by performing the following operations:
// - Swap 7 and 21 because gcd(7,21) = 7. nums = [**21**,**7**,3]
// - Swap 21 and 3 because gcd(21,3) = 3. nums = [**3**,7,**21**]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,2,6,2]
// Output: false
// Explanation: It is impossible to sort the array because 5 cannot be swapped with any other element.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [10,5,9,3,15]
// Output: true
// We can sort [10,5,9,3,15] by performing the following operations:
// - Swap 10 and 15 because gcd(10,15) = 5. nums = [**15**,5,9,3,**10**]
// - Swap 15 and 3 because gcd(15,3) = 3. nums = [**3**,5,9,**15**,10]
// - Swap 10 and 15 because gcd(10,15) = 5. nums = [3,5,9,**10**,**15**]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 3 * 10^4`
// - `2 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// Union-Find, TLE
//
// Use union-find to group swappable numbers.
// Next check if all number and the number at its target position are in the same group
class Solution {
  class UnionFind {
    vector<int> parents;
    vector<int> ranks;

   public:
    UnionFind(int n) : parents(n), ranks(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    bool isConnected(int x, int y) {  //
      return find(x) == find(y);
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

 public:
  bool gcdSort(const vector<int>& nums) {
    const int n = nums.size();

    // Grouping
    auto uf = UnionFind(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (gcd(nums[i], nums[j]) > 1) {
          uf.unite(i, j);
        }
      }
    }

    // Sort
    auto idxs = vector<int>(n);
    iota(idxs.begin(), idxs.end(), 0);
    auto comp = [&nums](int i, int j) -> bool { return nums[i] < nums[j]; };
    sort(idxs.begin(), idxs.end(), comp);

    // Check sortable
    for (int i = 0; i < n; ++i) {
      if (!uf.isConnected(i, idxs[i])) return false;
    }

    return true;
  }
};

// Union-Find
//
// Instead of comparing all pairs of numbers for gcd (cost O(N^2)),
// we find the prime decomposition of each number.
// We put these primes into a hash map.
//
// Next use union-find to group the numbers and the primes.
// Finally, check if all number and the number at its target position are in the same group
class Solution2 {
  class UnionFind {
    vector<int> parents;
    vector<int> ranks;

   public:
    UnionFind(int n) : parents(n), ranks(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int insert() {
      int x = parents.size();
      parents.push_back(x);
      ranks.push_back(0);
      return x;
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    bool isConnected(int x, int y) {  //
      return find(x) == find(y);
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

  // Prime Decomposition
  vector<int> getPrimes(int x) {
    auto primes = vector<int>();

    for (int p = 2; p * p <= x; ++p) {
      if (x % p != 0) continue;
      primes.push_back(p);
      do {
        x /= p;
      } while (x % p == 0);
    }

    if (x > 1) {
      primes.push_back(x);
    }

    return primes;
  }

 public:
  bool gcdSort(const vector<int>& nums) {
    const int n = nums.size();

    // Grouping
    auto uf = UnionFind(n);
    auto primeIds = unordered_map<int, int>();
    for (int i = 0; i < n; ++i) {
      for (int prime : getPrimes(nums[i])) {
        int id;
        if (primeIds.contains(prime)) {
          id = primeIds[prime];
        } else {
          id = uf.insert();
          primeIds[prime] = id;
        }

        uf.unite(i, id);
      }
    }

    // Sort
    auto idxs = vector<int>(n);
    iota(idxs.begin(), idxs.end(), 0);
    auto comp = [&nums](int i, int j) -> bool { return nums[i] < nums[j]; };
    sort(idxs.begin(), idxs.end(), comp);

    // Check sortable
    for (int i = 0; i < n; ++i) {
      if (!uf.isConnected(i, idxs[i])) return false;
    }

    return true;
  }
};

// Union-Find
//
// Instead of using number index in union-find, we use the value.
class Solution3 {
  class UnionFind {
    vector<int> parents;
    vector<int> ranks;

   public:
    UnionFind(int n) : parents(n), ranks(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    bool isConnected(int x, int y) {  //
      return find(x) == find(y);
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

  // Prime Decomposition
  vector<int> getPrimes(int x) {
    auto primes = vector<int>();

    for (int p = 2; p * p <= x; ++p) {
      if (x % p != 0) continue;
      primes.push_back(p);
      do {
        x /= p;
      } while (x % p == 0);
    }

    if (x > 1) {
      primes.push_back(x);
    }

    return primes;
  }

 public:
  bool gcdSort(const vector<int>& nums) {
    const int n = nums.size();
    const int m = *max_element(nums.cbegin(), nums.cend()) + 1;

    // Grouping
    auto uf = UnionFind(m);
    for (int num : nums) {
      for (int prime : getPrimes(num)) {
        uf.unite(num, prime);
      }
    }

    // Sort
    auto idxs = vector<int>(n);
    iota(idxs.begin(), idxs.end(), 0);
    auto comp = [&nums](int i, int j) -> bool { return nums[i] < nums[j]; };
    sort(idxs.begin(), idxs.end(), comp);

    // Check sortable
    for (int i = 0; i < n; ++i) {
      if (!uf.isConnected(nums[i], nums[idxs[i]])) return false;
    }

    return true;
  }
};
