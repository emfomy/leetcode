// Source: https://leetcode.com/problems/dot-product-of-two-sparse-vectors
// Title: Dot Product of Two Sparse Vectors
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two sparse vectors, compute their dot product.
//
// Implement class `SparseVector`:
//
// - `SparseVector(nums)`Initializes the object with the vector `nums`
// - `dotProduct(vec)`Compute the dot product between the instance of SparseVector and `vec`
//
// A **sparse vector** is a vector that has mostly zero values, you should store the sparse vector**efficiently **and compute the dot product between two SparseVector.
//
// **Follow up:**What if only one of the vectors is sparse?
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
// Output: 8
// Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
// v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
// Output: 0
// Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
// v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
// ```
//
// **Example 3:**
//
// ```
// Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
// Output: 6
// ```
//
// **Constraints:**
//
// - `n == nums1.length == nums2.length`
// - `1 <= n <= 10^5`
// - `0 <= nums1[i], nums2[i]<= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class SparseVector {
  vector<pair<int, int>> data;  // (index, value)

 public:
  SparseVector(vector<int>& nums) {
    int n = nums.size();
    for (auto i = 0; i < n; ++i) {
      if (nums[i] != 0) data.push_back({i, nums[i]});
    }
  }

  // Return the dotProduct of two sparse vectors
  int dotProduct(SparseVector& vec) {
    auto sum = 0;
    auto it1 = data.cbegin(), it2 = vec.data.cbegin();
    while (it1 != data.cend() && it2 != vec.data.cend()) {
      auto [idx1, val1] = *it1;
      auto [idx2, val2] = *it2;
      if (idx1 == idx2) {
        sum += val1 * val2;
        ++it1;
        ++it2;
      } else if (idx1 < idx2) {
        ++it1;
      } else {
        ++it2;
      }
    }
    return sum;
  }
};
