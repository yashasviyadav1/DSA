
## Heaps Implementation in Python:- 

HeapSort Dry Run:- 
![Diagram Dry run - HeapSort](https://i.ibb.co/Df0Rc55r/image.png)

```py
## H E A P S

#### lets implement Max heap using arrays
#### first we are given array we need to build a max heap using it so we will use 'buildHeap()'
#### buildheap internally uses 'max_heapify' on each node, 'min_heapify' for min heap on each node
#### remember leaf nodes are themselves max or min heap, so we only call heapify function on half nodes of the tree (internal nodes)
#### from N/2-1 to 0 (for 0 indexed heap)

### Time: Building a Heap: O(n)
### Time: HeapSort : O(n * logN)

"""
buildHeap()
minHeapify()
maxHeapify()
heapSort() - diagram: https://i.ibb.co/Df0Rc55r/image.png
"""


## this function is called on 1 node, its task is to fix the heap condition of curr node i
## it basically checks left and rigth node of the curr node and whichever is largest it swap its value in ith node
## then call the heapify on the value which we swapped with (left or right child)
def maxHeapify(arr, N, i): 
	leftChildIndex = i*2 + 1
	rightChildIndex = i*2 + 2

	largestValueIndex = i # we assign it to i so at the end we check if i != largestValueIndex means something changed, so we found a larger value in child of i
	if leftChildIndex < N and arr[leftChildIndex] > arr[largestValueIndex]:
		largestValueIndex = leftChildIndex

	if rightChildIndex < N and arr[rightChildIndex] > arr[largestValueIndex]:
		largestValueIndex = rightChildIndex

	# something was changed, found a larger value in childs
	if i != largestValueIndex:
		# swap
		arr[i],arr[largestValueIndex] = arr[largestValueIndex], arr[i]
		# since we swaped child with curr value, so the childs heap property might got disrupted, so heapify it as well
		maxHeapify(arr, N, largestValueIndex)

def buildMaxHeap(arr):
	N = len(arr)
	for i in range(N//2-1, -1, -1): # N/2 - 1 to 0 (considering 0 based indexing of heap)
		maxHeapify(arr, N, i)



## this function is called on 1 node, its task is to fix the heap condition of curr node i
## it basically checks left and rigth node of the curr node and whichever is smallest it swap its value in ith node (min heap property - smallest node will be parent)
## then call the heapify on the value which we swapped with (left or right child)
def minHeapify(arr, N, i): 
	leftChildIndex = i*2 + 1
	rightChildIndex = i*2 + 2

	smallestValueIndex = i # # we assign it to i so at the end we check if i != smallestValueIndex means something changed, so we found a smaller value in child of i
	if leftChildIndex < N and arr[leftChildIndex] < arr[smallestValueIndex]:
		smallestValueIndex = leftChildIndex

	if rightChildIndex < N and arr[rightChildIndex] < arr[smallestValueIndex]:
		smallestValueIndex = rightChildIndex

	# something was changed, found a smaller value in childs
	if i != smallestValueIndex:
		# swap
		arr[i],arr[smallestValueIndex] = arr[smallestValueIndex], arr[i]
		# since we swaped child with curr value, so the childs heap property might got disrupted, so heapify it as well
		minHeapify(arr, N, smallestValueIndex)

def buildMinHeap(arr):
	N = len(arr)
	for i in range(N//2-1, -1, -1): # N/2 - 1 to 0 (considering 0 based indexing of heap)
		minHeapify(arr, N, i)

def printHeap(arr):
	N = len(arr)
	queue = []
	queue.append(0) # appending 1st elements (roots) index (0 based index)
	while len(queue) > 0:
		size = len(queue)
		for i in range(0, size):

			frontIndex = queue.pop(0) # q pops at front
			print(arr[frontIndex], end=" ")

			leftChildIndex = 2*frontIndex + 1
			rightChildIndex = 2*frontIndex + 2

			if leftChildIndex < N:
				queue.append(leftChildIndex)

			if rightChildIndex < N:
				queue.append(rightChildIndex) # appending index into q and not element because only with index we can know the left and right childs index
		print()

def heapSort(arr): # dry run diagram: https://i.ibb.co/Df0Rc55r/image.png
	N = len(arr)
	for i in range(N-1, -1, -1): # loop from N-1 to 0 (placing each 0th node to last, then heapifying again)
		# in heap sort we simply swap 0th index and last index N and decrement size of array and maxHeapify it again....
		# swap
		arr[0],arr[i] = arr[i],arr[0] # because 0th index had largest element, now placed it to end to sort the array
		maxHeapify(arr, i ,0) # i = 0 (maxheapify root node) and N = updated N (excluding recently sorted element), passing decremented size to maxHeapify so that it doesn't include already sorted node in the heap again

print("---Building Max Heap---")
arr = [6, 7, 13, 3, 8, 10]
buildMaxHeap(arr)
printHeap(arr)

# Max Heap:- 
#
#  	      13 
# 		 /  \
#   	8    10 
#      / \   /
# 	  3   7 6 



""" HeapSort, lets apply on max heap: so our max heap looks like this

	so after bulding max heap we have arr = [13, 8, 10, 3, 7, 6] now we just need to 
	sort this array in asc, so see max 13 is the max element of the arr, means in max heap
	max element is at the 0th index, so what we do in Heap sort is, we swap(arr, index=0, index=last)
	arr becomes = [6, 8, 10, 3, 7, 13], now last element is placed at its correct position
	-> but all other elements are disrupted, so we need to maxHeapify the root (index=0) remaining array except [6, 8, 10, 3, 7] | 13<- this is placed at corret position
	after building max heap becomes = [10, 8, 6, 3, 4] 13 see max element again at 0th index, place it at its correct position
	[4, 8, 6, 3] | 10 15, again apply maxheapify on root node......so on till the whole array is sorted
"""
print("---H E A P S O R T---")
heapSort(arr)
print(arr) # [3, 6, 7, 8, 10, 13]


print('-'*10)
print("---Building Min Heap---")
buildMinHeap(arr)
printHeap(arr)

# Min Heap:- 
# 		  3 
# 		/  \
# 	   7    6 
#    /	\   /
# 	8   13 10 






```