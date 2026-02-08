// Source: https://leetcode.com/problems/snakes-and-ladders
// Title: Snakes and Ladders
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `n x n` integer matrix `board` where the cells are labeled from `1` to `n^2` in a <**Boustrophedon style** (https://en.wikipedia.org/wiki/Boustrophedon) starting from the bottom left of the board (i.e. `board[n - 1][0]`) and alternating direction each row.
//
// You start on square `1` of the board. In each move, starting from square `curr`, do the following:
//
// - Choose a destination square `next` with a label in the range `[curr + 1, min(curr + 6, n^2)]`.
//
// - This choice simulates the result of a standard **6-sided die roll**: i.e., there are always at most 6 destinations, regardless of the size of the board.
//
// - If `next` has a snake or ladder, you **must** move to the destination of that snake or ladder. Otherwise, you move to `next`.
// - The game ends when you reach the square `n^2`.
//
// A board square on row `r` and column `c` has a snake or ladder if `board[r][c] != -1`. The destination of that snake or ladder is `board[r][c]`. Squares `1` and `n^2` are not the starting points of any snake or ladder.
//
// Note that you only take a snake or ladder at most once per dice roll. If the destination to a snake or ladder is the start of another snake or ladder, you do **not** follow the subsequentsnake or ladder.
//
// - For example, suppose the board is `[[-1,4],[-1,3]]`, and on the first move, your destination square is `2`. You follow the ladder to square `3`, but do **not** follow the subsequent ladder to `4`.
//
// Return the least number of dice rolls required to reach the square `n^2`. If it is not possible to reach the square, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/09/23/snakes.png
//
// ```
// Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
// Output: 4
// Explanation:
// In the beginning, you start at square 1 (at row 5, column 0).
// You decide to move to square 2 and must take the ladder to square 15.
// You then decide to move to square 17 and must take the snake to square 13.
// You then decide to move to square 14 and must take the ladder to square 35.
// You then decide to move to square 36, ending the game.
// This is the lowest possible number of moves to reach the last square, so return 4.
// ```
//
// **Example 2:**
//
// ```
// Input: board = [[-1,-1],[-1,3]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `n == board.length == board[i].length`
// - `2 <= n <= 20`
// - `board[i][j]` is either `-1` or in the range `[1, n^2]`.
// - The squares labeled `1` and `n^2` are not the starting points of any snake or ladder.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// BFS + Heap (Dijkstra)
func snakesAndLadders(board [][]int) int {
	n := len(board)
	m := n * n

	// Convert to 1D board
	cells := make([]int, n*n)
	for i := range n {
		r := n - 1 - i
		for j := range n {
			c := j
			if i%2 == 1 {
				c = n - 1 - j
			}
			cells[i*n+j] = board[r][c] - 1 // minus one since we use 0-based here
		}
	}

	// BFS
	queue := make([]int, 0, m) // position queue
	queue = append(queue, 0)
	steps := make([]int, m) // visited in step
	steps[0] = 1
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		step := steps[curr]

		if curr == m-1 {
			return step - 1 // minus 1 since we start at 1
		}

		for dice := 1; dice <= 6; dice++ {
			next := curr + dice
			if next >= m {
				break
			}
			if cells[next] >= 0 {
				next = cells[next]
			}
			if steps[next] == 0 {
				queue = append(queue, next)
				steps[next] = step + 1
			}
		}
	}

	return -1
}
