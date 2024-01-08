// Josh Bakelaar (251139121)
// 3/23/2023
// Assignment-4.c
// Accept 2 or 3 parameters (You can assume parameters are supplied in this order)
// The first parameter defines the algorithm to simulate.
// -f for First Come First Served
// -s for Shortest Job First. This should be implemented with preemption.
// -r <integer> for Round Robin
// (If -r is supplied, the next parameter is a positive integer defining the time quantum)
// The next parameter defines the filename to read input from. For the purposes of this assignment, this will always be assignment-4-input.csv, but of course, you can create your own versions for testing
// Depending on which algorithm is selected, your program should display the simulation of that algorithm including each processes' wait and turnaround time for each "tick" (one tick per line).
// Once all processes have finished, display the average wait time and turnaround time for all processes using that algorithm (to an accuracy of one decimal point

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Quantum time which will be entered if -r is entered
int quantum = 0;
// Number of processes in the csv file
int numProcesses = 0;

// Struct process which holds each processes information
struct process {
    int arrivalTime;
    int burstTime;
    int waitTime;
    int turnAroundTime;
    int originalBurst;
};

// Find avg time is the function used to find average wait and turn around time and then prints it out
void findavgTime(struct process processes[], int size){
    int totalWait = 0;
    int totalTurnAround = 0;

    // Iterate through processes list
    for(int i = 0; i < size; i++){
        // Add the wait time to total
        totalWait = totalWait + processes[i].waitTime;
        // Add turnaround time to total
        totalTurnAround = totalTurnAround + processes[i].turnAroundTime;    

        // print out each processes waiting time and turnaround time
        printf("\nP%d\n\t Waiting time: \t\t%3d\n\t Turnaround time: \t%3d\n", i, processes[i].waitTime, processes[i].turnAroundTime);
    }
    // Print out averages
    printf("\nTotal average waiting time: \t%3.1f\n", (float)totalWait/(float)size);
    printf("Total average tunraround time: \t%3.1f\n", (float)totalTurnAround/(float)size);
}

// First come first served function
void fcfs(struct process *processes, int size){
    // Id of the process
    int id = 0;
    // Total tick count
    int time = 0;
    // # of processes that are completed
    int completed = 0;
    
    // While # of completed processes is less then the number of processes..
    while(completed < size){
        // Iterate through the processes to add wait time and turn around time
        for(int i = 0; i < size; i++){
            // wait time will be incremented every time the current time is great than or equal to the arrival time, the burst time is not 0, and it is not the active process
            if(time >= processes[i].arrivalTime && processes[i].burstTime > 0 && i != id){
                processes[i].waitTime++;
            }

            // turnaround time will be incremented every time the current time is greater than or equal to the arrival time, and the burst time is not 0
            if(time >= processes[i].arrivalTime && processes[i].burstTime > 0){
                processes[i].turnAroundTime++;
            }
        }
        // Print out information on the process
        printf("T%-3d: P%-3d - Burst left %3d, Wait time %3d, Turnaround time %3d\n", time, processes[id].arrivalTime, processes[id].burstTime, processes[id].waitTime, processes[id].turnAroundTime-1);
        // Decrease burst time by 1
        processes[id].burstTime--;
        // If the bursttime is less than 1 it means the process is complete
        if(processes[id].burstTime < 1){
            // Increment completed
            completed++;
            // Go to next process
            id++;
        }
        // Increment tick
        time++;  
    }
    // Find average time of the processes and print
    findavgTime(processes, size);
}

// Sort function used to sort the processes from shortest job to longest (used by shortest job first)
void sort(struct process processes[], int size){
    // Key which will be the process to be moved
    struct process key;
    // Index variable
    int j;

    // Iterate through the processes list
    for(int i = 1; i < size; i++){
        // key is going to be equal to current index
        key = processes[i];
        // set index variable to be one less so it will point at previous
        j = i - 1;
        
        // While j is greater than or equal 0 and the burst time of the PREVIOUS index is higher
        while(j >= 0 && processes[j].burstTime >= key.burstTime){
            // Swap J into the right place
            processes[j+1] = processes[j];
            j = j-1;
        }
        // Put key into the right place
        processes[j+1] = key;
    }
}

