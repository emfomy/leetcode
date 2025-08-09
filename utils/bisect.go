package utils

// The range [lo, hi) is unknown.
//
// We know check(lo-1) = false, check(hi) = true.
// This equality should be preserved during th algorithm.
//
// The algorithm ends when unknown range is empty, i.e. lo=hi.
// Here check(lo-1) = false, check(lo=hi) = true.
func bisect(check func(int) bool, lo, hi int) int {
	for lo < hi { // [lo, hi) is unknown
		mid := lo + (hi-lo)/2
		if check(mid) {
			hi = mid // [lo, mid) is unknown
		} else {
			lo = mid + 1 // [mid+1, hi) is unknown
		}
	}
	return lo
}
