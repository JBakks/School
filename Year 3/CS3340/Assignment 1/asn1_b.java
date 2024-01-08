/*  
 *  Josh Bakelaar (251139121)
 *  2/2/2023
 *  asn1b.java 
 *  A recursive function to compute Nn with time complexity O(n) using primitive types to store big number
 */

public class asn1_b {
    // Declare constant size for arrays to store fibonacci values
    public static final int SIZE = 500;

    public static int[] fib(double n){  
        // Initialize an array to store the fibonacci value for the given number n
        int[] value = new int[SIZE];

        // Initialize two arrays to store the fibonacci values of n-1 and n-2
        int[] nMinusOne = new int[SIZE];
        addOne(nMinusOne);
        
        int[] nMinusTwo = new int[SIZE];

        // Check if n is 0, 1, or greater than 1
        if(n == 0){
            value = new int[SIZE]; // If n is 0, return an array of zeros
        }else if(n == 1){
            // If n is 1, no need to do anything because nMinusOne was already initialized with a value of 1
        }else{
            // If n is greater than 1, loop from 2 to n to calculate the fibonacci values
            for(int i = 2; i <= n; i++){
                value = addLarge(nMinusOne, nMinusTwo);
                nMinusTwo = nMinusOne;
                nMinusOne = value;
            }
        }
        // Return the fibonacci value for n
        return value;
    }

    // Method to add two large numbers stored in arrays
    public static int[] addLarge(int[] x, int[] y){
        int[] sum = new int[SIZE];
        boolean carry = false;

        // Loop through each digit of the arrays, starting from the rightmost digit
        for(int i = SIZE; i > 0; i--){
            int index = 0;

            // Check if a carry value needs to be taken into consideration
            if(carry){
                index = 1;
                carry = false;
            }

            // Add the digits at the same position in both arrays
            index += x[i-1] + y[i-1];

            // Check if a carry value needs to be set for the next digit
            if(index > 9){
                carry = true;
            }

            // Set the current digit of the sum as the units digit of the result of the addition
            sum[i-1] = index % 10;
        }

        // Return the sum of the two large numbers
        return sum;
    }

    // Method to increment the value of an array by 1
    public static void addOne(int[] num){
        num[SIZE-1] = 1;
    }

    // Method to print the digits of a large number stored in an array
    public static void print(int[] num){
        boolean removeZero = true;

        // Loop through the array, starting from the leftmost digit
        for(int i = 0; i < SIZE; i++){
            // Skip any leading zeros in the number
            while(removeZero){
                if(i < SIZE && num[i] == 0){
                    i++;
                }else{
                    removeZero = false;
                }
            }

            // Print the current digit of the number
            if(i < SIZE){
                System.out.print(num[i]);
            }else{
                System.out.print("0");
            }
        }
        // Print a new line
        System.out.println();
    }
    /*
     * Main Method. calcuates and printf F(0) - F(500) prints every 20 numbers
     */
    public static void main(String[] args)
    {
        for(int i = 0; i <= 25; i++)
        {
            System.out.print("F(" + i*20 + ") = ");
            print(fib(i*20));
        }
    }
    
}
