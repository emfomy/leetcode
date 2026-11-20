// Source: https://leetcode.com/problems/maximum-number-of-ones
// Title: Maximum Number of Ones
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Consider a matrix `M` with dimensions `width * height`, such that every cell has value `0`or `1`, and any **square**sub-matrix of `M` of size `sideLength * sideLength`has at most `maxOnes`ones.
//
// Return the maximum possible number of ones that the matrix `M` can have.
//
// **Example 1:**
//
// ```
// Input: width = 3, height = 3, sideLength = 2, maxOnes = 1
// Output: 4
// Explanation:
// In a 3*3 matrix, no 2*2 sub-matrix can have more than 1 one.
// The best solution that has 4 ones is:
// [1,0,1]
// [0,0,0]
// [1,0,1]
// ```
//
// **Example 2:**
//
// ```
// Input: width = 3, height = 3, sideLength = 2, maxOnes = 2
// Output: 6
// Explanation:
// [1,0,1]
// [1,0,1]
// [1,0,1]
// ```
//
// **Constraints:**
//
// - `1 <= width, height <= 100`
// - `1 <= sideLength <= width, height`
// - `0 <= maxOnes <= sideLength * sideLength`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdio>
#include <functional>
#include <numeric>
#include <vector>

#include "../../utils/cpp/print.hpp"

using namespace std;

// Greedy
//
// The matrix can be repetitive with modulo `sideLength`.
// If we put 1 on (i, j) we can safely put 1 on all cells with the same index modulo.
//
// We first count the frequency of each (i, j) (i.e. number of cells with same modulo).
// Then choose the cells with most frequency to put 1.
class Solution {
 public:
  int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
    // Count frequency
    auto freq = vector(sideLength * sideLength, 0);
    for (auto i = 0; i < width; ++i) {
      for (auto j = 0; j < height; ++j) {
        auto x = i % sideLength, y = j % sideLength;
        ++freq[x * sideLength + y];
      }
    }

    // Sort
    sort(freq.begin(), freq.end(), greater());

    // Choose max frequencies
    auto ans = accumulate(freq.cbegin(), freq.cbegin() + maxOnes, 0);

    return ans;
  }
};

// Greedy + Math
//
// Denote S=sideLength.
// We split the matrix into several sxs grids.
// Note that some grids in the bottom and right edge are not complete.
//
// Say width = W * s + w, height = H * s + h.
//
// We labels the grids as follow:
// F: full grids                ; WH grids
// B: bottom edge grids         ; W grids
// R: right edge grids          ; H grids
// C: bottom right corner grid  ; 1 grid
//
// There are w*h         cells covered by F, B, R, C ; WH+W+H+1 grids
// There are (s-w)*h     cells covered by F, B       ; WH+W grids
// There are w*(s-h)     cells covered by F, R       ; WH+H grids
// There are (s-w)*(s-h) cells covered by F only     ; WH grids
class Solution2 {
 public:
  int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
    auto s = sideLength;
    auto W = width / sideLength;
    auto H = height / sideLength;
    auto w = width % sideLength;
    auto h = height % sideLength;

    // WLOG, assume W > H
    if (W < H) {
      swap(width, height);
      swap(W, H);
      swap(w, h);
    }

    // FBRC
    auto ans = (W + 1) * (H + 1) * min(w * h, maxOnes);
    maxOnes = max(maxOnes - w * h, 0);

    // FB
    ans += W * (H + 1) * min((s - w) * h, maxOnes);
    maxOnes = max(maxOnes - (s - w) * h, 0);

    // FR
    ans += (W + 1) * H * min(w * (s - h), maxOnes);
    maxOnes = max(maxOnes - w * (s - h), 0);

    // F
    ans += W * H * min((s - w) * (s - h), maxOnes);

    return ans;
  }
};
