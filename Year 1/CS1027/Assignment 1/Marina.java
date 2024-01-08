//Josh Bakelaar (251139121) 6/20/2021
//Marina.java
//This class is one of the sub-classes of Building, so it must be declared as such at the top. 
//This one is a Marina, so it must be adjacent to "water", meaning at least one cell of this structure must be along the edge of the city.

public class Marina extends Building {
	
	//Constructor takes in the same parameters as Building
	public Marina(String symbol, int width, int length) {
		super(symbol, width, length);
	}
	
	//checks to see if building placement is valid by taking into account previous rules, as well as the one for a Marina (must be touching the edge of the city)
	public boolean isValidPlacement(Building[][] array, int x, int y) {
		//checks previous rules
		if(!super.isValidPlacement(array, x, y)) {
			return false;
		}
		
		//if its on the edge of the map return true otherwise return false
		if(x == 0 || x+super.getWidth() == array.length || y == 0 || y+super.getLength() == array[0].length) {
			return true;
		}else {
			return false;
		}
	}
}
