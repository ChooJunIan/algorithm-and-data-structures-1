#include <iostream>
#include <vector>

// Priority Queue ADT using a max heap
template <typename T>
class PriorityQueue {
	private:
	std::vector<T> listHeap; // the max heap implemented using a vector (dynamic array)

	// Member function called by enqueue operation.
	// Iteratively adjust or 'heapify' the last node up the heap until the max-heap property is 
	// satisfied
	void heapifyUp() {
		int index = listHeap.size() - 1; // start with the last node (rightmost leaf node)

		// while the current node is not the root ...
		while (index > 0) { 
			int parentIndex = (index - 1) / 2; // get the parent of the current node
			
			// if the parent node value is less than the child node value (max-heap not satisfied)
			if (listHeap[parentIndex] < listHeap[index]) {
				std::swap(listHeap[parentIndex], listHeap[index]); // swap the two nodes, moves  
														   		   // the current node up the heap
				index = parentIndex; // update the current node position to be the swapped parent 
									 // node (i.e the next node to check)
			}
			else {
				// otherwise the max-heap property is satisfied, stop heapifying up
				break;
			}
		}
	}

	// Member function called by dequeue operation
	// iteratively adjust or 'heapify' the root node down the heap until the max-heap property is 
	// satisfied
	void heapifyDown() {
		int index = 0; // start with the root
	
		// while the current node is a parent (internal) node...
		while (index < listHeap.size() / 2) { 
			// get the index of the left and right children 
			int leftChildIndex = 2 * index + 1;
			int rightChildIndex = 2 * index + 2;

			// get the index of the largest value node between the current node and it's 
			// child/children
			int maxIndex = index;
			if (listHeap[maxIndex] < listHeap[leftChildIndex])
         		maxIndex = leftChildIndex;
			if (rightChildIndex < listHeap.size() && 
				listHeap[maxIndex] < listHeap[rightChildIndex])
				maxIndex = rightChildIndex;

			// if the current node value is not the largest (max-heap not satisfied)
			if (index != maxIndex) {
				std::swap(listHeap[index], listHeap[maxIndex]); // swap the two nodes, moves the 
																// current node down the heap
				index = maxIndex; // update the current node position to be the swapped child node 
								  // (i.e the next node to check)
			}
			else {
				// otherwise the max-heap property is satisfied, stop heapifying down
				break;
			}
		}
	}
	
	public:

	// constructors
	PriorityQueue() {
	}

	PriorityQueue(int initialCapacity) {
		listHeap.reserve(initialCapacity);
	}

	// The following member functions define the priority queue operations

	// Member function for enqueuing an element.
	// Takes the element object as input, adds it to the heap and moves it up to an appropriate 
	// position
	void enqueue(T element) {
		listHeap.push_back(element); // add new element at bottom leftmost position (end of list)
		heapifyUp(); // move this (last) element up the heap
	}
  
	// Member function for dequeuing an element
	// Returns and removes the element at the top (root) of the heap. Readjusts the heap 
	// appropriately.
	T dequeue() {
		T removed_element = listHeap[0]; // save the element in the root (first in list)
		listHeap[0] = listHeap[listHeap.size() - 1]; // copy last element to root
		listHeap.pop_back(); // remove last element
		heapifyDown(); // move this (root) element down the heap
		return removed_element; // finally return the initially removed element
	}

	// Member function to return the size of the priority queue (i.e. the heap size)
	int size() {
		return listHeap.size();
	}

	// Member function to clear the priority queue
	void clear() {
		listHeap.clear();
	}

	// Member function to print the entire priority queue
	void print() {
		for (int i = 0; i < listHeap.size(); i++)
			std::cout << "[" << i << "] : " << listHeap[i] << std::endl;
		std::cout << std::endl;
	}  
};