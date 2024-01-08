//Josh Bakelaar 251139121 7/16/2021
//StartSearch.java
//This class is the main heart of the program in which we are writing the algorithm that performs a search on a given map file. 
//This program must use an ArrayStack to keep track of the MapCells that have been visited or attempted to be visited.

import java.io.FileNotFoundException;
import java.io.IOException;

public class StartSearch {
	//Variables
	private Map map;
	
	int energy = 10;
	
	//Constructor
	public StartSearch(String fileName) throws InvalidMapException, FileNotFoundException, IOException {
		map = new Map(fileName);
	}
	
	//Determines the best (unmarked) cell from the current cell to continue the path
	public MapCell bestCell(MapCell current) {
		boolean covid = false;
		//Loops through 4 directions if one of them is Covid return false
		for(int i = 0; i <= 4; i++) {
			try{	
				if(current.getNeighbour(i).isCovid()) {
					return null;
				}
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
		}
		
		//i represents the direction of the cell 0 = north, 1 = east, 2 = south, 3 = west
		for(int i = 0; i <= 4; i++) {
			//If its marked skip the cell and exists
			try {
				if(current.getNeighbour(i).isMarked()) {
					continue;
				}
				
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
			
			//If its the exit prioritize it
			try {
				if(current.getNeighbour(i).isExit()) {
					return current.getNeighbour(i);
				}
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
		}
		
		//Next priority is the doughnut
		for(int i = 0; i <= 4; i++) {
			//If its marked skip the cell and exists
			try {
				if(current.getNeighbour(i).isMarked()) {
					continue;
				}
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
			
			try {
				if(current.getNeighbour(i).isDonut()) {
					return current.getNeighbour(i);
				}
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
		}
		
		//Next priority is the cross path
		for(int i = 0; i <= 4; i++) {
			//If its marked skip the cell and exists
			try {
				if(current.getNeighbour(i).isMarked()) {
					continue;
				}	
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
			
			try {
				//if its coming from a cross path or doughnut and it is a cross path its good
				if(current.getNeighbour(i).isCrossPath()) {
					if(current.isCrossPath() || current.isStart() || current.isDonut()) {
						if(current.getNeighbour(i).isCrossPath()) {
							return current.getNeighbour(i);
						}
					}
					//if the current is a horizontal and were going the correct direction
					if(current.isHorizontalPath() && (i == 1 || i == 3)) {
						if(current.getNeighbour(i).isCrossPath()) {
							return current.getNeighbour(i);
						}
					}
					//if the current is a vertical and were going the correct direction
					if(current.isVerticalPath() && (i == 0 || i == 2)) {
						if(current.getNeighbour(i).isCrossPath()) {
							return current.getNeighbour(i);
						}
					}
				}
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
		}
		
		//Next priority is the horizontal and vertical paths
		for(int i = 0; i<=4; i++) {
			//If its marked skip the cell and exists
			try {
				if(current.getNeighbour(i).isMarked()) {
					continue;
				}
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
			
			try {
				//if its a cross it can go to either as long as were heading the right direction
				if(current.isCrossPath()) {
					if(current.getNeighbour(i).isHorizontalPath() && (i == 1 || i == 3)) {
						return current.getNeighbour(i);
					}
					
					if(current.getNeighbour(i).isVerticalPath() && ( i == 0 || i == 2)) {
						return current.getNeighbour(i);
					}
					continue;
				}
				
				//if its horizontal and were heading the right directions
				if(current.getNeighbour(i).isHorizontalPath() && (i == 1 || i == 3)) {
					return current.getNeighbour(i);
				}
				
				//if its vertical and were heading the right directions
				if(current.getNeighbour(i).isVerticalPath() && ( i == 0 || i == 2)) {
					return current.getNeighbour(i);
				}	
			}catch(Exception InvalidNeighbourIndexException) {
				continue;
			}
		}
		
		return null;
	}
	
	//Finds the correct path
	public String findPath() {
		//Creates a new stack
		ArrayStack stack = new ArrayStack();
		//String to add actions into
		String actionString = "";
		//Status flag to indicate if the destination has been reached
		boolean found = false;
		//Int for energy
		int energy = 10;
		
		//Push the start of the map onto the stack
		stack.push(map.getStart());
		//Mark the start in stack
		map.getStart().markInStack();
		//add the start into the action string
		actionString = actionString + map.getStart() + "-";
		
		//While the stack is not empty and the destination has not been reached, perform the following steps
		while(!stack.isEmpty() && !found) {
			//Peek at the top of the stack to get the current cell.
			MapCell current = (MapCell) stack.peek();
			//Find the next unmarked neighbouring cell 
			MapCell next = (MapCell) bestCell(current);
			
			//Update the actionString to contain the cell being visited.
			if(next != null && !next.isExit() && energy>0) {
				actionString = actionString + next + "-";
			}
			
			//If such a next cell exists and the energy level is above 0
			if(energy>0 && next != null) {
				//Check if the next cell is the destination. If so, set the status flag to true
				if(next.isExit()) {
					found = true;
				}
				//Check if the next cell is a donut cell. If so, increase the energy level by 3
				if(next.isDonut()) {
					energy = energy+3;
				}
				
				//Push the neighbouring cell into the stack and mark it as inStack
				stack.push(next);
				next.markInStack();
				//Decrease the energy level by 1 because of this single movement
				energy--;
				
			//Otherwise, since there are no unmarked neighbouring cells that can be added to the path	
			}else {
				//Pop the top cell from the stack and mark it as out of stack
				current.markOutStack();
				stack.pop();
				
				//Update the actionString
				if(!stack.isEmpty()) {
					actionString = actionString + stack.peek() + "-";
				}
				
				//If that top cell is a donut cell, decrease the energy level by 3 (because we are undoing a donut consumption).
				if(current.isDonut()) {
					energy = energy-3;
				}
				
				//If that top cell is anything other than the start point, increase the energy level by 1
				if(!current.isStart()) {
					energy = energy + 1;
				}
			}
		}
		
		//While the stack is not empty
		while(!stack.isEmpty()) {
			//Pop the top cell from the stack and mark it as out of stack
			MapCell old = (MapCell) stack.pop();
			old.markOutStack();
		}
		
		actionString = actionString + "E" + energy;
		return actionString;
	}
	
	//This is the method that starts the program. See the Command Line Arguments section of Assignment instructions for which arguments to throw
	static void main(String[] args) throws InvalidMapException, FileNotFoundException, IOException {
		if (args.length < 1) {
			System.out.println("You must provide the name of the input file");
		}
		
		String mapFile = args[0];
		StartSearch ss = new StartSearch(mapFile);
		
	}
}
