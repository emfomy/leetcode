// Source: https://leetcode.com/problems/number-of-laser-beams-in-a-bank
// Title: Find Players With Zero or One Losses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array matches where matches[i] = [winner_i, loser_i] indicates that the player winner_i defeated player loser_i in a match.
//
// Return a list answer of size 2 where:
//   * answer[0] is a list of all players that have not lost any matches.
//   * answer[1] is a list of all players that have lost exactly one match.
//
// The values in the two lists should be returned in increasing order.
//
// Note:
//   * You should only consider the players that have played at least one match.
//   * The testcases will be generated such that no two matches will have the same outcome.
//
// Example 1:
//
//   Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
//   Output: [[1,2,10],[4,5,7,8]]
//   Explanation:
//     Players 1, 2, and 10 have not lost any matches.
//     Players 4, 5, 7, and 8 each have lost one match.
//     Players 3, 6, and 9 each have lost two matches.
//     Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].
//
// Example 2:
//
//   Input: matches = [[2,3],[1,3],[5,4],[6,4]]
//   Output: [[1,2,5,6],[]]
//   Explanation:
//     Players 1, 2, 5, and 6 have not lost any matches.
//     Players 3 and 4 each have lost two matches.
//     Thus, answer[0] = [1,2,5,6] and answer[1] = [].
//
// Constraints:
//
//   * 1 <= matches.length <= 10^5
//   * matches[i].length == 2
//   * 1 <= winner_i, loser_i <= 10^5
//   * winner_i != loser_i
//   * All matches[i] are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func findWinners(matches [][]int) [][]int {
	n := int(1e5 + 1)
	winCount := make([]int, n)
	loseCount := make([]int, n)

	for _, match := range matches {
		winCount[match[0]]++
		loseCount[match[1]]++
	}

	winners := make([]int, 0, len(winCount))
	for player, count := range winCount {
		if count > 0 && loseCount[player] == 0 {
			winners = append(winners, player)
		}
	}

	losers := make([]int, 0, len(loseCount))
	for player, count := range loseCount {
		if count == 1 {
			losers = append(losers, player)
		}
	}

	return [][]int{winners, losers}
}
