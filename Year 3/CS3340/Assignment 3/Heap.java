// Josh Bakelaar
// 251139121
// 4/4/2023

import java.util.Arrays;
import java.util.*;

// Initializes a heap with the array keys of n elements
public class Heap {
    // Array of keys
    int[] heap;
    // Stores ids to their corresponding key
    int[] idToIndex;
    // How many elements
    int size;
    
    public Heap(int[] keys, int n){
        heap = Arrays.copyOf(keys, n);
        idToIndex = new int[n];
        for(int i = 0; i < n; i++){
            idToIndex[i] = i;
        }
        size = n;
        for (int i = n/2 - 1; i >= 0; i--){
            heapifyDown(i);
        }
    }

    // Returns true if the element with id is in the heap
    public boolean in_heap(int id){
        if((id >= 0) && (id < size) && (idToIndex[id] < size) && (idToIndex[id] >= 0) && (heap[idToIndex[id]] == id)) {
            return true;
        }
        return false;
    }

    // Returns true if the heap is empty
    public boolean is_empty(){
        return size == 0;
    }

    // Returns the id of the element with minimum key in the heap
    public int min_key(){
        return heap[0];
    }

    // Returns the id of the element with minimum key in the heap
    public int min_id(){
        for(int i = 0; i < size; i++){
            if(heap[i] == heap[0]){
                return i;
            }
        }
        return -1;
    }
    // Returns the ky of the element with id in the heap
    public int key(int id){
        return heap[idToIndex[id]];
    }

    // Deletes the element with minimum key form the heap
    public int delete_min(){
        int toDelete = heap[0];
        heap[0] = heap[size-1];
        idToIndex[0] = idToIndex[size - 1];
        idToIndex[idToIndex[size - 1]] = 0;
        heap[size - 1] = Integer.MIN_VALUE;
        size--;
        heapifyDown(0);
        return toDelete;
    }

    // sets the key of the element with id to new_key if its current key is greater than new_key
    public void decrease_key(int id, int new_key){
        int i = idToIndex[id];
        heap[i] = new_key;
        heapifyUp(i);

    }

    private void heapifyUp(int i){
        int parent = (i - 1)/2;
        while(i > 0 && heap[i] < heap[parent]) {
            swap(i, parent);
            i = parent;
            parent = (i - 1)/2;
        }
    }

    private void heapifyDown(int i){
        int leftIndex = 2*i + 1;
        int rightIndex = 2*i + 2;
        int smallestIndex = i;

        if(leftIndex < size && heap[leftIndex] < heap[smallestIndex]){
            smallestIndex = leftIndex;
        }
        if(rightIndex < size && heap[rightIndex] < heap[smallestIndex]){
            smallestIndex = rightIndex;
        }
        if(smallestIndex != i){
            swap(i, smallestIndex);
            heapifyDown(smallestIndex);
        }
    }
    private void swap(int i, int j){
        int temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        temp = idToIndex[i];
        idToIndex[i] = idToIndex[j];
        idToIndex[j] = temp;
    }   
}