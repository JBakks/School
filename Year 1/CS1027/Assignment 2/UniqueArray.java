//Josh Bakelaar (251139121) 6/29/2021
//UniqueArray.java
//This class is a collection which is a regular array but with the requirement that duplicate elements are not allowed. 
//This means, when attempting to add a new item, you must check if that element already exists in the array and only add the item if it does not exist there already.

public class UniqueArray<T> {
	
	//Variables.
	private T[] array;
	private int num;
	
	//Constructor.
	public UniqueArray() {
		//Initialize the array with 5 slots.
		array = (T[])new Object[5];
		
		//Set num to 0.
		num = 0;
	}
	
	//Increase the capacity by 5 additional slots.
	private void expandCapacity() {
		//Temporary array with an additional 5 slots.
		T[] temp;
		temp = (T[])(new Object[array.length+5]);
		
		//Loop through the array and assign the objects in the old array with the new bigger one.
		for(int i=0; i<array.length; i++) {
			temp[i] = array[i];
		}
		
		//array now equals the bigger one
		array = temp;
	}
	
	public void addItem(T element) {
		//Boolean to see if item is already in the array.
		boolean check = false;
		
		//Checks every element in array, if its already there check = true.
		for(int i=0; i<array.length; i++) {
			if(array[i] == element) {
				check = true;
			}
		}
		
		//If the item was not found add it.
		if(!check) {
			//If the last element = null that means there is still room in the array.
			if(array[array.length-1] == null) {
				//Loop through the array, the first element that returns null is where the item will be placed.
				for(int i = 0; i < array.length; i++) {
					if(array[i] == null) {
						array[i] = element;
						//Break so it doesn't keep looping and adding the element.
						break;
					}
				}
			//If the last element is not null then the capacity needs to be expanded.
			}else {
				//Call expandCapacity
				expandCapacity();
				//Loop through the array and find the first element that returns null, this is where the element will be placed
				for(int i=0; i<array.length; i++) {
					if(array[i] == null) {
						array[i] = element;
						//Break so it doesn't keep looping and adding the element.
						break;
					}
				}
			}
			//Finally increment num.
			num++;
		}
	}
	
	//Returns length.
	public int getLength() {
		return array.length;
	}
	
	//Returns number of elements.
	public int getNumElements() {
		return num;
	}
	
	//Returns a string containing each element
	public String toString() {
		//String to return, and add onto.
		String elements = "";
		
		//Loop through the array and add each element there is.
		for(int i=0; i<array.length; i++) {
			//If the current cell = null that means we are at the end of the elements added.
			if(array[i] == null) {
				//Break out of the loop so we don't add "null".
				break;
			}
			//If i = num-1 (the last element) dont add a ", ".
			if(i==num-1) {
				elements = elements + array[i];
			}else {
				//Add the new element to existing with a ", ".
				elements = elements + array[i] + ", ";
			}
		}
		
		//Finally return the string.
		return elements;
	}
	
}
