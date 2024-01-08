//Josh Bakelaar 251139121 7/16/2021
//ArrayStack.Java
//This class represents a Stack implemented with an array data structure. It must work for the generic type T and must implement StackADT<T>.
// the first element will be added to the end of the array and then new items will be added to the left of existing items.

public class ArrayStack<T> implements StackADT<T> {
	
	//Variables
	private T[] array;
	private int top; 
	
	//Constructor
	public ArrayStack(){
		top = 9;
		array = (T[])(new Object[10]);
	}
	
	//Constructor
	public ArrayStack (int initialCapacity) {
		top = initialCapacity-1;
		array = (T[])(new Object[initialCapacity]);
	}
	
	//Add item to stack
	public void push(T dataItem) {
		//If the stack is full, add 5 new spaces to the stack
		if (top-1 == 0) {
			T[] larger;
			larger = (T[])(new Object[array.length+5]);	
			
			for(int i = 0; i<array.length; i++) {
				larger[(larger.length-1)-i] = array[(array.length-1)-i];
			}

			array = larger;
			top=top+5;
		}
		
		//Add the element to the top (to the left of the top)
		array[top-1] = dataItem;
		
		//Update top
		top--;
	}
	
	//Takes the top item off
	public T pop() throws StackException{
		T element = null;
		//Throw a StackException if the stack is empty
		if(isEmpty()) {
			throw new StackException("Error, Stack is empty");
		}
		
		//Remove the element from the top
		element = array[top];
		array[top] = null;
		
		//Update Top
		top++;
		
		//Return element
		return element;
	}
		
	//Look at the top
	public T peek() throws StackException {
		//Throw a stack exception if the stack is empty
		if(isEmpty()) {
			throw new StackException("Error, Stack is empty");
		}
		
		//Return the top element without remove it
		return array[top];
	}
	
	//Is the stack empty?
	public boolean isEmpty() {
		int count = 0;
		
		//Counts the elements in the array
		for(int i = 0; i<array.length; i++) {
			if(array[i] != null) {
				count++;
			}
		}
		
		//If that count = 0 the stack is empty
		if(count == 0) {
			return true;
		}else {
			return false;
		}
	}
	
	//Return size
	public int size() {
		int count = 0;
		
		for(int i = 0; i<array.length; i++) {
			if(array[i] != null) {
				count++;
			}
		}
		
		return count;
	}
	
	//Return Length
	public int getLength() {
		return array.length;
	}
	
	public int getTop() {
		return top;
	}
	
	//To String
	public String toString() {
		//Default start of string
		String result = "Stack: ";
				
		//If its empty return "The stack is empty."
		if(isEmpty()) {
			result= "The stack is empty.";
			return result;
		}
		
		//For loop to go through the whole array
		for(int i = 0; i<array.length-1; i++) {
			//If its null just skip
			if(array[i] == null) {
				continue;
			}
			
			//Add onto the result
			if(i == array.length-2) {
				//If its the last item end with a .
				result = result + array[i].toString() + ".";
			}else {
				//If its not the last on add a , 
				result = result + array[i].toString() + ", ";
			}
		}
		
		return result;
	}
}
