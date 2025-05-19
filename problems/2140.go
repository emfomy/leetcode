// Source: https://leetcode.com/problems/solving-questions-with-brainpower
// Title: Solving Questions With Brainpower
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D integer array `questions` where `questions[i] = [points_i, brainpower_i]`.
//
// The array describes the questions of an exam, where you have to process the questions **in order** (i.e., starting from question `0`) and make a decision whether to **solve** or **skip** each question. Solving question `i` will **earn** you `points_i` points but you will be **unable** to solve each of the next `brainpower_i` questions. If you skip question `i`, you get to make the decision on the next question.
//
// - For example, given `questions = [[3, 2], [4, 3], [4, 4], [2, 5]]`:
//
// - If question `0` is solved, you will earn `3` points but you will be unable to solve questions `1` and `2`.
// - If instead, question `0` is skipped and question `1` is solved, you will earn `4` points but you will be unable to solve questions `2` and `3`.
//
// Return the **maximum** points you can earn for the exam.
//
// **Example 1:**
//
// ```
// Input: questions = [[3,2],[4,3],[4,4],[2,5]]
// Output: 5
// Explanation: The maximum points can be earned by solving questions 0 and 3.
// - Solve question 0: Earn 3 points, will be unable to solve the next 2 questions
// - Unable to solve questions 1 and 2
// - Solve question 3: Earn 2 points
// Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more points.
// ```
//
// **Example 2:**
//
// ```
// Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
// Output: 7
// Explanation: The maximum points can be earned by solving questions 1 and 4.
// - Skip question 0
// - Solve question 1: Earn 2 points, will be unable to solve the next 2 questions
// - Unable to solve questions 2 and 3
// - Solve question 4: Earn 5 points
// Total points earned: 2 + 5 = 7. There is no other way to earn 7 or more points.
// ```
//
// **Constraints:**
//
// - `1 <= questions.length <= 10^5`
// - `questions[i].length == 2`
// - `1 <= points_i, brainpower_i <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use DP
func mostPoints(questions [][]int) int64 {
	n := len(questions)
	dp := make([]int64, n)
	res := int64(0)

	for i, question := range questions {
		point, brainpower := int64(question[0]), question[1]

		// skip this question
		if i+1 < n {
			dp[i+1] = max(dp[i+1], dp[i])
		} else {
			res = max(res, dp[i])
		}

		// solve this question
		if i+brainpower+1 < n {
			dp[i+brainpower+1] = max(dp[i+brainpower+1], dp[i]+point)
		} else {
			res = max(res, dp[i]+point)
		}
	}

	return res
}

// Use reverse DP
func mostPoints2(questions [][]int) int64 {
	n := len(questions)
	dp := make([]int64, n)
	dp[n-1] = int64(questions[n-1][0])

	for i := n - 2; i >= 0; i-- {
		point, brainpower := int64(questions[i][0]), questions[i][1]
		if i+brainpower+1 < n {
			dp[i] = max(dp[i+1], dp[i+brainpower+1]+point)
		} else {
			dp[i] = max(dp[i+1], point)
		}
	}

	return dp[0]
}
