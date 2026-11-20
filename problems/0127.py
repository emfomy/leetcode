# Source: https://leetcode.com/problems/word-ladder
# Title: Word Ladder
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s_1 -> s_2 -> ... -> s_k` such that:
#
# - Every adjacent pair of words differs by a single letter.
# - Every `s_i` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in `wordList`.
# - `s_k == endWord`
#
# Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return the **number of words** in the **shortest transformation sequence** from `beginWord` to `endWord`, or `0` if no such sequence exists.
#
# **Example 1:**
#
# ```
# Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
# Output: 5
# Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
# ```
#
# **Example 2:**
#
# ```
# Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
# Output: 0
# Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
# ```
#
# **Constraints:**
#
# - `1 <= beginWord.length <= 10`
# - `endWord.length == beginWord.length`
# - `1 <= wordList.length <= 5000`
# - `wordList[i].length == beginWord.length`
# - `beginWord`, `endWord`, and `wordList[i]` consist of lowercase English letters.
# - `beginWord != endWord`
# - All the words in `wordList` are **unique**.
#
################################################################################################################################


from collections import defaultdict, deque
from typing import Generator, List


# Create Graph (TLE)
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        def diff(word1: str, word2: str) -> int:
            return sum((int(ch1 != ch2) for ch1, ch2 in zip(word1, word2)))

        # Prepare graph
        graph: defaultdict[str, list[str]] = defaultdict(list)
        for word in wordList:
            if diff(beginWord, word) == 1:
                graph[beginWord].append(word)
                graph[word].append(beginWord)
        for i, word1 in enumerate(wordList):
            for word2 in wordList[:i]:
                if diff(word1, word2) == 1:
                    graph[word1].append(word2)
                    graph[word2].append(word1)

        # BFS
        visited: defaultdict[str, bool] = defaultdict(bool)
        queue: deque[tuple[str, int]] = deque()  # word, dist
        queue.append((beginWord, 1))
        visited[beginWord] = True

        while queue:
            head, dist = queue.popleft()
            for word in graph[head]:
                if word == endWord:
                    return dist + 1
                if not visited[word]:
                    visited[word] = True
                    queue.append((word, dist + 1))

        return 0


# Use bucket to create graph
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList:
            return 0

        # Word to bucket
        def word2key(word: str) -> Generator[str, None, None]:
            for i in range(len(word)):
                yield word[:i] + "*" + word[i + 1 :]

        buckets: defaultdict[str, list[str]] = defaultdict(list)
        for key in word2key(beginWord):
            buckets[key].append(beginWord)
        for word in wordList:
            for key in word2key(word):
                buckets[key].append(word)

        # Prepare graph
        graph: defaultdict[str, list[str]] = defaultdict(list)
        for bucket in buckets.values():
            for i, word1 in enumerate(bucket):
                for word2 in bucket[:i]:
                    graph[word1].append(word2)
                    graph[word2].append(word1)

        # BFS
        visited: defaultdict[str, bool] = defaultdict(bool)
        queue: deque[tuple[str, int]] = deque()  # word, dist
        queue.append((beginWord, 1))
        visited[beginWord] = True

        while queue:
            head, dist = queue.popleft()
            for word in graph[head]:
                if word == endWord:
                    return dist + 1
                if not visited[word]:
                    visited[word] = True
                    queue.append((word, dist + 1))

        return 0
