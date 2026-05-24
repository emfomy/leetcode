// Source: https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation
// Title: Minimum Jumps to Reach End via Prime Teleportation
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`.
//
// You start at index 0, and your goal is to reach index `n - 1`.
//
// From any index `i`, you may perform one of the following operations:
//
// - **Adjacent Step**: Jump to index `i + 1` or `i - 1`, if the index is within bounds.
// - **Prime Teleportation**: If `nums[i]` is a <button>prime number</button> `p`, you may instantly jump to any index `j != i` such that `nums[j] % p == 0`.
//
// Return the **minimum** number of jumps required to reach index `n - 1`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,4,6]
// Output: 2
// Explanation:
// One optimal sequence of jumps is:
// - Start at index `i = 0`. Take an adjacent step to index 1.
// - At index `i = 1`, `nums[1] = 2` is a prime number. Therefore, we teleport to index `i = 3` as `nums[3] = 6` is divisible by 2.
// Thus, the answer is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,3,4,7,9]
// Output: 2
// Explanation:
// One optimal sequence of jumps is:
// - Start at index `i = 0`. Take an adjacent step to index `i = 1`.
// - At index `i = 1`, `nums[1] = 3` is a prime number. Therefore, we teleport to index `i = 4` since `nums[4] = 9` is divisible by 3.
// Thus, the answer is 2.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [4,6,5,8]
// Output: 3
// Explanation:
// - Since no teleportation is possible, we move through `0 → 1 → 2 → 3`. Thus, the answer is 3.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// BFS
class Solution {
  using Bool = unsigned char;

 public:
  int minJumps(const vector<int>& nums) {
    const int n = nums.size();
    const int mx = *max_element(nums.begin(), nums.end());

    // Edge case
    if (n == 1) return 0;

    // Find primes
    vector<Bool> isPrime(mx + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (long long p = 2; p <= mx; p++) {
      if (!isPrime[p]) continue;
      for (long long x = p * p; x <= mx; x += p) isPrime[x] = false;
    }

    // Map number to index
    auto idxMap = vector<vector<int>>(mx + 1);
    for (int i = 0; i < n; ++i) {
      idxMap[nums[i]].push_back(i);
    }

    // BFS
    auto seen = vector<Bool>(n);
    auto curr = vector<int>();
    auto prev = vector<int>();
    curr.reserve(n);
    prev.reserve(n);

    seen[0] = true;
    curr.push_back(0);
    for (int dist = 0; !curr.empty(); ++dist) {
      swap(curr, prev);
      curr.clear();

      for (int i : prev) {
        int num = nums[i];

        // Found
        if (i == n - 1) return dist;

        // Traverse
        if (i + 1 < n && !seen[i + 1]) {
          seen[i + 1] = true;
          curr.push_back(i + 1);
        }
        if (i - 1 >= 0 && !seen[i - 1]) {
          seen[i - 1] = true;
          curr.push_back(i - 1);
        }
        if (isPrime[num]) {
          for (int x = num; x <= mx; x += num) {
            for (int j : idxMap[x]) {
              if (!seen[j]) {
                seen[j] = true;
                curr.push_back(j);
              }
            }
          }

          // Disable this prime to avoid redundant scanning
          isPrime[num] = false;
        }
      }
    }

    return -1;  // unreachable
  }
};
