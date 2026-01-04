// Source: https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid
// Title: Number of Ways to Paint N × 3 Grid
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a `grid` of size `n x 3` and you want to paint each cell of the grid with exactly one of the three colors: **Red**, **Yellow,** or **Green** while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).
//
// Given `n` the number of rows of the grid, return the number of ways you can paint this `grid`. As the answer may grow large, the answer **must be** computed modulo `10^9 + 7`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/03/26/e1.png
//
// ```
// Input: n = 1
// Output: 12
// Explanation: There are 12 possible way to paint the grid as shown.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5000
// Output: 30228214
// ```
//
// **Constraints:**
//
// - `n == grid.length`
// - `1 <= n <= 5000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <tuple>
#include <utility>

using namespace std;

// Math
//
// First list all possible 1x3 rows:
// RYG, RGY, YRG, YGR, GRY, GYR (class A, asymmetry)
// RYR, RGR, YRY, YGY, GRG, GYG (class B, symmetry)
// Note that all case in the same class are isomorphic.
//
// If the current row is class A (say RYG),
// then next row must be YGR, GRY, YRY, YGY (i.e. 2 class A & 2 class B).
//
// If the current row is class B (say RYR),
// then next row must be YRG, GRY, YRY, YGY, GRG (i.e. 2 class A & 3 class B).
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int numOfWays(int n) {
    int64_t currA = 6, currB = 6;
    for (auto i = 1; i < n; ++i) {
      auto nextA = (2 * currA + 2 * currB) % modulo;
      auto nextB = (2 * currA + 3 * currB) % modulo;
      currA = nextA, currB = nextB;
    }
    return (currA + currB) % modulo;
  }
};

// Math
//
// Use fast matrix power.
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;

  using Vec = pair<int64_t, int64_t>;  // column vector
  using Mat = pair<Vec, Vec>;          // two rows

 private:
  inline int64_t vecvec(Vec vec1, Vec vec2) {  //
    return (vec1.first * vec2.first + vec1.second * vec2.second) % modulo;
  }

  inline Vec matvec(Mat mat, Vec vec) {  //
    return {vecvec(mat.first, vec), vecvec(mat.second, vec)};
  }

  inline Mat matmat(Mat mat1, Mat mat2) {  //
    return {
        matvec(mat1, {mat2.first.first, mat2.second.first}),
        matvec(mat1, {mat2.first.second, mat2.second.second}),
    };
  }

  inline Mat matpow(Mat mat, int n) {
    auto res = Mat{{1, 0}, {0, 1}};
    while (n > 0) {
      if (n % 2) res = matmat(res, mat);
      n /= 2;
      mat = matmat(mat, mat);
    }
    return res;
  }

 public:
  int numOfWays(int n) {
    auto ans = matvec(matpow(Mat{{2, 2}, {2, 3}}, n - 1), {6, 6});
    return (ans.first + ans.second) % modulo;
  }
};

// Math
//
// Use fast matrix power.
// Use symmetric matrix.
class Solution3 {
  constexpr static int64_t modulo = 1e9 + 7;

  using Vec = pair<int64_t, int64_t>;            // column vector
  using Mat = tuple<int64_t, int64_t, int64_t>;  // [[a, b] [b, c]]

 private:
  inline Vec matvec(Mat mat, Vec vec) {  //
    auto [a, b, c] = mat;
    auto [d, e] = vec;
    return {
        ((a * d) % modulo + (b * e) % modulo) % modulo,
        ((b * d) % modulo + (c * e) % modulo) % modulo,
    };
  }

  inline Mat matmat(Mat mat1, Mat mat2) {  //
    auto [a, b, c] = mat1;
    auto [d, e, f] = mat2;
    return {
        ((a * d) % modulo + (b * e) % modulo) % modulo,
        ((b * d) % modulo + (c * e) % modulo) % modulo,
        ((b * e) % modulo + (c * f) % modulo) % modulo,
    };
  }

  inline Mat matpow(Mat mat, int n) {
    auto res = Mat{1, 0, 1};
    while (n > 0) {
      if (n % 2) res = matmat(res, mat);
      n /= 2;
      mat = matmat(mat, mat);
    }
    return res;
  }

 public:
  int numOfWays(int n) {
    auto ans = matvec(matpow(Mat{2, 2, 3}, n - 1), {6, 6});
    return (ans.first + ans.second) % modulo;
  }
};

