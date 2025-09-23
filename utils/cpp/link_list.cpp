#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* array2list(vector<int>&& arr) {
  ListNode* ret;
  for (auto item : arr) {
    ret = new ListNode(item, ret);
  }
  return ret;
}
