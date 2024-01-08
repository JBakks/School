//Josh Bakelaar (251139121) 6/20/2021
//City.java
//This class represents the new city that is being developed

public class City {
	//Variables
	private int width;
	private int length;
	private Building[][] layout;
	
	//Constructor
	public City(int x, int y) {
		width = x;
		length = y;
		
		//Initializes the layout 2D array using length and width as the array sizes
		layout = new Building[width][length];
	}
	
	//Takes in x and y position values and a Building object that we are attempting to add to the city at the given (x, y) position.
	public boolean addStructure(int x, int y, Building building) {
		//Call the isValidPlacement() method on the given Building object
		if(!building.isValidPlacement(layout, x, y)) {
			//If its not valid return false
			return false;
		}else {
			//Add the Building object to that location so loop through ALL the cells in which the Building will be constructed
			for(int i = 0; i<building.getLength(); i++) {
				for(int j = 0; j<building.getWidth(); j++)
				layout[x+j][y+i] = building;
			}
		}
		//Finally return true if it was allowed to be placed
		return true;
	}
	
	//Loop through the layout 2D array and construct a string with all the values in a well-formatted grid
	public String toString() {
		//creates an empty string which we can add each cell of the map too
		String map = "";
		for(int i = 0; i<length; i++) {
			for(int j = 0; j<width; j++) {
				//Any cells that do not contain a Building object should be shown with a period (.)
				if(layout[j][i] == null) {
					map = map + "." + "  ";
				}else {
					//the ones that do contain a Building should be shown with that Buildings symbol
					map = map + layout[j][i].toString() + "  ";
				}	
			}
			//add a newline character at the end of each line (except the last one) so that the string is formatted like a grid
			if(i != length-1) {
				map = map + "\n";
			}
		}
		//Finally return the map
		return map;
	}	
}
