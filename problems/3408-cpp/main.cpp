// Source: https://leetcode.com/problems/design-task-manager
// Title: Design Task Manager
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a task management system that allows users to manage their tasks, each associated with a priority. The system should efficiently handle adding, modifying, executing, and removing tasks.
//
// Implement the `TaskManager` class:
//
// -
// `TaskManager(vector<vector<int>>&amp; tasks)` initializes the task manager with a list of user-task-priority triples. Each element in the input list is of the form `[userId, taskId, priority]`, which adds a task to the specified user with the given priority.
//
// -
// `void add(int userId, int taskId, int priority)` adds a task with the specified `taskId` and `priority` to the user with `userId`. It is **guaranteed** that `taskId` does not exist in the system.
//
// -
// `void edit(int taskId, int newPriority)` updates the priority of the existing `taskId` to `newPriority`. It is **guaranteed** that `taskId` exists in the system.
//
// -
// `void rmv(int taskId)` removes the task identified by `taskId` from the system. It is **guaranteed** that `taskId` exists in the system.
//
// -
// `int execTop()` executes the task with the **highest** priority across all users. If there are multiple tasks with the same **highest** priority, execute the one with the highest `taskId`. After executing, the** **`taskId`** **is **removed** from the system. Return the `userId` associated with the executed task. If no tasks are available, return -1.
//
// **Note** that a user may be assigned multiple tasks.
//
// **Example 1:**
//
// ```
// Input:
// ["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]<br>
// [[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]
//
// Output:
// [null, null, null, 3, null, null, 5]
//
// Explanation:
// TaskManager taskManager = new TaskManager([[1, 101, 10], [2, 102, 20], [3, 103, 15]]); // Initializes with three tasks for Users 1, 2, and 3.<br>
// taskManager.add(4, 104, 5); // Adds task 104 with priority 5 for User 4.<br>
// taskManager.edit(102, 8); // Updates priority of task 102 to 8.<br>
// taskManager.execTop(); // return 3. Executes task 103 for User 3.<br>
// taskManager.rmv(101); // Removes task 101 from the system.<br>
// taskManager.add(5, 105, 15); // Adds task 105 with priority 15 for User 5.<br>
// taskManager.execTop(); // return 5. Executes task 105 for User 5.
// ```
//
// **Constraints:**
//
// - `1 <= tasks.length <= 10^5`
// - `0 <= userId <= 10^5`
// - `0 <= taskId <= 10^5`
// - `0 <= priority <= 10^9`
// - `0 <= newPriority <= 10^9`
// - At most `2 * 10^5` calls will be made in **total** to `add`, `edit`, `rmv`, and `execTop` methods.
// - The input is generated such that `taskId` will be valid.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Use Set
class TaskManager {
  unordered_map<int, pair<int, int>> taskMap;  // task -> (user, priority)
  set<pair<int, int>> taskSet;                 // { (priority, task) }

 public:
  TaskManager(vector<vector<int>>& tasks) {
    for (auto task : tasks) {
      add(task[0], task[1], task[2]);
    }
  }

  void add(int userId, int taskId, int priority) {
    taskMap[taskId] = {userId, priority};
    taskSet.insert({priority, taskId});
  }

  void edit(int taskId, int newPriority) {
    auto& task = taskMap[taskId];
    auto oldPriority = task.second;
    task.second = newPriority;

    taskSet.erase({oldPriority, taskId});
    taskSet.insert({newPriority, taskId});
  }

  void rmv(int taskId) {
    auto it = taskMap.find(taskId);
    auto priority = it->second.second;
    taskMap.erase(it);
    taskSet.erase({priority, taskId});
  }

  int execTop() {
    if (taskSet.empty()) return -1;

    auto setIt = taskSet.end();
    --setIt;
    auto taskId = setIt->second;
    taskSet.erase(setIt);

    auto taskIt = taskMap.find(taskId);
    auto userId = taskIt->second.first;
    taskMap.erase(taskIt);

    return userId;
  }
};

// Use Heap
class TaskManager2 {
  unordered_map<int, pair<int, int>> taskMap;  // task -> (user, priority)
  priority_queue<pair<int, int>> taskQueue;    // (priority, task)

 public:
  TaskManager2(vector<vector<int>>& tasks) {
    for (auto task : tasks) {
      add(task[0], task[1], task[2]);
    }
  }

  void add(int userId, int taskId, int priority) {
    taskMap[taskId] = {userId, priority};
    taskQueue.push({priority, taskId});
  }

  void edit(int taskId, int newPriority) {
    auto& task = taskMap[taskId];
    task.second = newPriority;
    taskQueue.push({newPriority, taskId});  // lazy update
  }

  void rmv(int taskId) {
    taskMap.erase(taskId);  // lazy delete
  }

  int execTop() {
    while (!taskQueue.empty()) {
      auto [priority, taskId] = taskQueue.top();
      taskQueue.pop();

      auto taskIt = taskMap.find(taskId);
      if (taskIt != taskMap.end() && taskIt->second.second == priority) {
        auto userId = taskIt->second.first;
        taskMap.erase(taskIt);
        return userId;
      }
    }
    return -1;
  }
};

// Use Heap
class TaskManager3 {
  unordered_map<int, pair<int, int>> taskMap;  // task -> (user, priority)
  priority_queue<pair<int, int>> taskQueue;    // (priority, task)

 public:
  TaskManager3(vector<vector<int>>& tasks) {
    for (auto task : tasks) {
      add(task[0], task[1], task[2]);
    }
  }

  void add(int userId, int taskId, int priority) {
    taskMap[taskId] = {userId, priority};
    taskQueue.push({priority, taskId});
  }

  void edit(int taskId, int newPriority) {
    auto& task = taskMap[taskId];
    task.second = newPriority;
    taskQueue.push({newPriority, taskId});  // lazy update
  }

  void rmv(int taskId) {
    taskMap[taskId].second = -1;  // lazy delete
  }

  int execTop() {
    while (!taskQueue.empty()) {
      auto [priority, taskId] = taskQueue.top();
      taskQueue.pop();

      if (taskMap[taskId].second == priority) {
        auto userId = taskMap[taskId].first;
        taskMap[taskId].second = -1;
        return userId;
      }
    }

    return -1;
  }
};
