// Josh Bakelaar (251139121)
// CS3305: Assignment 2
// This programs accepts two 4-digit command line parameters
// Particians the two numbers into a1, a2, b1, b2
// Establish a pipe
// Fork a child process
//  1. The parent will send a1 and b1 to the child through a pipe
//  2. The child will multiply a1 and b1 and send A to the parent through a pipe. The parent will calculate X
//  3. The parent will send a2 and b1 and send B to the parent through a pipe
//  4. The chld will multiply a1 and b2 and send C to the parent through a pipe. The parent will calculate Y
//  5. The parent will send a1 and b2 to the child through a pipe
//  6. The child will multiply a1 and b2 and send C to the parent thorugh a pipe. The parent will calculate Y
//  7. The parent will send a2 and b2 and to the child thorugh a pipe
//  8. The child will multiply a2 and b2 and send D to the parent through a pipe. The parent will calculate Z
//  9. The child will exit
// The program will then calculate X + Y + Z and print the sum to the screen

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

int main(int argc, char *argv[] ) {
   // Declare all ints that we will be using.
   int a1, a2, b1, b2, A, B, C, D, X, Y, Z, num;
   // Declare the pipe ports that we will use.
   int sendPort[2], recPort[2];
   // Declare our pid to be forked later.
   pid_t pid;   

   // Run a loop which iterates at the 2nd argument entered, for this assignment it will always be 3.
   for(int i = 1; i < argc; i++){
      // Put the argument at position i into a character array.
      char* str = argv[i];
      
      // If it is the first argument, that will be A.
      if(i == 1){
         // Change the character array to an int.
         num = atoi(str);
         // Put the first 2 digits into a1.
         a1 = num/100;
         // Put the second 2 digits into a2.
         a2 = num%100;
      // Else if it is the second argument, that will be B
      }else if(i == 2){
         // Change the character array to an int.
         num = atoi(str);
         // Put the first 2 digits into a1.
         b1 = num/100;
         // Put the second 2 digits into a2.
         b2 = num%100;         
      }
   }

   // Print out what the arguments were.
   printf("\nYour integers are %d%d %d%d\n", a1, a2, b1, b2);
   
   // Just incase the pipes are < 0, this will catch the error and exit.
   if(pipe(sendPort) < 0 || pipe(recPort) < 0){
      perror("pipe error\n");
      exit(0);
   }

   // Start our fork process.
   pid = fork();

   // Parent will print out the parent ID and childs ID (always +1 from the parent).
   if(pid > 0){
      printf("Parent (PID %d): created child (PID %d)\n", getpid(), getpid()+1);
   }

   // Just incase the pid is > 0, this will catch the error and exit.
   if(pid < 0){
      perror("fork error\n");
      exit(0);
   }

   // Parent Process.
   if(pid > 0){
      // Calculating our X.
      printf("\n###\n# Calculating X\n###\n");

      // Send a1 and b1 through the pipe to the child and print out that it is being sent.
      printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
      write(sendPort[1], &a1, sizeof(a1));
      printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);
      write(sendPort[1], &b1, sizeof(b1));

      // Read our A value returned from the child and print out that it has been received.
      read(recPort[0], &A, sizeof(A));
      printf("Parent (PID %d): Received %d from child\n", getpid(), A);

      // Calculate our X by A * 10^n (where n is the length, in this case it will always be 4)
      X = A * pow(10, 4);

      // Calculating our Y.
      printf("\n###\n# Calculating Y\n###\n");

      // Send a1 and b2 through the pipe to the child and print out that it is being sent.
      printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
      write(sendPort[1], &a1, sizeof(a1));
      printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);
      write(sendPort[1], &b2, sizeof(b2));

      // Read our B value returned from the child and print out that it has been received.
      read(recPort[0], &B, sizeof(B));
      printf("Parent (PID %d): Received %d from child\n", getpid(), B);

      // Send a2 and b1 through the pipe to the child and print out that it is being sent.
      printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
      write(sendPort[1], &a2, sizeof(a2));
      printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);
      write(sendPort[1], &b1, sizeof(b1));

      // Read our C value returned from the child and print out that it has been received.
      read(recPort[0], &C, sizeof(C));
      printf("Parent (PID %d): Received %d from child\n", getpid(), C);

      // Calculate our Y by adding the returned B+C and multiply it by 10^n/2 (Because n is always 4 in this assignment we will just make n/2 = 2).
      Y = (B + C) * pow(10, 2);

      // Calculating our Z.
      printf("\n###\n# Calculating Z\n###\n");

      // Send a2 and b1 through the pipe to the child and print out that it is being sent.
      printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
      write(sendPort[1], &a2, sizeof(a2));
      printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);
      write(sendPort[1], &b2, sizeof(b2));

      // Read our C value returned from the child and print out that it has been received.
      read(recPort[0], &D, sizeof(D));
      printf("Parent (PID %d): Received %d from child\n", getpid(), D);

      // Calculate our Z by multiplying the returned D by 10^0 (always 1).
      Z = D * pow(10, 0);
   } 
   // Child Process.
   if(pid == 0){

      // Calculating our A.
      // Recieve a1 and b1 from the parent and print that it has been received.
      read(sendPort[0], &a1, sizeof(a1));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), a1);
      read(sendPort[0], &b1, sizeof(b1));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), b1);
      
      // A is going to be a1*b1.
      A = a1*b1;

      // Send A back to the parent and print that it is being sent.
      printf("\tChild (PID %d): Sending %d to parent\n", getpid(), A);
      write(recPort[1], &A, sizeof(A));

      // Calculating our B.
      // Recieve a1 and b2 from the parent and print that it has been received.
      read(sendPort[0], &a1, sizeof(a1));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), a1);
      read(sendPort[0], &b2, sizeof(b2));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), b2);

      // B is going to be a1*b1.
      B = a1*b2;

      // Send B back to the parent and print that it is being sent.
      printf("\tChild (PID %d): Sending %d to parent\n", getpid(), B);
      write(recPort[1], &B, sizeof(B));

      // Calculating our C.
      // Recieve a2 and b1 from the parent and print that it has been received.
      read(sendPort[0], &a2, sizeof(a2));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), a2);
      read(sendPort[0], &b1, sizeof(b1));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), b1);

      // C is going to be a1*b1.
      C = a2*b1;

      // Send C back to the parent and print that it is being sent.
      printf("\tChild (PID %d): Sending %d to parent\n", getpid(), C);
      write(recPort[1], &C, sizeof(C));

      // Calculating our D.
      // Recieve a2 and b2 from the parent and print that it has been received.
      read(sendPort[0], &a2, sizeof(a2));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), a2);
      read(sendPort[0], &b2, sizeof(b2));
      printf("\tChild (PID %d): Received %d from parent\n", getpid(), b2);

      // D is going to be a1*b1.
      D = a2*b2;

      // Send D back to the parent and print that it is being sent.
      printf("\tChild (PID %d): Sending %d to parent\n", getpid(), D);
      write(recPort[1], &D, sizeof(D));
   }
   
   // If the process is the parent process print out the final calulation.
   if(pid > 0){
      printf("\n%d%d*%d%d == %d + %d + %d == %d\n", a1, a2, b1, b2, X, Y, Z, X+Y+Z);
   }

   // End.
   return 0;
}