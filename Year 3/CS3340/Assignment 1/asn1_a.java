/*  
 *  Josh Bakelaar (251139121)
 *  2/2/2023
 *  asn1a.java 
 *  a recursive way to calculate an nth number in the fibonacci sequence.
 */

public class asn1_a {
    
    /*
     * Calculates and returns the nth number in the Fibonacci sequence.
     */
    public static long fib(int n) {
        // if n is 0, return 0
        if (n == 0) {
            return 0;
        } 
        // if n is 1, return 1
        else if (n == 1) {
            return 1;
        } 
        // if n is greater than 1, recursively calculate fib(n-1) + fib(n-2)
        else {
            return fib(n - 1) + fib(n - 2);
        }
    }

    /*
     * The main method that prints numbers i*5 of the Fibonacci sequence, where i is between 0 <= i <= 10
     * each time incrementing the input to the "fib" method by 5.
     */
    public static void main(String[] args) {
        // loop through i from 0 to 10 (inclusive)
        for (int i = 0; i <= 10; i++) {
            // print "F(" + i * 5 + ") = " + fib(i * 5) to the console
            System.out.println("F(" + i * 5 + ") = " + fib(i * 5));
        }
    }
}