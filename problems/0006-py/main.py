# Source: https://leetcode.com/problems/zigzag-conversion
# Title: ZigZag Conversion
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# The string `"PAYPALISHIRING"` is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
#
# ```
# P   A   H   N
# A P L S I I G
# Y   I   R
# ```
#
# And then read line by line: `"PAHNAPLSIIGYIR"`
#
# Write the code that will take a string and make this conversion given a number of rows:
#
# ```
# string convert(string s, int numRows);
# ```
#
# **Example 1:**
#
# ```
# Input: s = "PAYPALISHIRING", numRows = 3
# Output: "PAHNAPLSIIGYIR"
# ```
#
# **Example 2:**
#
# ```
# Input: s = "PAYPALISHIRING", numRows = 4
# Output: "PINALSIGYAHRPI"
# Explanation:
# P     I    N
# A   L S  I G
# Y A   H R
# P     I
# ```
#
# **Example 3:**
#
# ```
# Input: s = "A", numRows = 1
# Output: "A"
# ```
#
# **Constraints:**
#
# - `1 <= s.length <= 1000`
# - `s` consists of English letters (lower-case and upper-case), `','` and `'.'`.
# - `1 <= numRows <= 1000`
#
################################################################################################################################


class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1:
            return s

        period = 2 * (numRows - 1)
        chars = list(s)

        ans = []

        # first row
        ans.extend(chars[::period])

        # middle rows
        for i in range(1, numRows - 1):
            sub1 = chars[i::period]
            sub2 = chars[period - i :: period]
            for ch1, ch2 in zip(sub1, sub2):
                ans.extend((ch1, ch2))
            if len(sub1) > len(sub2):
                ans.append(sub1[-1])

        # last row
        ans.extend(chars[numRows - 1 :: period])

        return "".join(ans)
