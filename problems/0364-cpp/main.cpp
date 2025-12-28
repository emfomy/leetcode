// Source: https://leetcode.com/problems/nested-list-weight-sum-ii
// Title: Nested List Weight Sum II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a nested list of integers `nestedList`. Each element is either an integer or a list whose elements may also be integers or other lists.
//
// The **depth** of an integer is the number of lists that it is inside of. For example, the nested list `[1,[2,2],[[3],2],1]` has each integer's value set to its **depth**. Let `maxDepth` be the **maximum depth** of any integer.
//
// The **weight** of an integer is `maxDepth - (the depth of the integer) + 1`.
//
// Return the sum of each integer in `nestedList` multiplied by its **weight**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/27/nestedlistweightsumiiex1.png
//
// ```
// Input: nestedList = [[1,1],2,[1,1]]
// Output: 8
// Explanation: Four 1's with a weight of 1, one 2 with a weight of 2.
// 1*1 + 1*1 + 2*2 + 1*1 + 1*1 = 8
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/27/nestedlistweightsumiiex2.png
//
// ```
// Input: nestedList = [1,[4,[6]]]
// Output: 17
// Explanation: One 1 at depth 3, one 4 at depth 2, and one 6 at depth 1.
// 1*3 + 4*2 + 6*1 = 17
// ```
//
// **Constraints:**
//
// - `1 <= nestedList.length <= 50`
// - The values of the integers in the nested list is in the range `[-100, 100]`.
// - The maximum **depth** of any integer is less than or equal to `50`.
// - There are no empty lists.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
 public:
  // Constructor initializes an empty nested list.
  NestedInteger();

  // Constructor initializes a single integer.
  NestedInteger(int value);

  // Return true if this NestedInteger holds a single integer, rather than a nested list.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a single integer
  // The result is undefined if this NestedInteger holds a nested list
  int getInteger() const;

  // Set this NestedInteger to hold a single integer.
  void setInteger(int value);

  // Set this NestedInteger to hold a nested list and adds a nested integer to it.
  void add(const NestedInteger &ni);

  // Return the nested list that this NestedInteger holds, if it holds a nested list
  // The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger> &getList() const;
};

class Solution {
 public:
  int depthSumInverse(vector<NestedInteger> &nestedList) {
    auto maxDepth = _maxDepth(nestedList);
    return _depthSumInv(nestedList, maxDepth);
  }

 private:
  int _maxDepth(const vector<NestedInteger> &nestedList) {
    auto depth = 0;
    for (auto &item : nestedList) {
      if (!item.isInteger()) depth = max(depth, _maxDepth(item.getList()));
    }
    return depth + 1;
  }

  int _depthSumInv(const vector<NestedInteger> &nestedList, int depthInv) {
    auto ans = 0;
    for (auto &item : nestedList) {
      if (item.isInteger()) {
        ans += item.getInteger() * depthInv;
      } else {
        ans += _depthSumInv(item.getList(), depthInv - 1);
      }
    }
    return ans;
  }
};
