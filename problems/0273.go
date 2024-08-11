// Source: https://leetcode.com/problems/integer-to-english-words
// Title: Integer to English Words
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert a non-negative integer num to its English words representation.
//
// Example 1:
//
//   Input: num = 123
//   Output: "One Hundred Twenty Three"
//
// Example 2:
//
//   Input: num = 12345
//   Output: "Twelve Thousand Three Hundred Forty Five"
//
// Example 3:
//
//   Input: num = 1234567
//   Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
//
// Constraints:
//
//   0 <= num <= 2^31 - 1
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var names = map[int]string{
	0:             "Zero",
	1:             "One",
	2:             "Two",
	3:             "Three",
	4:             "Four",
	5:             "Five",
	6:             "Six",
	7:             "Seven",
	8:             "Eight",
	9:             "Nine",
	10:            "Ten",
	11:            "Eleven",
	12:            "Twelve",
	13:            "Thirteen",
	14:            "Fourteen",
	15:            "Fifteen",
	16:            "Sixteen",
	17:            "Seventeen",
	18:            "Eighteen",
	19:            "Nineteen",
	20:            "Twenty",
	30:            "Thirty",
	40:            "Forty",
	50:            "Fifty",
	60:            "Sixty",
	70:            "Seventy",
	80:            "Eighty",
	90:            "Ninety",
	100:           "Hundred",
	1_000:         "Thousand",
	1_000_000:     "Million",
	1_000_000_000: "Billion",
}

func numberToWords(num int) string {
	if num < 20 {
		return names[num]
	}

	if num < 100 {
		ones := num % 10
		tens := num - ones
		if ones == 0 {
			return names[tens]
		}
		return names[tens] + " " + names[ones]
	}

	if num < 1_000 {
		remainder := num % 100
		quotient := num / 100
		if remainder == 0 {
			return names[quotient] + " " + names[100]
		}
		return names[quotient] + " " + names[100] + " " + numberToWords(remainder)
	}

	if num < 1_000_000 {
		remainder := num % 1_000
		quotient := num / 1_000
		if remainder == 0 {
			return numberToWords(quotient) + " " + names[1_000]
		}
		return numberToWords(quotient) + " " + names[1_000] + " " + numberToWords(remainder)
	}

	if num < 1_000_000_000 {
		remainder := num % 1_000_000
		quotient := num / 1_000_000
		if remainder == 0 {
			return numberToWords(quotient) + " " + names[1_000_000]
		}
		return numberToWords(quotient) + " " + names[1_000_000] + " " + numberToWords(remainder)
	}

	remainder := num % 1_000_000_000
	quotient := num / 1_000_000_000
	if remainder == 0 {
		return numberToWords(quotient) + " " + names[1_000_000_000]
	}
	return numberToWords(quotient) + " " + names[1_000_000_000] + " " + numberToWords(remainder)
}
