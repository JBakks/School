//Josh Bakelaar (251139121) 6/20/2021
//Building.java
//This class represents a building structure to be placed within the city.
//Rules for a building being created are that the structure cannot be off the island, and they cannot be overlapping with another building.

public class Building {
	//Variables
	private String symbol;
	private int width;
	private int length;
	
	//Constructor
	public Building(String symbol, int width, int length) {
		this.symbol = symbol;
		this.width = width;
		this.length = length;
	}
	
	//returns the width of the building
	public int getWidth() {
		return width;
	}
	
	//returns the length of the building
	public int getLength() {
		return length;
	}
	
	//takes in a 2D Building array and the x & y positions of the building trying to be built
	public boolean isValidPlacement(Building[][] array, int x, int y) {
		//Rule 1: the building has to be on the island
		//if the x+width is greater or smaller than the size of the island return false
		for(int i=0; i<=width; i++) {
			if((x+i)>array.length || (x+i)<0) {
				return false;
			}
		}
		//if the y is greater or smaller than the size of the island return false
		for(int i=0; i<length; i++) {
			if((y+i)>array[0].length-1 || (y+i)<0) {
				return false;
			}
		}
		
		//Rule 2: buildings cannot be overlapping with other buildings
		//if a building trying to be placed is overlapping with another building return false
		//Checks the x
		for(int i=0; i<width; i++) {
			if(array[(x+i)][y] != null) {
				return false;
			}	
		}
		//Checks the y
		for(int i=0; i<length; i++) {
			if(array[x][(y+i)] != null) {
				return false;
			}	
		}
		
		//if it passes previous rules that building is allowed to be placed 
		return true;
	}
	
	//returns the symbol of the building
	public String toString() {
		return symbol;
	}
}