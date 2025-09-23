// Source: https://leetcode.com/problems/compare-version-numbers
// Title: Compare Version Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two **version strings**, `version1` and `version2`, compare them. A version string consists of **revisions** separated by dots `'.'`. The **value of the revision** is its **integer conversion** ignoring leading zeros.
//
// To compare version strings, compare their revision values in **left-to-right order**. If one of the version strings has fewer revisions, treat the missing revision values as `0`.
//
// Return the following:
//
// - If `version1 < version2`, return -1.
// - If `version1 > version2`, return 1.
// - Otherwise, return 0.
//
// **Example 1:**
//
// ```
// Input: version1 = "1.2", version2 = "1.10"
// Output: -1
// Explanation:
// version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.
//
// **Example 2:**
//
// ```
// Input: version1 = "1.01", version2 = "1.001"
// Output: 0
// Explanation:
// Ignoring leading zeroes, both "01" and "001" represent the same integer "1".
//
// **Example 3:**
//
// ```
// Input: version1 = "1.0", version2 = "1.0.0.0"
// Output: 0
// Explanation:
// version1 has less revisions, which means every missing revision are treated as "0".
//
// **Constraints:**
//
// - `1 <= version1.length, version2.length <= 500`
// - `version1` and `version2`only contain digits and `'.'`.
// - `version1` and `version2`**are valid version numbers**.
// - All the given revisions in`version1` and `version2`can be stored ina**32-bit integer**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  int compareVersion(string version1, string version2) {
    auto nums1 = parseVersion(version1);
    auto nums2 = parseVersion(version2);

    int n1 = nums1.size(), n2 = nums2.size();

    for (auto i = 0; i < max(n1, n2); ++i) {
      auto v1 = i < n1 ? nums1[i] : 0;
      auto v2 = i < n2 ? nums2[i] : 0;
      if (v1 != v2) {
        return (v1 > v2) ? 1 : -1;
      }
    }

    return 0;
  }

 private:
  vector<int> parseVersion(string version) {
    istringstream iss(version);
    vector<int> nums;
    string str;
    while (getline(iss, str, '.')) {
      nums.push_back(stoi(str));
    }
    return nums;
  }
};
