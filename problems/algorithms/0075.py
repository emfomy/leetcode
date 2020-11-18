# Source: https://leetcode.com/problems/sort-colors/
# Title: Sort Colors
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
#
# Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
#
# Follow up:
#
#   Could you solve this problem without using the library's sort function?
#   Could you come up with a one-pass algorithm using only O(1) constant space?
#
# Example 1:
#
#   Input: nums = [2,0,2,1,1,0]
#   Output: [0,0,1,1,2,2]
#
# Example 2:
#
#   Input: nums = [2,0,1]
#   Output: [0,1,2]
#
# Example 3:
#
#   Input: nums = [0]
#   Output: [0]
#
# Example 4:
#
#   Input: nums = [1]
#   Output: [1]
#
# Constraints:
#
#   n == nums.length
#   1 <= n <= 300
#   nums[i] is 0, 1, or 2.
#
################################################################################################################################

class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        One-pass algorithm
        Time: O(n); Space: O(1)
        """

        red_pointer  = 0
        blue_pointer = len(nums)-1

        cur_pointer = 0
        while cur_pointer <= blue_pointer:
            color = nums[cur_pointer]
            if color == 0: # red
                nums[cur_pointer], nums[red_pointer] = nums[red_pointer], nums[cur_pointer]
                cur_pointer += 1
                red_pointer += 1
            elif color == 1:  # white
                cur_pointer += 1
            else: # blue
                nums[cur_pointer], nums[blue_pointer] = nums[blue_pointer], nums[cur_pointer]
                blue_pointer -= 1

################################################################################################################################

class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        Two-pass algorithm
        Time: O(n); Space: O(1)
        """

        # Count
        counts = { 0: 0, 1: 0, 2: 0 }
        for n in nums:
            counts[n] += 1

        # Red
        shift = 0
        for color, count in counts.items():
            for i in range(shift, shift+count):
                nums[i] = color
            shift += count
