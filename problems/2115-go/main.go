// Source: https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies
// Title: Find All Possible Recipes from Given Supplies
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have information about `n` different recipes. You are given a string array `recipes` and a 2D string array `ingredients`. The `i^th` recipe has the name `recipes[i]`, and you can **create** it if you have **all** the needed ingredients from `ingredients[i]`. A recipe can also be an ingredient for **other **recipes, i.e., `ingredients[i]` may contain a string that is in `recipes`.
//
// You are also given a string array `supplies` containing all the ingredients that you initially have, and you have an infinite supply of all of them.
//
// Return a list of all the recipes that you can create. You may return the answer in **any order**.
//
// Note that two recipes may contain each other in their ingredients.
//
// **Example 1:**
//
// ```
// Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
// Output: ["bread"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
// ```
//
// **Example 2:**
//
// ```
// Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
// Output: ["bread","sandwich"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
// We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
// ```
//
// **Example 3:**
//
// ```
// Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
// Output: ["bread","sandwich","burger"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
// We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
// We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".
// ```
//
// **Constraints:**
//
// - `n == recipes.length == ingredients.length`
// - `1 <= n <= 100`
// - `1 <= ingredients[i].length, supplies.length <= 100`
// - `1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10`
// - `recipes[i], ingredients[i][j]`, and `supplies[k]` consist only of lowercase English letters.
// - All the values of `recipes` and `supplies`combined are unique.
// - Each `ingredients[i]` does not contain any duplicate values.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// DFS
func findAllRecipes(recipes []string, ingredients [][]string, supplies []string) []string {
	r := len(recipes)
	s := len(supplies)

	// Prepare depend map
	dependMap := make(map[string][]string, r+s) // map ingredient to recipe
	for i, recipe := range recipes {
		for _, ingredient := range ingredients[i] {
			dependMap[ingredient] = append(dependMap[ingredient], recipe)
		}
	}

	// Prepare recipe map
	recipeMap := make(map[string]map[string]bool) // map recipe to ingredient
	for i, recipe := range recipes {
		recipeMap[recipe] = make(map[string]bool, len(ingredients[i]))
		for _, ingredient := range ingredients[i] {
			recipeMap[recipe][ingredient] = true
		}
	}

	// DFS
	visited := make(map[string]bool, r) // visited recipe (i.e. creatable)

	var dfs func(item string)
	dfs = func(item string) {
		if visited[item] { // visited
			return
		}
		if len(recipeMap[item]) > 0 { // not ready
			return
		}
		visited[item] = true
		for _, dependent := range dependMap[item] {
			delete(recipeMap[dependent], item)
			dfs(dependent)
		}
	}

	for _, supply := range supplies {
		dfs(supply)
	}

	res := make([]string, 0, r)
	for _, recipe := range recipes {
		if visited[recipe] {
			res = append(res, recipe)
		}
	}

	return res
}

// Topological Sort (Kahn's Algorithm)
func findAllRecipes2(recipes []string, ingredients [][]string, supplies []string) []string {
	r := len(recipes)
	s := len(supplies)
	res := make([]string, 0, r)

	// Prepare depend map
	dependMap := make(map[string][]string, r+s) // map ingredient to recipe
	for i, recipe := range recipes {
		for _, ingredient := range ingredients[i] {
			dependMap[ingredient] = append(dependMap[ingredient], recipe)
		}
	}

	// Count in-degree
	inDegree := make(map[string]int, r)
	for i, recipe := range recipes {
		inDegree[recipe] = len(ingredients[i])
	}

	// Loop through the queue
	queue := supplies
	for len(queue) > 0 {
		item := queue[0]
		queue = queue[1:]
		for _, dependent := range dependMap[item] {
			inDegree[dependent]--
			if inDegree[dependent] == 0 {
				res = append(res, dependent)
				queue = append(queue, dependent)
			}
		}
	}

	return res
}

func main() {
	fmt.Println(findAllRecipes2(
		[]string{
			"bread", "sandwich",
		},
		[][]string{
			{"yeast", "flour"},
			{"bread", "meat"},
		},
		[]string{
			"yeast", "flour",
		},
	))
}
