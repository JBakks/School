//Josh Bakelaar (251139121) 6/20/2021
//Skyscraper.java
//This class is the other sub-class of Building. This one represents a Skyscraper building and it has a new instance variable to represent the height of the skyscraper. 
//The placement rules specific to this type is based on the height. The height must be less than 10 and it must be greater than or equal to the base area (width x length).

public class Skyscraper extends Building{
	
	//New Variable height 
	private int height;
	
	//Constructor takes in the same parameters as Building
	public Skyscraper(String symbol, int width, int length, int height) {
		super(symbol, width, length);
		this.height = height;
	}
	
	//checks to see if building placement is valid by taking into account previous rules, as well as the rules for Skyscrapers (height must be less then 10, height must be greater then or equal to the base area)
	public boolean isValidPlacement(Building[][] array, int x, int y) {
		//checks for previous building rules
		if(!super.isValidPlacement(array, x, y)) {
			return false;
		}
		
		//if height is greater then 9 return false
		if(height>=9) {
			return false;
		}
		
		//if height is smaller then the area (length*width) return false
		if(height<(super.getLength()*super.getWidth())) {
			return false;
		}
		
		//if other rules were passed the building placement is valid, so return true
		return true;
	}
	
	//Override the previous toString and put the height
	public String toString() {		
		return String.valueOf(height);
	}
}
