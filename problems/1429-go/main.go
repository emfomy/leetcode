// Source: https://leetcode.com/problems/first-unique-number
// Title: First Unique Number
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a queue of integers, you need to retrieve the first unique integer in the queue.
//
// Implement the `FirstUnique` class:
//
// - `FirstUnique(int[] nums)`  Initializes the object with the numbers in the queue.
// - `int showFirstUnique()` returns the value of **thefirst unique** integer of the queue, and returns **-1** if there is no such integer.
// - `void add(int value)` insert valuetothe queue.
//
// **Example 1:**
//
// ```
// Input:
//   ["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
//   [[[2,3,5]],[],[5],[],[2],[],[3],[]]
// Output:
//   [null,2,null,2,null,3,null,-1]
// Explanation:
//   FirstUnique firstUnique = new FirstUnique([2,3,5]);
//   firstUnique.showFirstUnique(); // return 2
//   firstUnique.add(5);            // the queue is now [2,3,5,5]
//   firstUnique.showFirstUnique(); // return 2
//   firstUnique.add(2);      // the queue is now [2,3,5,5,2]
//   firstUnique.showFirstUnique(); // return 3
//   firstUnique.add(3);      // the queue is now [2,3,5,5,2,3]
//   firstUnique.showFirstUnique(); // return -1
// ```
//
// **Example 2:**
//
// ```
// Input:
//   ["FirstUnique","showFirstUnique","add","add","add","add","add","showFirstUnique"]
//   [[[7,7,7,7,7,7]],[],[7],[3],[3],[7],[17],[]]
// Output:
//   [null,-1,null,null,null,null,null,17]
// Explanation:
//   FirstUnique firstUnique = new FirstUnique([7,7,7,7,7,7]);
//   firstUnique.showFirstUnique(); // return -1
//   firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7]
//   firstUnique.add(3);      // the queue is now [7,7,7,7,7,7,7,3]
//   firstUnique.add(3);      // the queue is now [7,7,7,7,7,7,7,3,3]
//   firstUnique.add(7);      // the queue is now [7,7,7,7,7,7,7,3,3,7]
//   firstUnique.add(17);     // the queue is now [7,7,7,7,7,7,7,3,3,7,17]
//   firstUnique.showFirstUnique(); // return 17
// ```
//
// **Example 3:**
//
// ```
// Input:
//   ["FirstUnique","showFirstUnique","add","showFirstUnique"]
//   [[[809]],[],[809],[]]
// Output:
//   [null,809,null,-1]
// Explanation:
//   FirstUnique firstUnique = new FirstUnique([809]);
//   firstUnique.showFirstUnique(); // return 809
//   firstUnique.add(809);          // the queue is now [809,809]
//   firstUnique.showFirstUnique(); // return -1
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^8`
// - `1 <= value <= 10^8`
// - At most `50000` calls will be made to `showFirstUnique` and `add` .
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

type FirstUnique struct {
	queue []int        // value queue
	uniqs map[int]bool // uniqueness
}

func Constructor(nums []int) FirstUnique {
	this := FirstUnique{
		uniqs: make(map[int]bool),
	}
	for _, num := range nums {
		this.insert(num)
	}
	this.pop()
	return this
}

func (this *FirstUnique) ShowFirstUnique() int {
	if len(this.queue) == 0 {
		return -1
	}
	return this.queue[0]
}

func (this *FirstUnique) Add(value int) {
	this.insert(value)
	this.pop()
}

func (this *FirstUnique) insert(value int) {
	// Insert value
	if _, ok := this.uniqs[value]; !ok {
		this.queue = append(this.queue, value)
		this.uniqs[value] = true
	} else {
		this.uniqs[value] = false
	}
}

func (this *FirstUnique) pop() {
	// Pop non-unique values
	for len(this.queue) > 0 && !this.uniqs[this.queue[0]] {
		this.queue = this.queue[1:]
	}
}
