//Josh Bakelaar
// 251139121

// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

// Define a Train struct with capacity and passengers fields
typedef struct {
    int capacity;
    int passengers;
} Train;

// Define the number of trains and initialize them with their respective capacity and passengers
#define NUM_TRAINS 2
Train trains[NUM_TRAINS] = {{50, 0}, {100, 0}};

// Define an array of integers representing the number of passengers at each station
int passengers[5] = {500, 50, 100, 250, 100};

// Define a mutex object for thread synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to print the arrival of a train at a station
void print_train_arrival(int train_num, int station_num) {
    printf("Train %d ENTERS Station %d\n", train_num, station_num);
}

// Function to print the departure of a train from a station
void print_train_departure(int train_num, int station_num) {
    printf("Train %d LEAVES Station %d\n", train_num, station_num);
}

// Function to print the status of a train at a station
void print_train_status(int train_num, int station_num) {
    printf("\tTrain %d is at Station %d and has %d/%d passengers\n", 
           train_num, station_num, trains[train_num].passengers, trains[train_num].capacity);
}

// Function to unload passengers from a train at a station
void unload_passengers(int train_num, int station_num) {
    // Acquire the lock to ensure mutual exclusion
    pthread_mutex_lock(&mutex);

    // Get the train object and print its arrival at the station
    Train* train = &trains[train_num];
    print_train_arrival(train_num, station_num);

    // Calculate the number of passengers to drop off based on the number of passengers at the station and the number of passengers on the train
    int num_to_dropoff = (passengers[station_num] < train->passengers) ? 
                         passengers[station_num] : train->passengers;

    // Print the number of passengers at the station and the number of passengers to be dropped off
    printf("\tStation %d has %d passengers to drop off\n", station_num, passengers[station_num]);
    printf("\tUnloading %d passengers...\n", num_to_dropoff);

    // Sleep for a period of time proportional to the number of passengers being dropped off
    sleep(num_to_dropoff / 10);

    // Subtract the number of passengers to be dropped off from the number of passengers at the station and the train
    passengers[station_num] -= num_to_dropoff;
    train->passengers -= num_to_dropoff;

    // Print the status of the train and its departure from the station
    print_train_status(train_num, station_num);
    print_train_departure(train_num, station_num);

    // Release the lock
    pthread_mutex_unlock(&mutex);
}

// Function to check if a train can pick up passengers at a station
bool can_pickup_passengers(int train_num, int station_num) {
    Train* train = &trains[train_num];
    int num_passengers = passengers[station_num];
    int train_capacity = train->capacity;
    int available_seats = train_capacity - train->passengers;
    return (available_seats > 0 && num_passengers > 0);
}

void pickup_passengers(Train* train, int station_num) {
    // Calculate how many passengers to pick up
    int num_to_pickup = trains[train - trains].capacity - train->passengers;

    // if there are more passengers at the station than the train can take pick up only as many as you can
    if (num_to_pickup > passengers[station_num]) {
        num_to_pickup = passengers[station_num];
    }

    // Lock to prevent other threads
    pthread_mutex_lock(&mutex);

    // Print information about pickup process
    printf("\tStation %d has %d passengers to pick up\n", station_num, passengers[station_num]);
    printf("\tLoading %d passengers...\n", num_to_pickup);

    // Sleep for a period of time proportional to the number of passengers being picked up
    sleep(num_to_pickup / 10);

    // Update the number of passengers at the station and on train
    passengers[station_num] -= num_to_pickup;
    train->passengers += num_to_pickup;

    // Update number of passengers at the station and on the train
    print_train_status(train - trains, station_num);
    print_train_departure(train - trains, station_num);

    // Unlock the mutex to allow other threads to access
    pthread_mutex_unlock(&mutex);
}

void* run_train(void* arg) {
    // Get train number from arg
    int* train_num_ptr = (int*)arg;
    int train_num = *train_num_ptr;

    // Loop through all stations    
    while (1) {
        bool passengers_remaining = false;
        for (int i = 0; i < 5; i++) {
            // Unload passengers at the current station
            unload_passengers(train_num, i);
            
            // if there are passengers to pick up at the current station pick them up
            if (can_pickup_passengers(train_num, i)) {
                pickup_passengers(&trains[train_num], i);
                passengers_remaining = true;
            }
        }
        // exit the loop if there are no more passengers to pick up or drop off
        if (!passengers_remaining) {
            break;        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_TRAINS];
    // create threads for each train
    for (int i = 0; i < NUM_TRAINS; i++) {
        int* train_num_ptr = malloc(sizeof(int));
        *train_num_ptr = i;
        pthread_create(&threads[i], NULL, run_train, (void*)train_num_ptr);
    }

    // wait for all threads to complete
    for (int i = 0; i < NUM_TRAINS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}