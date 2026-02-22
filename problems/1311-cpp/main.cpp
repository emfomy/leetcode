// Source: https://leetcode.com/problems/get-watched-videos-by-your-friends
// Title: Get Watched Videos by Your Friends
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` people, each person has a unique id between `0` and `n-1`. Given the arrays `watchedVideos` and `friends`, where `watchedVideos[i]` and `friends[i]` contain the list of watched videos and the list of friends respectively for the person with `id = i`.
//
// Level **1** of videos are all watched videos by yourfriends, level **2** of videos are all watched videos by the friends of yourfriends and so on. In general, the level `k` of videos are allwatched videos by peoplewith the shortest path **exactly** equalto`k` with you. Given your`id` and the `level` of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/01/02/leetcode_friends_1.png
//
// ```
// Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
// Output: ["B","C"]
// Explanation:
// You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
// Person with id = 1 -> watchedVideos = ["C"]
// Person with id = 2 -> watchedVideos = ["B","C"]
// The frequencies of watchedVideos by your friends are:
// B -> 1
// C -> 2
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2020/01/02/leetcode_friends_2.png
//
// ```
// Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
// Output: ["D"]
// Explanation:
// You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
// ```
//
// **Constraints:**
//
// - `n == watchedVideos.length ==friends.length`
// - `2 <= n<= 100`
// - `1 <=watchedVideos[i].length <= 100`
// - `1 <=watchedVideos[i][j].length <= 8`
// - `0 <= friends[i].length < n`
// - `0 <= friends[i][j]< n`
// - `0 <= id < n`
// - `1 <= level < n`
// - if`friends[i]` contains `j`, then `friends[j]` contains `i`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// BFS
class Solution {
 public:
  vector<string> watchedVideosByFriends(      //
      vector<vector<string>>& watchedVideos,  //
      vector<vector<int>>& friends,           //
      int id, int level                       //
  ) {
    const int n = watchedVideos.size();
    if (level == 0) return watchedVideos[id];

    // Init
    auto visited = vector<bool>(n);
    auto currQue = vector<int>();
    auto nextQue = vector<int>();
    nextQue.reserve(n);
    currQue.reserve(n);

    // BFS
    visited[id] = true;
    currQue.push_back(id);
    for (int l = 0; l < level; ++l) {
      for (int currId : currQue) {
        for (int nextId : friends[currId]) {
          if (visited[nextId]) continue;
          visited[nextId] = true;
          nextQue.push_back(nextId);
        }
      }

      currQue.clear();
      swap(currQue, nextQue);
    }

    // Union videos
    auto videoCounter = unordered_map<string, int>();
    for (int id : currQue) {
      for (const string& video : watchedVideos[id]) {
        ++videoCounter[video];
      }
    }
    const int m = videoCounter.size();

    // Sort
    auto videoCounts = vector<pair<int, string>>();
    videoCounts.reserve(m);
    for (auto& [video, count] : videoCounter) {
      videoCounts.emplace_back(count, std::move(video));
    }
    sort(videoCounts.begin(), videoCounts.end());

    // Answer
    auto videos = vector<string>();
    videos.reserve(m);
    for (auto& [_, video] : videoCounts) {
      videos.push_back(std::move(video));
    }

    return videos;
  }
};
