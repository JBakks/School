//Josh Bakelaar
//251139121
//3/31/2022
//calculateNr.java

import java.io.FileNotFoundException;
import java.util.*;

public class calculateNr {

	//method to help with duplicates
	public static void duplicate(int numbers[]) {
		boolean duplicate = false;
		int count = 0;

		for (int z = 0; z < numbers.length; z++) {
			while (z > count){
				if (numbers[z] == numbers[count] && (z != count)) {
						duplicate = true;
				}
				count++;
			}

			if (duplicate == true) {
				System.out.print(numbers[z] + "  ");
			}
		}
	}

	public static void main(String[] args) throws FileNotFoundException {
	
		int temp = 0, temp2 = 0, max = 0, i;
		
		//Create trees
		AVLTree tree;
		tree = new AVLTree();

		AVLTree tree2;
		tree2 = new AVLTree();
		
		//Read the words in the file
		FileWordRead words;
		words = new FileWordRead("words.txt");
		
		//iterate through words
		Iterator<String> iter;
		iter = words.get_iterator();
		
		//create a hashmap
		HashMap<String, Integer> grid;
		grid = new HashMap<>();
			
		//checks if aything is left
		while (iter.hasNext() == true) {
		
			//get next item
			String str;
			str = iter.next(); 

			//remove puncuation, and special characters
			str = str.replaceAll(" [^&,()*.?!@#$%_+-]+", "");
				
			//get a key for the hashtable
			if(grid.containsKey(str) != true) {
				temp = 1;
				grid.put(str, temp);
				if (str.length() >= max + 1) { 
					max = str.length();}
				}else {
					temp = grid.get(str)+1; grid.put(str,temp);
				}

		}
		TreeMap<String, Integer> treemap = new TreeMap<>();
		
		int A[] = new int[treemap.size()];

		//put the hashtable in the tree
		treemap.putAll(grid);

		int x = treemap.size();
		boolean v[] = new boolean[x];
		Arrays.fill(v, false);
		
		//Insert words into the tree
		for (Map.Entry<String, Integer> e: treemap.entrySet()) {
			if(temp == 0) {
				System.out.println("word is not in file");
			}else {
				tree.Insert(e.getValue());
					
				for(i = 0; i <= treemap.size() + 1; ++i) {
					if(i == e.getValue()) {
						A[temp2++] = i;
					}else {
						return;
					}
				}
			}
		}
		
		//traversing through elements in the array and counting frequencies
		for (i = 0; i < x; i++) {
			
			//counting frequency
			if (v[i] != true) {
				int count;
				count = 1;
				for (int z = i + 1; z < x; z++) {
					if (A[i] == A[z]) {
						v[z] = true; 
						count++;
					}
				}
				
				System.out.println("(" + A[i] + ", " + count + " ) ");
				
				tree.Insert(count);
			}
			
			//if already processed, skip the element
			else {
				continue;
			}
		}
	}
}


