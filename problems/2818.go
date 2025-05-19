// Source: https://leetcode.com/problems/apply-operations-to-maximize-score
// Title: Apply Operations to Maximize Score
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` of `n` positive integers and an integer `k`.
//
// Initially, you start with a score of `1`. You have to maximize your score by applying the following operation at most `k` times:
//
// - Choose any **non-empty** subarray `nums[l, ..., r]` that you haven't chosen previously.
// - Choose an element `x` of `nums[l, ..., r]` with the highest **prime score**. If multiple such elements exist, choose the one with the smallest index.
// - Multiply your score by `x`.
//
// Here, `nums[l, ..., r]` denotes the subarray of `nums` starting at index `l` and ending at the index `r`, both ends being inclusive.
//
// The **prime score** of an integer `x` is equal to the number of distinct prime factors of `x`. For example, the prime score of `300` is `3` since `300 = 2 * 2 * 3 * 5 * 5`.
//
// Return the **maximum possible score** after applying at most `k` operations.
//
// Since the answer may be large, return it modulo `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: nums = [8,3,9,3,8], k = 2
// Output: 81
// Explanation: To get a score of 81, we can apply the following operations:
// - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
// It can be proven that 81 is the highest score one can obtain.```
//
// **Example 2:**
//
// ```
// Input: nums = [19,12,14,6,10,18], k = 3
// Output: 4788
// Explanation: To get a score of 4788, we can apply the following operations:
// - Choose subarray nums[0, ..., 0]. nums[0] is the only element in this subarray. Hence, we multiply the score by nums[0]. The score becomes 1 * 19 = 19.
// - Choose subarray nums[5, ..., 5]. nums[5] is the only element in this subarray. Hence, we multiply the score by nums[5]. The score becomes 19 * 18 = 342.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 2, but nums[2] has the smaller index. Hence, we multipy the score by nums[2]. The score becomes 342 * 14 = 4788.
// It can be proven that 4788 is the highest score one can obtain.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length == n <= 10^5`
// - `1 <= nums[i] <= 10^5`
// - `1 <= k <= min(n * (n + 1) / 2, 10^9)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"container/heap"
	"fmt"
)

const modulo = int(1e9 + 7)

// A number `x` is chosen in [l, , ..., c..., r]
// iff. nums[l], ..., nums[c-1] < x
// and nums[c+1], ..., nums[r] <= x
//
// Use monotonic stack to compute left and right indices.
// Use heap to sort the numbers (we only need the top numbers, sorting is too expansive)
func maximumScore(nums []int, k int) int {
	n := len(nums)

	// Find prime scores
	getScore := func(num int) int {
		score := 0
		if num%2 == 0 {
			score++
			for num%2 == 0 {
				num /= 2
			}
		}
		for p := 3; p*p <= num; p += 2 {
			if num%p == 0 {
				score++
				for num%p == 0 {
					num /= p
				}
			}
		}
		if num >= 2 { // prime
			score++
		}
		return score
	}
	scores := make([]int, n)
	for i, num := range nums {
		scores[i] = getScore(num)
	}
	// scores = []int{1, 3, 4, 2,

	type stackItem struct {
		val int
		idx int
	}

	// Find left index such that nums[l] >= x
	lefts := make([]int, n)
	{
		stack := make([]stackItem, 0, n)
		stack = append(stack, stackItem{val: 1_000_000, idx: -1})
		for i := 0; i < n; i++ {
			score := scores[i]
			for stack[len(stack)-1].val < score {
				stack = stack[:len(stack)-1]
			}
			lefts[i] = stack[len(stack)-1].idx
			stack = append(stack, stackItem{val: score, idx: i})
		}
	}

	// Find right index such that nums[r] > x
	rights := make([]int, n)
	{
		stack := make([]stackItem, 0, n)
		stack = append(stack, stackItem{val: 1_000_000, idx: n})
		for i := n - 1; i >= 0; i-- {
			score := scores[i]
			for stack[len(stack)-1].val <= score {
				stack = stack[:len(stack)-1]
			}
			rights[i] = stack[len(stack)-1].idx
			stack = append(stack, stackItem{val: score, idx: i})
		}
	}
	fmt.Println(scores)
	fmt.Println(lefts)
	fmt.Println(rights)

	// Compute results
	res := 1
	h := newPairHeap(nums)
	for k > 0 && h.Len() > 0 {
		item := heap.Pop(h).(pairType)
		num := item.val
		idx := item.idx
		left := lefts[idx]
		right := rights[idx]
		count := min((right-idx)*(idx-left), k)
		fmt.Println(idx, left, right, num, count)
		res = fastPow(res, num, count)
		k -= count
	}

	return res
}

func fastPow(base int, x int, n int) int {
	for true {
		if (n & 1) != 0 {
			base = (base * x) % modulo
		}
		n >>= 1
		if n == 0 {
			break
		}
		x = (x * x) % modulo
	}
	return base
}

type pairType struct {
	val int
	idx int
}

type pairHeap []pairType

func (h pairHeap) Len() int           { return len(h) }
func (h pairHeap) Less(i, j int) bool { return h[i].val > h[j].val } // max-heap
func (h pairHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func newPairHeap(arr []int) *pairHeap {
	h := make(pairHeap, 0, len(arr))
	for i, v := range arr {
		h = append(h, pairType{
			val: v,
			idx: i,
		})
	}
	heap.Init(&h)
	return &h
}

func (h *pairHeap) Push(x interface{}) {
	*h = append(*h, x.(pairType))
}

func (h *pairHeap) Pop() interface{} {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

func main() {
	fmt.Println(maximumScore(
		// []int{8, 3, 9, 3, 8}, 2,
		[]int{19, 12, 14, 6, 10, 18}, 3,
		// []int{3289, 2832, 14858, 22011}, 6,
		// []int{6, 15, 420, 2, 40}, 1,
	))
}
