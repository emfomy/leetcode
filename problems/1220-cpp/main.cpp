// Source: https://leetcode.com/problems/count-vowels-permutation
// Title: Count Vowels Permutation
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, your task is to count how many strings of length `n` can be formed under the following rules:
//
// - Each character is a lower case vowel(`'a'`, `'e'`, `'i'`, `'o'`, `'u'`)
// - Each vowel`'a'` may only be followed by an `'e'`.
// - Each vowel`'e'` may only be followed by an `'a'`or an `'i'`.
// - Each vowel`'i'` **may not** be followed by another `'i'`.
// - Each vowel`'o'` may only be followed by an `'i'` or a`'u'`.
// - Each vowel`'u'` may only be followed by an `'a'`.
//
// Since the answermay be too large,return it modulo`10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: 5
// Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2
// Output: 10
// Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
// ```
//
// **Example 3:**
//
// ```
// Input: n = 5
// Output: 68```
//
// **Constraints:**
//
// - `1 <= n <= 2 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>

using namespace std;

// Math
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int countVowelPermutation(int n) {
    int64_t currA = 1, currE = 1, currI = 1, currO = 1, currU = 1;
    for (auto i = 1; i < n; ++i) {
      auto nextA = (currE + currI + currU) % modulo;
      auto nextE = (currA + currI) % modulo;
      auto nextI = (currE + currO) % modulo;
      auto nextO = (currI) % modulo;
      auto nextU = (currI + currO) % modulo;
      currA = nextA, currE = nextE, currI = nextI, currO = nextO, currU = nextU;
    }
    return (currA + currE + currI + currO + currU) % modulo;
  }
};

// Math, Eigen Decomposition in Finite Field
//
// Define the transition matrix:
// A = [
// 0   1   1   0   1
// 1   0   1   0   0
// 0   1   0   1   0
// 0   0   1   0   0
// 0   0   1   1   0
// ]
//
// Find the eigen-system in Fp (p = 1e9+7)
// A = U * D * U^{-1}, U is the right eigenvectors
// Write e = (1, 1), u = U' * e, v = U^{-1} * e
// The solution is
// e' * A^(n-1) * e
// = e' * U * D^(n-1) * U^{-1} * e
// = (U' * e)' * D^(n-1) * (U^{-1} * e)
// = u' * D^(n-1) * v
// = sum(u @ v @ d^(n-1)), where @ is element-wise product
// = sum(c @ d^(n-1)), Write c = (u @ v)
//
// # eigen decomposion
// F = GF(1_000_000_007)
// A = Matrix(F, [...])
// e = vector(F, (1, 1, 1, 1, 1))
// d = A.eigenvalues()
// _, U = A.eigenmatrix_right()
// u = U.transpose() * e
// v = U.inverse() * e
// c = vector([a * b for a, b in zip(u, v)])
//
// d = (1000000006, 882979097, 653592850, 419376480, 44051588)
// u = (1, 12689468, 930879210, 885471712, 170959635)
// v = (0, 459873583, 779875704, 153844979, 606405749)
// c = (0, 74674987, 155923322, 984156423, 785245287)
//
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;

  // Element in Fp
  struct Int {
    int64_t val;

    inline constexpr Int operator+(Int other) {  //
      return {(val + other.val) % modulo};
    }

    inline constexpr Int operator*(Int other) {  //
      return {(val * other.val) % modulo};
    }
  };

  inline Int fastPow(Int x, int n) {
    auto res = Int{1};
    while (n > 0) {
      if (n % 2) res = res * x;
      n /= 2;
      x = x * x;
    }
    return res;
  }

 public:
  int countVowelPermutation(int n) {
    return (Int{74674987} * fastPow({882979097}, n - 1) +   //
            Int{155923322} * fastPow({653592850}, n - 1) +  //
            Int{984156423} * fastPow({419376480}, n - 1) +  //
            Int{785245287} * fastPow({44051588}, n - 1))
        .val;
  }
};

class Solution3 {
  constexpr static int64_t modulo = 1e9 + 7;

  // Element in Fp
  struct Int {
    int64_t val;

    inline constexpr Int operator+(Int other) {  //
      return {(val + other.val) % modulo};
    }

    inline constexpr Int operator*(Int other) {  //
      return {(val * other.val) % modulo};
    }
  };

  inline Int fastPow(Int x, int n) {
    auto res = Int{1};
    while (n > 0) {
      if (n % 2) res = res * x;
      n /= 2;
      x = x * x;
    }
    return res;
  }

 public:
  int countVowelPermutation(int n) {
    return (Int{514029000} * fastPow({882979097}, n) +  //
            Int{638771916} * fastPow({653592850}, n) +  //
            Int{784439686} * fastPow({419376480}, n) +  //
            Int{62759413} * fastPow({44051588}, n))
        .val;
  }
};
