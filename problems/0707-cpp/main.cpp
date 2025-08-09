// Source: https://leetcode.com/problems/design-linked-list
// Title: Design Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design your implementation of the linked list. You can choose to use a singly or doubly linked list.<br>
// A node in a singly linked list should have two attributes: `val` and `next`. `val` is the value of the current node, and `next` is a pointer/reference to the next node.<br>
// If you want to use the doubly linked list, you will need one more attribute `prev` to indicate the previous node in the linked list. Assume all nodes in the linked list are **0-indexed**.
//
// Implement the `MyLinkedList` class:
//
// - `MyLinkedList()` Initializes the `MyLinkedList` object.
// - `int get(int index)` Get the value of the `index^th` node in the linked list. If the index is invalid, return `-1`.
// - `void addAtHead(int val)` Add a node of value `val` before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
// - `void addAtTail(int val)` Append a node of value `val` as the last element of the linked list.
// - `void addAtIndex(int index, int val)` Add a node of value `val` before the `index^th` node in the linked list. If `index` equals the length of the linked list, the node will be appended to the end of the linked list. If `index` is greater than the length, the node **will not be inserted**.
// - `void deleteAtIndex(int index)` Delete the `index^th` node in the linked list, if the index is valid.
//
// **Example 1:**
//
// ```
// Input
//
// ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
// [[], [1], [3], [1, 2], [1], [1], [1]]
// Output
//
// [null, null, null, null, 2, null, 3]
//
// Explanation
//
// MyLinkedList myLinkedList = new MyLinkedList();
// myLinkedList.addAtHead(1);
// myLinkedList.addAtTail(3);
// myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
// myLinkedList.get(1);              // return 2
// myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
// myLinkedList.get(1);              // return 3
// ```
//
// **Constraints:**
//
// - `0 <= index, val <= 1000`
// - Please do not use the built-in LinkedList library.
// - At most `2000` calls will be made to `get`, `addAtHead`, `addAtTail`, `addAtIndex` and `deleteAtIndex`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
using namespace std;

// Use vector
class MyLinkedList {
  vector<int> data;

 public:
  MyLinkedList() {  //
    data.reserve(1000);
  }

  int get(int index) {  //
    if (index >= data.size()) return -1;
    return data[index];
  }

  void addAtHead(int val) {  //
    data.insert(data.cbegin(), val);
  }

  void addAtTail(int val) {  //
    data.push_back(val);
  }

  void addAtIndex(int index, int val) {  //
    if (index > data.size()) return;
    data.insert(data.cbegin() + index, val);
  }

  void deleteAtIndex(int index) {  //
    if (index >= data.size()) return;
    data.erase(data.cbegin() + index);
  }
};

class MyLinkedList2 {
  class Node {
   public:
    int val;
    Node* next;
  };

  Node* end;
  Node* begin;
  int size;

  Node* getIter(int index) {
    if (index > size) return nullptr;
    auto node = begin;
    for (auto i = 0; i < index; i++) {
      node = node->next;
    }
    return node;
  }

 public:
  MyLinkedList2() {  //
    end = new Node();
    begin = new Node();
    begin->next = end;
    size = 0;
  }

  int get(int index) {  //
    auto it = getIter(index);
    if (it == nullptr || it->next == end) return -1;

    return it->next->val;
  }

  void addAtHead(int val) {  //
    addAtIndex(0, val);
  }

  void addAtTail(int val) {  //
    addAtIndex(size, val);
  }

  void addAtIndex(int index, int val) {  //
    auto it = getIter(index);
    if (it == nullptr) return;

    auto node = new Node();
    node->val = val;
    node->next = it->next;
    it->next = node;
    size++;
  }

  void deleteAtIndex(int index) {  //
    auto it = getIter(index);
    if (it == nullptr || it->next == end) return;

    auto node = it->next;
    it->next = node->next;
    delete node;
    size--;
  }
};
