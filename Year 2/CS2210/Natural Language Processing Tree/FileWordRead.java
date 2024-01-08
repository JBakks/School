import java.util.Iterator;
import java.util.Scanner;
import java.io.*;
 
public class FileWordRead {
	

/**
 * 
 * @param abc
 */
public FileWordRead(String abc) {
		// TODO Auto-generated constructor stub
	}

/**
 * 
 * @return
 * @throws FileNotFoundException
 */
//getter
public Iterator<String> get_iterator() throws FileNotFoundException{
	
	 File file;
	 file = new File("words.txt");
	 Scanner in;
	 in = new Scanner(file); 

	 return in;
	
	}


@SuppressWarnings("resource")
/**
 * 
 * @param args
 * @throws IOException
 */
public static void main(String[] args) throws IOException {
 
    File file;
    file = new File("words.txt");
    Scanner input;
    input = new Scanner(file); 
 
    int count = 0;
    while (input.hasNext()) {
      String word  = input.next();
      System.out.println(word);
      count = count + 1;
    }
    System.out.println("Word count: " + count);
  }


}