// Shortest job first function
void sjf(struct process processes[], int size){
    // List to be sorted into shortest job
    struct process *sjfList = malloc(numProcesses * sizeof(struct process));
    // How many processes in sjfList
    int count = 0;
    // Current index
    int id = 0;
    int completed = 0;
    int time = 0;

    // While # of completed processes is less then the number of processes..
    while(completed < size){
        // add in the new process to the list
        if(time < numProcesses){
            sjfList[time] = processes[time];
            count++;
        }
        // sort the list
        sort(sjfList, count);

        // Iterate through the processes to add wait time and turn around time
        for(int j = 0; j < count; j++){
            // wait time will be incremented every time the current time is great than or equal to the arrival time, the burst time is not 0, and it is not the active process
            if(time >= sjfList[j].arrivalTime && sjfList[j].burstTime > 0 && j != id){
                sjfList[j].waitTime++;
            }
            // turnaround time will be incremented every time the current time is greater than or equal to the arrival time, and the burst time is not 0
            if(time >= sjfList[j].arrivalTime && sjfList[j].burstTime > 0){
                sjfList[j].turnAroundTime++;
            }
        }
        // Print out process info
        printf("T%-3d: P%-3d - Burst left %3d, Wait time %3d, Turnaround time %3d\n", time, sjfList[id].arrivalTime, sjfList[id].burstTime, sjfList[id].waitTime, sjfList[id].turnAroundTime-1);
        sjfList[id].burstTime = sjfList[id].burstTime-1;
        // If the bursttime is less than 1 it means the process is complete
        if(sjfList[id].burstTime < 1){
            // Increment completed
            completed++;
            // Go to next process
            id++;
        }
        // Increment tick
        time++;  
    }

    // Key to hold the process we are sorting
    struct process key;
    // Index value
    int j;

    // Iterate through the process list
    for(int i = 1; i < size; i++){
        // Key is going to equal the one we are wanting to sort
        key = sjfList[i];
        // Index is going to point to previous
        j = i - 1;

        // While j is greater than or equal 0 and the burst time of the PREVIOUS index is higher
        while(j >= 0 && sjfList[j].arrivalTime >= key.arrivalTime){
            // Swap J into the right place
            sjfList[j+1] = sjfList[j];
            j = j-1;
        }
        // Put the key into the right place
        sjfList[j+1] = key;
    }

    // Find average time of the processes and print
    findavgTime(sjfList, size);
}

// Round Robin Function
void rr(struct process processes[], int quantum, int size){
    // ID of the process
    int id = 0;
    // Tick count to keep track of quantum
    int tickCount = 0;
    // Variable to keep track of how many processes are complete
    int completed = 0;
    // To keep track of the time
    int time = 0;
    
    // While not all processes are complete
    while(completed < size){
        // If the tick count is greater than quantum
        if(tickCount >= quantum){
            // Reset tick count
            tickCount = 0;
            // Move the id to the next one (modulo for when it becomes bigger than size)
            id = (id + 1) % size;
            // Continue the iteration
            continue;
        }
        
        // If process is complete
        if(processes[id].burstTime == 0){
            // Reset tick count
            tickCount = 0;
            // Move the id to the next one (modulo for when it becomes bigger than size)
            id = (id + 1) % size;
            // Continue the iteration
            continue;
        }

        // Iterate through the processes to add wait time and turn around time
        for(int i = 0; i < size; i++){
            // wait time will be incremented every time the current time is great than or equal to the arrival time, the burst time is not 0, and it is not the active process
            if(time >= processes[i].arrivalTime && processes[i].burstTime > 0 && i != id){
                processes[i].waitTime++;
            }

            // turnaround time will be incremented every time the current time is greater than or equal to the arrival time, and the burst time is not 0
            if(time >= processes[i].arrivalTime && processes[i].burstTime > 0){
                processes[i].turnAroundTime++;
            }
        }

        // Print out info
        printf("T%-3d: P%-3d - Burst left %3d, Wait time %3d, Turnaround time %3d\n", time, processes[id].arrivalTime, processes[id].burstTime, processes[id].waitTime, processes[id].turnAroundTime-1);
        // Decrement burst count
        processes[id].burstTime--;     

        // If the process is complete
        if(processes[id].burstTime == 0){
            completed++;
        }
    
        // Increment tick
        tickCount++;  
        // Increment time 
        time++;
    }
    
    // Find average time and print it out
    findavgTime(processes, size);
}

// Main function
int main(int argc, char *argv[]){
    // If the arguments entered are incorrect
    if(argc < 2 || argc > 4){
        printf("Proper usage is ./assignment-4 [-f|-s|-r <quantum>] <Input file name>");
        exit(1);
    }

    // File input is going to be the last argument always
    char* input = argv[argc - 1];
    // Open file
    FILE *file = fopen(input, "r");

    // If file isnt found print error and exit 
    if(file == NULL){
        printf("Could not open %s\n", argv[argc - 1]);
        exit(1);
    }

    // Temp line count if needed go larger
    char line[1000];
    // For each line increment number of processes
    while(fgets(line, 100, file) != NULL){
        numProcesses++;
    }
    // Close file to restart back at 0 when opened again
    fclose(file);
    
    // Open file
    file = fopen(input, "r");
    // Create a dynamic list of processes
    struct process *processes = malloc(numProcesses * sizeof(struct process));

    // Counter
    int count = 0;
    // While there are lines
    while(fgets(line, 100, file) != NULL){
        // get the burst time
        char* time = strtok(line, ",");
        time = strtok(NULL, ",");
        // Make a new process 
        processes[count] = (struct process) {count, atoi(time), 0, 0, atoi(time)};
        // Increment
        count++;
    }
    // Close file
    fclose(file);

    // If fcfs wants to be used run it
    if(strcmp(argv[1], "-f") == 0){
        printf("First Come First Served\n");
        fcfs(processes, numProcesses);
    }
    // If sjf wants to be used run it
    if(strcmp(argv[1], "-s") == 0){
        printf("Shortest Job First\n");
        sjf(processes, numProcesses);
    }
    // If rr wants to be used run it
    if(strcmp(argv[1], "-r") == 0){
        quantum = atoi(argv[2]);
        printf("Round Robin with Quantum %d\n", quantum);
        rr(processes, quantum, numProcesses);
    }

    // Free the allcated memory
    free(processes);
}