// Math, Eigen Decomposition in Finite Field
//
// Define the transition matrix:
// A = [
// 2   2
// 2   3
// ]
//
// tr(A) = 2+3 = 5, det(A) = 2*3-2*2 = 2, Delta(A) = tr^2 - 4det = 17
// Since 17 has not square root in Fp (p = 1e9+7), we can not compute the eigen-system.
// Therefore we need to extend the field to K = Fp(sqrt17).
// (Note that we can choose K = Fp(sqrt(-1)) as well.)
//
// Now we find the eigen-system in K.
// A = U * D * inv(U), U is the right eigenvectors
// Write e = (1, 1), u = U' * e, v = inv(U) * e
// The solution is
// 6 * e' * A^(n-1) * e
// = 6 * e' * U * D^(n-1) * inv(U) * e
// = 6 * (U' * e)' * D^(n-1) * (inv(U) * e)
// = 6 * u' * D^(n-1) * v
// = 6 * sum(u @ v @ d^(n-1)), where @ is element-wise product
// = sum(c @ d^(n-1)), Write c = (6 * u @ v)
//
// # Field extension, s = sqrt(17)
// F = GF(1_000_000_007)
// R.<x> = PolynomialRing(F)
// K.<s> = F.extension(x^2 - 17)
//
// # eigen decomposion
// A = Matrix(K, [...])
// e = vector(K, (1, 1))
// d = A.eigenvalues()
// _, U = A.eigenmatrix_right()
// u = U.transpose() * e
// v = U.inverse() * e
// c = vector([6 * a * b for a, b in zip(u, v)])
//
// d = (500000006 + 500000004s, 500000006 + 500000003s)
// u = (250000003 + 250000002s, 250000003 + 750000005s)
// v = (500000004 +  29411765s, 500000004 + 970588242s)
// c = (        6 + 470588240s,         6 + 529411767s)
//
class Solution4 {
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

  // Element in Fp(sqrt17)
  struct Elem {
    Int real;
    Int imag;

    inline constexpr Elem operator+(Elem other) {  //
      return {real + other.real, imag + other.imag};
    }

    inline constexpr Elem operator*(Elem other) {  //
      return {
          real * other.real + imag * other.imag * Int{17},
          real * other.imag + imag * other.real,
      };
    }
  };

  inline Elem fastPow(Elem x, int n) {
    auto res = Elem{1, 0};
    while (n > 0) {
      if (n % 2) res = res * x;
      n /= 2;
      x = x * x;
    }
    return res;
  }

 public:
  int numOfWays(int n) {
    return ((Elem{6, 470588240} * fastPow({500000006, 500000004}, n - 1)).real +
            (Elem{6, 529411767} * fastPow({500000006, 500000003}, n - 1)).real)
        .val;
  }
};

// Math, Cayley–Hamilton theorem
//
// Define the transition matrix:
// A = [
// 2   2
// 2   3
// ]
//
// Instead of solving the eigen system in finite field, we use Cayley–Hamilton theorem.
// The characteristic polynomial of A is: p(x) = x^2 - 5x + 2
// By Cayley–Hamilton theorem, we have A^2 = -2I + 5A.
// Now we can represent A^k as linear combination of I and A.
//
// The arithmetic operations in the quotient ring Fp[A]/<P(A)> are:
// (aI + bA) + (cI + dA) = (a+c)I + (b+d)A
// (aI + bA) * (cI + dA) = (ac)I + (ad+bc)A + (bd)A^2
//                       = (ac-2bd)I + (ad+bc+5bd)A
//
// Write e = (1, 1). We have e'Ie = 2, e'Ae = 9.
// Say A^(n-1) = aI + bA.  The final solution is
// 6 * e' * A^(n-1) * e = 6e'(aI + bA)e = 12a + 54b.
class Solution5 {
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

  // Element in Fp[A]/<P(A)>
  struct Poly {
    Int val0;
    Int val1;

    inline constexpr Poly operator+(Poly other) {  //
      return {val0 + other.val0, val1 + other.val1};
    }

    inline constexpr Poly operator*(Poly other) {  //
      return {
          val0 * other.val0 + val1 * other.val1 * Int{modulo - 2},
          val0 * other.val1 + val1 * other.val0 + val1 * other.val1 * Int{5},
      };
    }
  };

  inline Poly fastPow(Poly x, int n) {
    auto res = Poly{1, 0};  // I
    while (n > 0) {
      if (n % 2) res = res * x;
      n /= 2;
      x = x * x;
    }
    return res;
  }

 public:
  int numOfWays(int n) {
    auto poly = fastPow({0, 1}, n - 1);  // A^(n-1)
    return (poly.val0 * Int{12} + poly.val1 * Int{54}).val;
  }
};
