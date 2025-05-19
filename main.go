package main

func search(nums []int, target int) int {
	n := len(nums)
	lo, hi := 0, n
	if target >= nums[0] {
		for lo < hi {
			mid := (lo + hi) / 2
			if nums[mid] == target {
				return mid
			}
			if nums[mid] < nums[0] || nums[mid] > target {
				hi = mid
			} else {
				lo = mid + 1
			}
		}
	} else {
		for lo < hi {
			mid := (lo + hi) / 2
			if nums[mid] == target {
				return mid
			}
			if nums[mid] >= nums[0] || nums[mid] < target {
				lo = mid + 1
			} else {
				hi = mid
			}
		}
	}
	return -1
}
