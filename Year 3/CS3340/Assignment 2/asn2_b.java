import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

import javax.imageio.stream.ImageInputStreamImpl;

public class asn2_b{
    
    public static void main(String[] args){
        
        // Initialize variables
        int[][] image = null;
        boolean[][] flag = null;

        int rows = 72;
        int cols = 75;
        
        // Load the image
        try {
            // Get the file from input
            String filename = "girl.img.txt";
            BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
            
            // Set up image and flag arrays
            image = new int[rows][cols];
            flag = new boolean[rows][cols];
            
            String string;
            
            // Read through each line; for each + image to 1 and flag to true
            for(int i = 0; input.ready(); i++){
                string = input.readLine();
                for(int j = 0; j < string.length(); j++){
                    if(string.charAt(j) == '+'){
                        image[i][j] = 1;
                        flag[i][j] = true;
                    }
                }
            }
            
            // Close the buffer
            input.close();
        }
        
        // Catch FileNotFound exception
        catch (FileNotFoundException e){
            System.out.println("File Not Found");
        }
        
        // Catch IO Exception
        catch (IOException e){
            System.out.println("Can't Read File.");
        }
        
        // Print out part 1
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                System.out.print(image[i][j]);
            }
            System.out.println();
        }
        System.out.println();

        // Part 2
        char[][] connectedComp = new char[rows][cols];

        int next = 0;

        uandf ds = new uandf(rows*cols);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(image[i][j] == 1){
                    // left
                    if (j > 0 && image[i][j-1] == 1) {
                        ds.union_sets(i * cols + j, i * cols + (j-1));
                    }
                    // right
                    if (j < cols-1 && image[i][j+1] == 1) {
                        ds.union_sets(i * cols + j, i * cols + (j+1));
                    }
                    // down
                    if (i > 0 && image[i-1][j] == 1){
                        ds.union_sets(i * cols + j, (i-1) * cols + j);
                    }
                    // up
                    if (i > rows-1 && image[i+1][j] == 1){
                        ds.union_sets(i * cols + j, (i+1) * cols + j);
                    }
                    // up-left
                    if (i > 0 && j > 0 && j < cols-1 && i < rows-1 &&  image[i+1][j-1] == 1) {
                        ds.union_sets(i * cols + j, (i+1) * cols + (j-1));
                    }
                    // up-right
                    if (i > 0 && j > 0 && j < cols-1 && i < rows-1 &&  image[i+1][j+1] == 1) {
                        ds.union_sets(i * cols + j, (i+1) * cols + (j+1));
                    }
                    // down-left
                    if (i > 0 && j > 0 && j < cols-1 && i < rows-1 && image[i-1][j-1] == 1){
                        ds.union_sets(i * cols + j, (i-1) * cols + (j-1));
                    }
                    // up-left
                    if (i > 0 && j > 0 && j < cols-1 && i < rows-1 &&  image[i+1][j-1] == 1){
                        ds.union_sets(i * cols + j, (i+1) * cols + (j-1));
                    }
 
                    int root = ds.find_set(i * cols + j);
                    int rootRow = root / cols;
                    int rootCol = root % cols;
                    
                    if(connectedComp[rootRow][rootCol] == 0){
                        connectedComp[rootRow][rootCol] = (char)('A'+ next);
                        next++;
                    }
        
                    connectedComp[i][j] = connectedComp[rootRow][rootCol];
                }else{
                    connectedComp[i][j] = (char)(' ');
                }

            }
        }
        
        // print part 2
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                System.out.print(connectedComp[i][j]);
            }
            System.out.println();
        }
        System.out.println();

        // print part 4
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(ds.find_set(i) > 1){
                    System.out.print(connectedComp[i][j]);
                }
            }
            System.out.println();
        }
        System.out.println();
        
        // print part 5
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(ds.find_set(i) > 11){
                    System.out.print(connectedComp[i][j]);
                }
            }
            System.out.println();
        }
        System.out.println();
    }
}