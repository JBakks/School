/*
    Josh Bakelaar (251139121)
    CS3305: Assignment 3
    assignment-3.c
    A C program which acceps two command-line parameters
        - how many threads to create
        - maximum number to calculate prime numbers up to
    Program will count number of primes up to N and the sum of those pirmes
    This tas needs to be done by dividing the task across multiple threads
*/

// Includes.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// Varible count to calculate what numbers each thread is calculating.
int count = 0;

// Final sum and final number of prime numbers.
long int grandSum = 0;
int grandPrimeCount = 0;

// Data to be passed through threads
typedef struct data{
    int threadCount;
    int start;
    int end;
    long int sum;
    int primeCount;
} data;

// isPrime calculates wether or not a number is prime or not.
// Returns false if not a prime.
// Returns true if is a prime.
bool isPrime(int num){
    // Iterate from 2 (1 and 0 are not primes) - i*i.
    for(int i = 2; i*i<=num; i++){
        // Test wether or not our num can be divided by i
        if(num % i == 0){
            // if it can return false
            return false;
        }
    }
    // if it cant be devided by anything return true.
    return true;
}

void *sumPrimes(void * args) {
    // To hold the sum of the range of numbers we are testing
    long int sum = 0;
    // To count how many primes in range
    int primeCount = 0;
    
    // Put the passed through data into a threadData object
    data *threadData = args;

    // Assign all needed numbers to variables used for calculating primes
    int threadCount = threadData->threadCount;
    int start = threadData->start;
    int end = threadData->end;

    // Print out what thread, and what range it is looking at
    printf("Thread # %d is finding primes from low = %d to high = %d\n", threadCount, start, end);

    // Iterate from the starting number to the end number checking primes
    for(int i = start; i < end; i++){
        // Skip 1 and 0
        if(i == 1 || i == 0){
            continue;
        }
        
        // Check if the number is prime
        if(isPrime(i)){
            // If number is prime, increase our prime count.
            primeCount++;
            // Add number to sum
            sum= sum + i;
        }
    }

    // Print of what thread we are on, its sum of primes, and how many primes
    printf("Sum of thread %d is %ld, Count is %d\n", threadCount, sum, primeCount);

    // Add thread totals to grand totals
    grandPrimeCount+=primeCount;
    grandSum+=sum;

    // Assign needed data to threads
    threadData->primeCount = primeCount;
    threadData->sum = sum;
    threadData->threadCount = threadCount;

    // Increment our thread count
    threadCount++;
    return 0;
}

int main(int argc, char const *argv[])
{
    // Only take valid inputs
    if(argv[1] == NULL || argv[2] == NULL || argc > 3){
        printf("Proper usage is ./assignment-3 <threadCount> <highestInt>\n");
        
        // leave main
        return 0;
    }

    // How many threads your program should create
    int numThreads = atoi(argv[1]);
    // Maximum number your prime counting/summing will go to
    int maxNum = atoi(argv[2]);

    // How many numbers will each thread calculate
    int perThread = (maxNum/numThreads)+1;

    // Values for our start and end numbers
    int start = 0;
    int end = 0;

    // Create threads
    pthread_t worker_thread[numThreads];
    // Create data object to hold thread data
    data *threadData = malloc(sizeof *threadData);

    // Iterate through how many threads we have
    for (int i = 0; i < numThreads; i++){
        // Starting number is going to equal what number we left off at (0 for first)
        start = count;
        // If the number we left off at + how many we want to calculate is over the maxNum
        if(count+perThread > maxNum){
            // Our end number will be the maxNum
            end = maxNum;     
        // Else just add how many were going to iterate through to where we left off       
        }else{
            end = count+perThread; 
        }

        // Create data for this thread and assign needed values
        data *threadData = malloc(sizeof *threadData);
        threadData -> threadCount = i;
        threadData -> start = start;
        threadData -> end = end;
        
        // Create the thread
        if (pthread_create(&worker_thread[i], NULL, sumPrimes, threadData)) {
            printf("Error while creating thread\n");
        }

        // Add how many numbers we just checked to where we left off
        count = count+perThread;
    }

    // Only print if not the main thread
    if(!pthread_self()){
        // Print what thread it is, what the sum of the thread was, and the number of prime numbers the thread incountered
        printf("Sum of thread %d is %ld, Count is %d\n", threadData->threadCount, threadData->sum, threadData->primeCount);
    }
    

    // Iterate through how many threads we have
    for (int i = 0; i<numThreads; i++){
        // Join the threads
        if (pthread_join(worker_thread[i], NULL)){ 
            printf("Error joining with thread");
        }
    }

    // Print grand sum and grand count
    printf("\n\tGRAND SUM IS = %ld, COUNT IS %d\n", grandSum, grandPrimeCount);
}
