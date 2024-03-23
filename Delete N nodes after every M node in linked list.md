# Delete N nodes after every M node in linked list

### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/delete-n-nodes-after-m-nodes-of-a-linked-list_668903?leftPanelTabValue=PROBLEM)

## ✔️Approach - 1  (using array)
```java

import java.util.*;

// usign array 
public class Solution {
	public static Node<Integer> getListAfterDeleteOperation(Node<Integer> head, int n, int m) {
		List<Integer> arr = new ArrayList<>();
		Node<Integer> temp = head;
		while(temp != null){ // creating array from list values
			arr.add(temp.data);
			temp = temp.next;
		}

		// in this array
		int i = 0;
		int size = arr.size();
		while(i < size){
			// skip m nodes, 
			for(int j = 0; (j < m && i < size); j++)
				i++;
			// delete n nodes
			for(int j = 0; (j < n && i < size); j++){
				arr.set(i, Integer.MAX_VALUE);  // put inf coz later on we will create a linked list with non inf nodes
				i++;
			}
		}

		// from this list create a new Linekd List (nonly with non Infinity values)
		Node dummyHead = new Node(-1);
		Node dummyTail = dummyHead;
		for(i = 0; i < size; i++){
			if(arr.get(i) == Integer.MAX_VALUE)
				continue;
			dummyTail.next = new Node(arr.get(i));
			dummyTail = dummyTail.next;
		}

		return dummyHead.next;
	}
}
```
