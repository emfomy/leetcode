// Source: https://leetcode.com/problems/min-stack
// Title: Min Stack
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
//
// Implement the `MinStack` class:
//
// - `MinStack()` initializes the stack object.
// - `void push(int val)` pushes the element `val` onto the stack.
// - `void pop()` removes the element on the top of the stack.
// - `int top()` gets the top element of the stack.
// - `int getMin()` retrieves the minimum element in the stack.
//
// You must implement a solution with `O(1)` time complexity for each function.
//
// **Example 1:**
//
// ```
// Input
//
// ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]
//
// Output
//
// [null,null,null,null,-3,null,0,-2]
//
// Explanation
//
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin(); // return -3
// minStack.pop();
// minStack.top();    // return 0
// minStack.getMin(); // return -2
// ```
//
// **Constraints:**
//
// - `-2^31 <= val <= 2^31 - 1`
// - Methods `pop`, `top` and `getMin` operations will always be called on **non-empty** stacks.
// - At most `3 * 10^4` calls will be made to `push`, `pop`, `top`, and `getMin`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>

using namespace std;

// Use two stack
// One for values, one for min values (until now)
class MinStack {
  stack<int> vals;
  stack<int> mins;

 public:
  void push(int val) {
    vals.push(val);
    if (mins.empty()) {
      mins.push(val);
    } else {
      mins.push(min(mins.top(), val));
    }
  }

  void pop() {
    vals.pop();
    mins.pop();
  }

  int top() { return vals.top(); }

  int getMin() { return mins.top(); }
};

// Use two stack
// One for values, one for min values (until now).
// Update min stack only when new value is smaller.
class MinStack2 {
  stack<int> vals;
  stack<int> mins;

 public:
  void push(int val) {
    if (mins.empty() || mins.top() >= val) mins.push(val);
    vals.push(val);
  }

  void pop() {
    if (mins.top() == vals.top()) mins.pop();
    vals.pop();
  }

  int top() { return vals.top(); }

  int getMin() { return mins.top(); }
};

// Use stack of pair
class MinStack3 {
  stack<pair<int, int>> data;

 public:
  void push(int val) {
    if (data.empty()) {
      data.push({val, val});
    } else {
      data.push({val, min(data.top().second, val)});
    }
  }

  void pop() { data.pop(); }

  int top() { return data.top().first; }

  int getMin() { return data.top().second; }
};
