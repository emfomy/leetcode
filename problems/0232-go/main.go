// Source: https://leetcode.com/problems/implement-queue-using-stacks
// Title: Implement Queue using Stacks
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).
//
// Implement the MyQueue class:
//
//   void push(int x) Pushes element x to the back of the queue.
//   int pop() Removes the element from the front of the queue and returns it.
//   int peek() Returns the element at the front of the queue.
//   boolean empty() Returns true if the queue is empty, false otherwise.
//
// Notes:
//
//   You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
//   Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
//
// Example 1:
//
//   Input
//     ["MyQueue", "push", "push", "peek", "pop", "empty"]
//     [[], [1], [2], [], [], []]
//   Output
//     [null, null, null, 1, 1, false]
//   Explanation
//     MyQueue myQueue = new MyQueue();
//     myQueue.push(1); // queue is: [1]
//     myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
//     myQueue.peek(); // return 1
//     myQueue.pop(); // return 1, queue is [2]
//     myQueue.empty(); // return false
//
// Constraints:
//
//   1 <= x <= 9
//   At most 100 calls will be made to push, pop, peek, and empty.
//   All the calls to pop and peek are valid.
//
// Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

/**
 * Your MyQueue object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(x);
 * param_2 := obj.Pop();
 * param_3 := obj.Peek();
 * param_4 := obj.Empty();
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

type myStack struct {
	data []int
	size int
}

func newMyStack() myStack {
	return myStack{
		data: make([]int, 100),
		size: 0,
	}
}

func (this *myStack) push(x int) {
	this.data[this.size] = x
	this.size++
}

func (this *myStack) pop() int {
	this.size--
	return this.data[this.size]
}

func (this *myStack) peek() int {
	return this.data[this.size-1]
}

func (this *myStack) empty() bool {
	return this.size == 0
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

type MyQueue struct {
	stack1 myStack
	stack2 myStack
}

func Constructor() MyQueue {
	return MyQueue{
		stack1: newMyStack(),
		stack2: newMyStack(),
	}
}

func (this *MyQueue) Push(x int) {
	this.stack1.push(x)
}

func (this *MyQueue) Pop() int {
	this.Peek()
	return this.stack2.pop()
}

func (this *MyQueue) Peek() int {
	if this.stack2.empty() {
		for !this.stack1.empty() {
			this.stack2.push(this.stack1.pop())
		}
	}
	return this.stack2.peek()
}

func (this *MyQueue) Empty() bool {
	return this.stack1.empty() && this.stack2.empty()
}
