// Source: https://leetcode.com/problems/count-days-spent-together
// Title: Count Days Spent Together
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alice and Bob are traveling to Rome for separate business meetings.
//
// You are given 4 strings `arriveAlice`, `leaveAlice`, `arriveBob`, and `leaveBob`. Alice will be in the city from the dates `arriveAlice` to `leaveAlice` (**inclusive**), while Bob will be in the city from the dates `arriveBob` to `leaveBob` (**inclusive**). Each will be a 5-character string in the format `"MM-DD"`, corresponding to the month and day of the date.
//
// Return the total number of days that Alice and Bob are in Rome together.
//
// You can assume that all dates occur in the **same** calendar year, which is **not** a leap year. Note that the number of days per month can be represented as: `[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]`.
//
// **Example 1:**
//
// ```
// Input: arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
// Output: 3
// Explanation: Alice will be in Rome from August 15 to August 18. Bob will be in Rome from August 16 to August 19. They are both in Rome together on August 16th, 17th, and 18th, so the answer is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01", leaveBob = "12-31"
// Output: 0
// Explanation: There is no day when Alice and Bob are in Rome together, so we return 0.
// ```
//
// **Constraints:**
//
// - All dates are provided in the format `"MM-DD"`.
// - Alice and Bob's arrival dates are **earlier than or equal to** their leaving dates.
// - The given dates are valid dates of a **non-leap** year.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

class Solution {
 public:
  int countDaysTogether(const string& arriveAlice, const string& leaveAlice, const string& arriveBob, const string& leaveBob) {
    const int alice0 = parseDate(arriveAlice);
    const int alice1 = parseDate(leaveAlice);
    const int bob0 = parseDate(arriveBob);
    const int bob1 = parseDate(leaveBob);

    const int start = max(alice0, bob0);
    const int end = min(alice1, bob1);
    return max(0, end - start + 1);
  }

 private:
  static int parseDate(const string& str) {
    static constexpr auto monthDays = [] {
      array<int, 13> days{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};  // last month is unused
      for (int i = 1; i < 12; ++i) days[i] += days[i - 1];
      return days;
    }();

    const int month = (str[0] - '0') * 10 + (str[1] - '0') - 1;  // 0-indexed
    const int day = (str[3] - '0') * 10 + (str[4] - '0') - 1;    // 0-indexed

    return monthDays[month] + day;
  }
};
