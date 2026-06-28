// Source: https://leetcode.com/problems/number-of-zigzag-arrays-ii
// Title: Number of ZigZag Arrays II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given three integers `n`, `l`, and `r`.
//
// A **ZigZag** array of length `n` is defined as follows:
//
// - Each element lies in the range `[l, r]`.
// - No **two** adjacent elements are equal.
// - No **three** consecutive elements form a **strictly increasing** or **strictly decreasing** sequence.
//
// Return the total number of valid **ZigZag** arrays.
//
// Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// A **sequence** is said to be **strictly increasing** if each element is strictly greater than its previous one (if exists).
//
// A **sequence** is said to be **strictly decreasing** if each element is strictly smaller than its previous one (if exists).
//
// **Example 1:**
//
// ```
// Input: n = 3, l = 4, r = 5
// Output: 2
// Explanation:
// There are only 2 valid ZigZag arrays of length `n = 3` using values in the range `[4, 5]`:
// - `[4, 5, 4]`
// - `[5, 4, 5]`
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, l = 1, r = 3
// Output: 10
// Explanation:
// There are 10 valid ZigZag arrays of length `n = 3` using values in the range `[1, 3]`:
// - `[1, 2, 1]`, `[1, 3, 1]`, `[1, 3, 2]`
// - `[2, 1, 2]`, `[2, 1, 3]`, `[2, 3, 1]`, `[2, 3, 2]`
// - `[3, 1, 2]`, `[3, 1, 3]`, `[3, 2, 3]`
// All arrays meet the ZigZag conditions.
// ```
//
// **Constraints:**
//
// - `3 <= n <= 10^9`
// - `1 <= l < r <= 75`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

// Matrix Power
//
// Let m = r-l+1.
// The transition A is a m x m matrix with Aij = 1 iff. i+j < m.
//
// Since m << n, computing A^n costs O(m^3log n),
// which is faster than O(mn).
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

  // Element in Fp
  struct Zp {
    int64_t val = 0;

    inline constexpr Zp operator+=(const Zp other) {  //
      val = (val + other.val) % modulo;
      return *this;
    }

    inline constexpr Zp operator*(const Zp other) const {  //
      return {(val * other.val) % modulo};
    }
  };

  struct Mat {
    vector<vector<Zp>> data;  // mxm

    Mat(int m) : data(m, vector<Zp>(m)) {}
  };

  inline void matMul(const Mat& a, const Mat& b, Mat& c) {
    const int m = a.data.size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        c.data[i][j] = {0};
        for (int k = 0; k < m; ++k) {
          c.data[i][j] += a.data[i][k] * b.data[k][j];
        }
      }
    }
  }

  inline Mat matPow(Mat& mat, int n) {
    const int m = mat.data.size();
    auto pow = Mat(m), tmp = Mat(m);
    for (int i = 0; i < m; ++i) pow.data[i][i] = {1};
    while (n > 0) {
      if (n % 2) {
        matMul(pow, mat, tmp);
        swap(pow.data, tmp.data);
      }
      n /= 2;
      matMul(mat, mat, tmp);
      swap(mat.data, tmp.data);
    }
    return pow;
  }

 public:
  int zigZagArrays(const int n, const int l, const int r) {
    const int m = r - l + 1;

    // Init
    auto mat = Mat(m);  // A
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m - i - 1; ++j) {
        mat.data[i][j] = {1};
      }
    }

    // Power
    auto pow = matPow(mat, n - 1);

    // Total
    Zp total;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        total += pow.data[i][j];
      }
    }

    return (Zp{2} * total).val;
  }
};
