// Josh Bakelaar (251139121)
// assignment-1.c
// Given a checkPassowrd function, by brute force, figure out what the password is

// Password is 12 characters in length
// Password could contain any character in range 33 - 126 in ASCII
// Function provided called checkPassword
// --> Can only check 3 characters at a time
// --> Supply 3 letter guess and position you want to check
// --> Returns 0 if correct
// --> Returns -1 if incorrect

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "checkPassword.h"

/* crackPassword
------------------------------------------------------------------
   Takes in starting position to test password with.
   Returns the correct combonation for the segment of the password
*/
char* crackPassword(int start){
    char *chars = malloc(2);

    // Loop for 1st character
    for(int i = 33; i <= 126; i++){
        // Loop for 2nd character
        for(int j = 33; j <= 126; j++){
            // Loop for 3rd character
            for(int k = 33; k <= 126; k++){
                chars[0] = i;
                chars[1] = j;
                chars[2] = k;
                // If combo is correct then return it
                if (checkPassword(chars, start) == 0){
                    return chars;
                }
            }
        }
    }
    return(0);
}

int main(int argc, char *argv[]){
    // Booleans for args (-f, -p)
    bool shouldFork = false;
    bool shouldHackMe = false;
    
    // Create a pid
    pid_t pid;

    // Loop for checking the args
    for(int i = 1; i < argc; i++){
        // Can accept an optional command-line argument -f to signify that forking should be enabled or not.
        if(strcmp(argv[i], "-f") == 0){
            shouldFork = true;
        }
        // Can accept an optional command-line argument -p to signify that the parent process should automatically run hackme using execl
        if(strcmp(argv[i], "-p") == 0){
            shouldHackMe = true;
        }
    }

    // If no args run the program without forking, cracking one part at a time.
    if(!shouldFork){
        printf("%s\n", crackPassword(0));
        printf("%s\n",crackPassword(3));
        printf("%s\n",crackPassword(6));
        printf("%s\n",crackPassword(9));
    // Else user will want you to fork
    }else{
        //First Fork
        pid = fork();
        
        // Parent 1.0
        if(pid > 0){
            // Second Fork
            pid = fork();
            if(pid>0){ 
                // Parent check 0-2
                printf("%s\n", crackPassword(0));
                // Wait for child 1 and 2
                wait(NULL);
            // Child 1.2 (1)
            }else{
                // Print out parent process id and its own
                printf("PID 1.0 IS %d. CHILD 1.2 IS %d.\n", getppid() ,getpid());
                printf("PID 1.2 IS %d. PPID IS 1.0 %d\n", getpid(), getppid());
                // Child 1 check 3-5
                printf("%s\n", crackPassword(3));
            }
            // Wait for the res
            wait(NULL);
        // Child 1.1
        }else{
            // Print out parent process id and its own
            printf("PID 1.0 IS %d. CHILD 1.1 IS %d\n", getppid(),getpid());
            printf("PID 1.1 IS %d. PPID IS 1.0 %d\n", getpid(), getppid());
            // Third Fork
            pid = fork();
            // Parent 1.1
            if(pid > 0){
                // Print out parent process id and its own
                printf("PID 1.1 IS %d. CHILD 1.1.1 IS %d\n", getppid(),getpid());
                printf("PID 1.1.1 IS %d. PPID IS 1.1 %d\n", getpid(), getppid());
                // Child 2 check 6-9
                printf("%s\n", crackPassword(6));
                // Wait for Child of Child 2
                wait(NULL);
            // Child 1.1.1
            }else{
                // Child of Child 2 check 10-12
                printf("%s\n", crackPassword(9));
                // If -p run hackme
                if(shouldHackMe){
                    execl("./hackme","hackme", NULL);
                }else {
                    // Else return 0
                    return(0);
                }
            }
        }
    }
}
