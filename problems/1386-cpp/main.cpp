// Source: https://leetcode.com/problems/cinema-seat-allocation
// Title: Cinema Seat Allocation
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// https://assets.leetcode.com/uploads/2020/02/14/cinema_seats_1.png
//
// A cinemahas `n`rows of seats, numbered from 1 to `n`and there are tenseats in each row, labelled from 1to 10as shown in the figure above.
//
// Given the array `reservedSeats` containing the numbers of seats already reserved, for example, `reservedSeats[i] = [3,8]`means the seat located in row **3** and labelled with **8**is already reserved.
//
// Return the maximum number of four-person groupsyou can assign on the cinemaseats. A four-person groupoccupies fouradjacent seats **in one single row**. Seats across an aisle (such as [3,3]and [3,4]) are not considered to be adjacent, but there is an exceptional caseon which an aisle splita four-person group, in that case, the aisle splita four-person group in the middle,which means to have two people on each side.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/02/14/cinema_seats_3.png
//
// ```
// Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
// Output: 4
// Explanation: The figure above shows the optimal allocation for four groups, where seats mark with blue are already reserved and contiguous seats mark with orange are for one group.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
// Output: 2
// ```
//
// **Example 3:**
//
// ```
// Input: n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^9`
// - `1 <=reservedSeats.length <= min(10*n, 10^4)`
// - `reservedSeats[i].length == 2`
// - `1<=reservedSeats[i][0] <= n`
// - `1 <=reservedSeats[i][1] <= 10`
// - All `reservedSeats[i]` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

// Hash Set
//
// The only possible groups are [2, 5], [4, 7], [6, 9].
// We track the availability of these groups in each row.
// Note that the middle group is only available if both left and right are not available.
class Solution {
 public:
  int maxNumberOfFamilies(const int n, const vector<vector<int>>& reservedSeats) {
    // Reserved
    auto rows = unordered_set<int>();
    auto lefts = unordered_set<int>();
    auto mids = unordered_set<int>();
    auto rights = unordered_set<int>();
    for (const auto& seat : reservedSeats) {
      const int row = seat[0] - 1, col = seat[1];
      if (2 <= col && col <= 9) rows.insert(row);
      if (2 <= col && col <= 5) lefts.insert(row);
      if (4 <= col && col <= 7) mids.insert(row);
      if (6 <= col && col <= 9) rights.insert(row);
    }

    // Count
    int groups = (n - rows.size()) * 2;
    for (int row : rows) {
      bool left = !lefts.contains(row), right = !rights.contains(row), mid = !mids.contains(row);
      groups += left + right + (mid && !left && !right);
    }

    return groups;
  }
};

// Sort
//
// The only possible groups are [2, 5], [4, 7], [6, 9].
// We track the availability of these groups in each row.
// Note that the middle group is only available if both left and right are not available.
class Solution2 {
 public:
  int maxNumberOfFamilies(const int n, vector<vector<int>>& reservedSeats) {
    auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {
      return a[0] < b[0];  //
    };
    sort(reservedSeats.begin(), reservedSeats.end(), comp);

    // Insert an extra seat after the last seat.
    // Therefore we don't need to handle the trailing empty seats.
    reservedSeats.push_back({n + 1, 1});

    // Count
    int groups = 0;
    int prevRow = 0;
    bool left = false, mid = false, right = false;  // 0-th row is unavailable
    for (const auto& seat : reservedSeats) {
      const int row = seat[0], col = seat[1];
      if (row != prevRow) {
        groups += left + right + (mid && !left && !right);  // handle previous row
        groups += 2 * (row - prevRow - 1);                  // empty rows between
        left = true, mid = true, right = true;
      }
      prevRow = row;
      if (2 <= col && col <= 5) left = false;
      if (4 <= col && col <= 7) mid = false;
      if (6 <= col && col <= 9) right = false;
    }

    return groups;
  }
};
