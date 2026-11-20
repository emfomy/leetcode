// Source: https://leetcode.com/problems/count-mentions-per-user
// Title: Count Mentions Per User
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `numberOfUsers` representing the total number of users and an array `events` of size `n x 3`.
//
// Each `events[i]` can be either of the following two types:
//
// - **Message Event:** `["MESSAGE", "timestamp_i", "mentions_string_i"]`
//
// - This event indicates that a set of users was mentioned in a message at `timestamp_i`.
// - The `mentions_string_i` string can contain one of the following tokens:
//
// - `id<number>`: where `<number>` is an integer in range `[0,numberOfUsers - 1]`. There can be **multiple** ids separated by a single whitespace and may contain duplicates. This can mention even the offline users.
// - `ALL`: mentions **all** users.
// - `HERE`: mentions all **online** users.
//
// - **Offline Event:** `["OFFLINE", "timestamp_i", "id_i"]`
//
// - This event indicates that the user `id_i` had become offline at `timestamp_i` for **60 time units**. The user will automatically be online again at time `timestamp_i + 60`.
//
// Return an array `mentions` where `mentions[i]` represents the number of mentions the user with id `i` has across all `MESSAGE` events.
//
// All users are initially online, and if a user goes offline or comes back online, their status change is processed before handling any message event that occurs at the same timestamp.
//
// **Note **that a user can be mentioned **multiple** times in a **single** message event, and each mention should be counted **separately**.
//
// **Example 1:**
//
// ```
// Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
// Output: [2,2]
// Explanation:
// Initially, all users are online.
// At timestamp 10, `id1` and `id0` are mentioned. `mentions = [1,1]`
// At timestamp 11, `id0` goes **offline.**
// At timestamp 71, `id0` comes back **online** and `"HERE"` is mentioned. `mentions = [2,2]`
// ```
//
// **Example 2:**
//
// ```
// Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
// Output: [2,2]
// Explanation:
// Initially, all users are online.
// At timestamp 10, `id1` and `id0` are mentioned. `mentions = [1,1]`
// At timestamp 11, `id0` goes **offline.**
// At timestamp 12, `"ALL"` is mentioned. This includes offline users, so both `id0` and `id1` are mentioned. `mentions = [2,2]`
// ```
//
// **Example 3:**
//
// ```
// Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
// Output: [0,1]
// Explanation:
// Initially, all users are online.
// At timestamp 10, `id0` goes **offline.**
// At timestamp 12, `"HERE"` is mentioned. Because `id0` is still offline, they will not be mentioned. `mentions = [0,1]`
// ```
//
// **Constraints:**
//
// - `1 <= numberOfUsers <= 100`
// - `1 <= events.length <= 100`
// - `events[i].length == 3`
// - `events[i][0]` will be one of `MESSAGE` or `OFFLINE`.
// - `1 <= int(events[i][1]) <= 10^5`
// - The number of `id<number>` mentions in any `"MESSAGE"` event is between `1` and `100`.
// - `0 <= <number> <= numberOfUsers - 1`
// - It is **guaranteed** that the user id referenced in the `OFFLINE` event is **online** at the time the event occurs.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Simulation
class Solution {
  // Note that we handle offline
  static constexpr int OFFLINE = 1;
  static constexpr int MESSAGE = 2;
  static constexpr int MESSAGE_ALL = 3;
  static constexpr int MESSAGE_HERE = 4;

  struct Event {
    int ts;
    int kind;
    vector<int> ids;

    Event(int ts, int kind) : ts(ts), kind(kind) {}
    Event(int ts, int kind, int id) : ts(ts), kind(kind), ids({id}) {}
    Event(int ts, int kind, vector<int>& ids) : ts(ts), kind(kind), ids(ids) {}
  };

 public:
  vector<int> countMentions(int n, vector<vector<string>>& eventStrs) {
    auto mentions = vector<int>(n);
    auto onlines = vector(n, true);
    auto offlines = queue<pair<int, int>>();  // (id, timestamp)

    // Parse events
    auto events = vector<Event>();
    for (auto& eventStr : eventStrs) {
      auto kind = eventStr[0];
      auto ts = stoi(eventStr[1]);

      if (kind == "MESSAGE") {  // MESSAGE
        if (eventStr[2] == "ALL") {
          events.emplace_back(ts, MESSAGE_ALL);
        } else if (eventStr[2] == "HERE") {
          events.emplace_back(ts, MESSAGE_HERE);
        } else {
          auto items = string_split(eventStr[2]);
          auto ids = vector<int>();
          for (auto item : items) {
            ids.push_back(stoi(item.substr(2)));
          }
          events.emplace_back(ts, MESSAGE, ids);
        }
      } else {  // OFFLINE
        auto id = stoi(eventStr[2]);
        events.emplace_back(ts, OFFLINE, id);
      }
    }

    // Sort events
    sort(events.begin(), events.end(), [](Event& a, auto& b) -> bool {
      return make_pair(a.ts, a.kind) < make_pair(b.ts, b.kind);  // sort by ts, OFFLINE < MESSAGE
    });

    // Loop
    for (auto event : events) {
      // Make user online
      while (!offlines.empty() && offlines.front().second <= event.ts) {
        auto id = offlines.front().first;
        onlines[id] = true;
        offlines.pop();
      }

      // Process event
      switch (event.kind) {
        case OFFLINE: {
          auto id = event.ids[0];
          onlines[id] = false;
          offlines.push({id, event.ts + 60});
          break;
        }

        case MESSAGE: {
          for (auto id : event.ids) {
            ++mentions[id];
          }
          break;
        }

        case MESSAGE_ALL: {
          for (auto id = 0; id < n; ++id) {
            ++mentions[id];
          }
          break;
        }

        case MESSAGE_HERE: {
          for (auto id = 0; id < n; ++id) {
            if (onlines[id]) ++mentions[id];
          }
          break;
        }
      }
    }

    return mentions;
  }

 private:
  vector<string> string_split(const string& s, char delim = ' ') {
    istringstream iss(s);
    vector<string> words;
    string word;
    while (getline(iss, word, delim)) {
      words.push_back(word);
    }
    return words;
  }
};
