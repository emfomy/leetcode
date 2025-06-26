package utils

// check(lo-1) = false, check(lo=hi) = true
// the range should always be [check=false, check=true)
func bisect(check func(int) bool, lo, hi int) int {
	for lo < hi { // find in range [lo, hi)
		mid := lo + (hi-lo)/2
		if check(mid) {
			hi = mid // go to range [lo, mid)
		} else {
			lo = mid + 1 // go to range [mid+1, hi)
		}
	}
	return lo
}
