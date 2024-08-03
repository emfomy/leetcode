// Source: https://leetcode.com/problems/range-sum-query-immutable
// Title: Range Sum Query - Immutable
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, handle multiple queries of the following type:
//
//   Update the value of an element in nums.
//   Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
//
// Implement the NumArray class:
//
//   NumArray(int[] nums) Initializes the object with the integer array nums.
//   void update(int index, int val) Updates the value of nums[index] to be val.
//   int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
//
// Example 1:
//
//   Input
//     ["NumArray", "sumRange", "update", "sumRange"]
//     [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
//
//   Output
//     [null, 9, null, 8]
//
//   Explanation
//     NumArray numArray = new NumArray([1, 3, 5]);
//     numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
//     numArray.update(1, 2);   // nums = [1, 2, 5]
//     numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
//
// Constraints:
//
//   1 <= nums.length <= 3 * 104
//   -100 <= nums[i] <= 100
//   0 <= index < nums.length
//   -100 <= val <= 100
//   0 <= left <= right < nums.length
//   At most 3 * 104 calls will be made to update and sumRange.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

/**
 * Your NumArray object will be instantiated and called as such:
 * obj := Constructor(nums);
 * obj.Update(index,val);
 * param_2 := obj.SumRange(left,right);
 */

type NumArray struct {
	nums       []int
	partialSum []int
}

func Constructor(nums []int) NumArray {
	partialSum := make([]int, len(nums))
	partialSum[0] = nums[0]
	for i := 1; i < len(nums); i++ {
		partialSum[i] = nums[i] + partialSum[i-1]
	}

	return NumArray{
		nums:       nums,
		partialSum: partialSum,
	}
}

func (this *NumArray) Update(index int, val int) {
	diff := val - this.nums[index]
	for i := index; i < len(this.nums); i++ {
		this.partialSum[i] += diff
	}
	this.nums[index] = val
}

func (this *NumArray) SumRange(left int, right int) int {
	if left == 0 {
		return this.partialSum[right]
	}
	return this.partialSum[right] - this.partialSum[left-1]
}
