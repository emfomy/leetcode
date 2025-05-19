package utils

type ListNode struct {
	Val  int
	Next *ListNode
}

func array2List(arr ...int) *ListNode {
	head := &ListNode{
		Val: arr[0],
	}

	curr := head
	for _, val := range arr[1:] {
		curr.Next = &ListNode{
			Val: val,
		}
		curr = curr.Next
	}

	return head
}

func list2Array(head *ListNode) []int {
	arr := make([]int, 0)
	for head != nil {
		arr = append(arr, head.Val)
		head = head.Next
	}
	return arr
}
