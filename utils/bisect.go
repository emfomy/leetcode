package utils

import "cmp"

// arr[lo-1] < target <= arr[lo=hi]
func bisectLeft[T cmp.Ordered](arr []T, target T, lo, hi int) int {
	for lo < hi {
		mid := (lo + hi) / 2
		if arr[mid] < target {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

// arr[lo-1] <= target < arr[lo=hi]
func bisectRight[T cmp.Ordered](arr []T, target T, lo, hi int) int {
	for lo < hi {
		mid := (lo + hi) / 2
		if arr[mid] <= target {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

// fn should be be arr[mid] < target for bisect left
// fn should be be arr[mid] <= target for bisect right
func bisectFunc(fn func(int) bool, lo, hi int) int {
	for lo < hi {
		mid := (lo + hi) / 2
		if fn(mid) {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}
