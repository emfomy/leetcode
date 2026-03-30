// Source: https://leetcode.com/problems/design-twitter
// Title: Design Twitter
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the `10` most recent tweets in the user's news feed.
//
// Implement the `Twitter` class:
//
// - `Twitter()` Initializes your twitter object.
// - `void postTweet(int userId, int tweetId)` Composes a new tweet with ID `tweetId` by the user `userId`. Each call to this function will be made with a unique `tweetId`.
// - `List<Integer> getNewsFeed(int userId)` Retrieves the `10` most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be **ordered from most recent to least recent**.
// - `void follow(int followerId, int followeeId)` The user with ID `followerId` started following the user with ID `followeeId`.
// - `void unfollow(int followerId, int followeeId)` The user with ID `followerId` started unfollowing the user with ID `followeeId`.
//
// **Example 1:**
//
// ```
// Input:
// ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
// [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
//
// Output:
// [null, null, [5], null, null, [6, 5], null, [5]]
//
// Explanation:
// Twitter twitter = new Twitter();
// twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
// twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
// twitter.follow(1, 2);    // User 1 follows user 2.
// twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
// twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
// twitter.unfollow(1, 2);  // User 1 unfollows user 2.
// twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.
// ```
//
// **Constraints:**
//
// - `1 <= userId, followerId, followeeId <= 500`
// - `0 <= tweetId <= 10^4`
// - All the tweets have **unique** IDs.
// - At most `3 * 10^4` calls will be made to `postTweet`, `getNewsFeed`, `follow`, and `unfollow`.
// - A user cannot follow himself.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <deque>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

// Fanout-on-read (construct feed on read)
//
// Use array of hash set for follow relationship.
// Use deque for user tweet (newest to front).
// For news feed, loop through all its followee, and merge the tweets using a heap.
class Twitter {
  constexpr static int kMaxUser = 500;
  constexpr static int kMaxTweet = 10;

  struct Tweet {
    int id;
    int time;
  };

  using Queue = deque<Tweet>;
  using QueueIt = Queue::const_iterator;
  struct Node {
    QueueIt curr;  // current iterator
    QueueIt end;   // end iterator

    bool isEnd() const { return curr == end; }

    Node& operator++() {
      ++curr;
      return *this;
    }
  };
  struct NodeComp {
    bool operator()(const Node& a, const Node& b) { return a.curr->time < b.curr->time; };
  };
  using Heap = priority_queue<Node, vector<Node>, NodeComp>;  // max-heap by time

  array<unordered_set<int>, kMaxUser + 1> following;  // follower -> followee
  array<Queue, kMaxUser + 1> tweets;                  // user -> tweet
  int now = 0;

 public:
  Twitter() {
    for (int u = 1; u <= kMaxUser; ++u) {
      following[u].insert(u);  // follow self
    }
  }

  void postTweet(int userId, int tweetId) {
    if (tweets[userId].size() == kMaxTweet) tweets[userId].pop_back();
    tweets[userId].push_front({.id = tweetId, .time = ++now});
  }

  vector<int> getNewsFeed(int userId) {
    // Init heap
    Heap heap;
    for (const int followeeId : following[userId]) {
      Node node{tweets[followeeId].cbegin(), tweets[followeeId].cend()};
      if (!node.isEnd()) heap.push(node);
    }

    // Construct feed
    auto feed = vector<int>();
    feed.reserve(kMaxTweet);
    while (!heap.empty() && feed.size() < kMaxTweet) {
      Node node = heap.top();
      heap.pop();
      feed.push_back(node.curr->id);

      // Next node
      ++node;
      if (!node.isEnd()) heap.push(node);
    }

    return feed;
  }

  void follow(int followerId, int followeeId) {
    if (followerId == followeeId) return;
    following[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    if (followerId == followeeId) return;
    following[followerId].erase(followeeId);
  }
};
