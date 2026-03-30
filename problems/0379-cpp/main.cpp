// Source: https://leetcode.com/problems/design-phone-directory
// Title: Design Phone Directory
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a phone directory that initially has `maxNumbers` empty slots that can store numbers. The directory should store numbers, check if a certain slot is empty or not, and empty a given slot.
//
// Implement the `PhoneDirectory` class:
//
// - `PhoneDirectory(int maxNumbers)` Initializes the phone directory with the number of available slots `maxNumbers`.
// - `int get()` Provides a number that is not assigned to anyone. Returns `-1` if no number is available.
// - `bool check(int number)` Returns `true` if the slot `number` is available and `false` otherwise.
// - `void release(int number)` Recycles or releases the slot `number`.
//
// **Example 1:**
//
// ```
// Input
//
// ["PhoneDirectory", "get", "get", "check", "get", "check", "release", "check"]
// [[3], [], [], [2], [], [2], [2], [2]]
// Output
//
// [null, 0, 1, true, 2, false, null, true]
//
// Explanation
//
// PhoneDirectory phoneDirectory = new PhoneDirectory(3);
// phoneDirectory.get();      // It can return any available phone number. Here we assume it returns 0.
// phoneDirectory.get();      // Assume it returns 1.
// phoneDirectory.check(2);   // The number 2 is available, so return true.
// phoneDirectory.get();      // It returns 2, the only number that is left.
// phoneDirectory.check(2);   // The number 2 is no longer available, so return false.
// phoneDirectory.release(2); // Release number 2 back to the pool.
// phoneDirectory.check(2);   // Number 2 is available again, return true.
// ```
//
// **Constraints:**
//
// - `1 <= maxNumbers <= 10^4`
// - `0 <= number < maxNumbers`
// - At most `2 * 10^4` calls will be made to `get`, `check`, and `release`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Array
//
// Use two array for number to index bidirectional mapping.
//
// We put the used number at front.
// When release, swap the number to the end.
class PhoneDirectory {
  vector<int> idx2num;
  vector<int> num2idx;
  const int capacity;
  int size;

 public:
  // O(N)
  PhoneDirectory(int maxNumbers)
      : idx2num(maxNumbers),   //
        num2idx(maxNumbers),   //
        capacity(maxNumbers),  //
        size(0) {
    iota(idx2num.begin(), idx2num.end(), 0);
    iota(num2idx.begin(), num2idx.end(), 0);
  }

  // O(1)
  int get() {
    if (size == capacity) return -1;
    return idx2num[size++];
  }

  // O(1)
  bool check(int number) {  //
    return num2idx[number] >= size;
  }

  // O(1)
  void release(int number) {
    if (check(number)) return;  // already released

    --size;
    int idx = num2idx[number];
    int lastNum = idx2num[size];

    swap(idx2num[size], idx2num[idx]);
    swap(num2idx[number], num2idx[lastNum]);
  }
};

// Array
//
// We initialize idx2num and num2idx empty,
// and extend idx2num and num2idx if needed.
class PhoneDirectory2 {
  vector<int> idx2num;
  vector<int> num2idx;
  const int capacity;
  int size;

 public:
  // O(1)
  PhoneDirectory2(int maxNumbers)
      : idx2num(),             //
        num2idx(),             //
        capacity(maxNumbers),  //
        size(0) {}

  int get() {
    if (size == capacity) return -1;

    // Issue new number
    if (idx2num.size() == size) {
      int num = size++;
      idx2num.push_back(num);
      num2idx.push_back(num);
      return num;
    }

    // Issue old number
    return idx2num[size++];
  }

  bool check(int number) {
    // Un-issued number
    if (number >= idx2num.size()) return true;

    // Check issued number
    return num2idx[number] >= size;
  }

  void release(int number) {
    if (check(number)) return;  // already released

    --size;
    int idx = num2idx[number];
    int lastNum = idx2num[size];

    swap(idx2num[size], idx2num[idx]);
    swap(num2idx[number], num2idx[lastNum]);
  }
};
