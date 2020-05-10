# Source: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
# Title: Letter Combinations of a Phone Number
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
#
# A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
#
# http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png
#
# Example:
#
#   Input: "23"
#   Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
#
# Note:
#
#   Although the above answer is in lexicographical order, your answer could be in any order you want.
#
################################################################################################################################

PHONE = {
    '2': 'abc',
    '3': 'def',
    '4': 'ghi',
    '5': 'jkl',
    '6': 'mno',
    '7': 'pqrs',
    '8': 'tuv',
    '9': 'wxyz',
}

import itertools

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if digits:
            yield from map(''.join, itertools.product(*map(PHONE.get, digits)))
