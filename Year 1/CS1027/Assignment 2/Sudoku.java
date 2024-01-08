//Josh Bakelaar (251139121) 6/30/2021
//Sudoku.java
//This class represents the Sudoku as an array of linked data structures. 
//This is also where we will be checking the validity of the Sudoku.

public class Sudoku {
	//Variables.
	LinearNode<Integer>[] board;
	
	//Constructor.
	public Sudoku(int array[][]) {
		//Initialize the board with 9 slots.
		board = new LinearNode[9];
		
		//Loop through the 9 slots and initialize them with the values from column 1.
		for(int i=0; i<array.length; i++) {	
			LinearNode elem = new LinearNode(array[i][0]);
			board[i] = elem;
		}
		
		//Insert the rest of the nodes in their respective places.
		for(int i=0; i<array.length; i++) {
			for(int j=1; j<array.length; j++) {		
				//Holds the element were wanting to place.
				LinearNode elem = new LinearNode(array[i][j]);
				//Represents the last node visited.
				LinearNode last = board[i];
				
				//Loop through each one until the next is null.
				while(last.getNext() != null) {
					last = last.getNext();
				}
				//Place the next node there.
				last.setNext(elem);
			}
		}
	}
	
	//Checks the row to make sure it is valid (numbers 1-9 in row, no duplicates)
	public boolean isValidRow(int row) {
		UniqueArray array = new UniqueArray();
		LinearNode last = board[row-1];
		//String to check if there are duplicates/ if there is a 0/ if the length of the string is>9 that means there is at least 1 element with 2 digits.
		String test = "";
		
		//Add the first node
		array.addItem(board[row-1]);
		
		//Loop through row and add the rest of the nodes.
		while(last.getNext() != null) {
			last = last.getNext();
			array.addItem(last);
			test = test + last.getElement();
		}
		
		//Makes sure there are no duplicates in the string
		for (int i=0; i<test.length(); i++) {
			for (int j =i+1; j<test.length(); j++) {
				if (test.charAt(i) == test.charAt(j)) {
					return false;
				}
			}
		}
		
		//If the string contains a 0 return false.
		if(test.contains("0")) {
			return false;
		}
		//If the length is greater then 9 characters return false.
		if(test.length()>9) {
			return false;
		}
		//If the number of elements is 9 return true, else return false.
		if(array.getNumElements() == 9) {
			return true;
		}else {
			return false;
		}
	}
	
	//Checks the column to make sure it is valid (numbers 1-9 in column, no duplicates)
	public boolean isValidCol(int col) {
		UniqueArray array = new UniqueArray();
		//String to check if there are duplicates/ if there is a 0/ if the length of the string is>9 that means there is at least 1 element with 2 digits.
		String test = "";
		
		//Loops through board and grabs the nodes in the specific column
		for(int i=0; i<board.length; i++) {
			LinearNode last = board[i];
			for(int j=0; j<(col-1); j++) {
				last = last.getNext();
			}
			array.addItem(last);
			test = test + last.getElement();
		}
		
		//Makes sure there are no duplicates in the string
		for (int i=0; i<test.length(); i++) {
			for (int j=i+1; j<test.length(); j++) {
				if (test.charAt(i) == test.charAt(j)) {
					return false;
				}
			}
		}
		
		//If the string contains a 0 return false.
		if(test.contains("0")) {
			return false;
		}
		//If the length is greater then 9 characters return false.
		if(test.length()>9) {
			return false;
		}
		
		//If the number of elements is 9 return true, else return false.
		if(array.getNumElements() == 9) {
			return true;
		}else {
			return false;
		}
	}
	
	//Take in two numbers representing the row and col indices in which the 3x3 box begins. These numbers must be from 1 to 7.
	public boolean isValidBox(int row, int col) {
		UniqueArray array = new UniqueArray();
		
		//String to check if there are duplicates/ if there is a 0/ if the length of the string is>9 that means there is at least 1 element with 2 digits.
		String test = "";
		
		//If the row is less then 1 or greater then 7 return false
		if(row<1 || row>7) {
			return false;
		}
		
		//If the col is less then 1 or greater then 7 return false.
		if(col<1 || col>7) {
			return false;
		}
		
		//Go to the row where the square starts
		for(int i=row-1; i<row+2; i++) {
			//head is equal to where the row starts
			LinearNode last = board[i];
			
			//Skip to the correct column
			for(int j=0; j<col-1; j++) {
				last = last.getNext();
			}
			//Add the elements in the columns of the row
			for(int j=0; j<3; j++) {
				array.addItem(last);
				test = test + last.getElement();
				last = last.getNext();
			}
		}
		
		//Makes sure there are no duplicates in the string
		for (int i=0; i<test.length(); i++) {
			for (int j=i+1; j<test.length(); j++) {
				if (test.charAt(i) == test.charAt(j)) {
					return false;
				}
			}
		}
		
		//If the string contains a 0 return false.
		if(test.contains("0")) {
			return false;
		}
		
		//If the length is greater then 9 characters return false.
		if(test.length()>9) {
			return false;
		}
		
		//If the number of elements is 9 return true, else return false.
		if(array.getNumElements() == 9) {
			return true;
		}else {
			return false;
		}
	}
	
	//Checks to see if the Sudoku is valid.
	public boolean isValidSolution() {
		//Go through each row and column.
		for(int i = 1; i<=board.length; i++) {
			if(!isValidRow(i)) {
				return false;
			}
			
			if(!isValidCol(i)) {
				return false;
			}
		}
		
		//Go through each cell where a box is valid.
		if(!isValidBox(1,1)) {
			return false;
		}
		if(!isValidBox(1,4)) {
			return false;
		}
		if(!isValidBox(1,7)) {
			return false;
		}
		if(!isValidBox(4,1)) {
			return false;
		}
		if(!isValidBox(4,4)) {
			return false;
		}
		if(!isValidBox(4,7)) {
			return false;
		}
		if(!isValidBox(7,1)) {
			return false;
		}
		if(!isValidBox(7,4)) {
			return false;
		}
		if(!isValidBox(7,7)) {
			return false;
		}
		
		//If all tests pass then it is valid.
		return true;
	}
	
	//Loop through the Sudoku structure and build a string with all the values in a wellformatted grid.
	public String toString() {
		String result = "";
		
		for(int j=0; j<board.length; j++) {
			LinearNode last = board[j];
			if(j == 0) {
				//Add 2 spaces after each cell
				result = result +board[j].getElement() + "  ";
			}else {
				result = result + "\n" +board[j].getElement() + "  ";
			}
			for(int i=0; i<board.length; i++) {
				while(last.getNext() != null) {
					last = last.getNext();
					//If its the last node in the row it means there is no spaces
					if(last.getNext() == null) {
						result = result + last.getElement();
					}else {
						result = result + last.getElement() + "  ";
					}
				}
			}
		}
		
		//Return result.
		return result;
	}
}
