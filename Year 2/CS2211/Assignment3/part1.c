//Josh Bakelaar (251139121)
//CS2211
//March 2, 2022nd
//part1.c
//Playing around with arrays

#include <stdio.h>
#include <stdlib.h>

//Part 1 (Print elements, num of elements, total size of array in bytes)
void print_array(int *a, int size){
    printf("\nPart 1: \n");

    //Print each element in the array
    printf("    Your array is: ");
    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }

    //num of elements will be the size
    printf("\n    Your array has %d elements.", size);
    //multiply size by 4 to find number of bytes
    printf("\n    The size of the array is %d bytes.", (size*4));
}

//Part 2 (Print array in reverse)
void reverse_array(int *a, int size){
    printf("\n\nPart 2: \n");

    //Same as part 1 but start from end of array and go backwards
    printf("    Your array in reverse is: "); 
    for (int i = size-1; i >= 0; i--){
        printf("%d ", a[i]);
    }
}

//Part 3
void smallest_array(int *a, int size){
    printf("\n\nPart 3: \n");

    //variable to hold smallest value
    int smallest = a[0];

    //iterate through the array if the current value is < smallest, smallest now = that value
    for (int i = 1; i < size; i++){
        if (smallest > a[i]){
            smallest = a[i];
        }
    }

    printf("    The smallest value in your array is: %d", smallest);
}

//Part 4
void sum_array(int *a, int size){
    printf("\n\nPart 4: \n");

    //variable to hold the sum
    int sum = 0;

    //iterate through the array and add each value to the sum
    for (int i = 0; i < size; i++){
        sum = sum + a[i];
    }

    printf("    The sum of all values in your array is: %d", sum);
}

//Part 5
void swap_array(int *a, int size){
    printf("\n\nPart 5: \n");

    //Temp variable to hold the first value
    int temp = a[0];
    //Make the first value = the last
    a[0] = a[size-1];
    //Make the last = the temp
    a[size-1] = temp;

    //Print out the array the same way as Part 1
    printf("    Your array with first and last element switched is: ");
    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
}

//Part 6
void sort_array(int *a, int size){
    printf("\n\nPart 6: \n");

    //Using a bubble sort algorithm navigate and sort the array
    for (int i = 0; i < size; i++){ //First loop will go through each element
        for (int j = 0; j < size - 1; j++){//Second loop will compare elements
            //If the current element is greater then the next swap them
            if (a[j] > a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
           }
       }
   }

   //Print out the array the same way as Part 1
    printf("    Your array in sorted order is: ");
    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main (void){
    int *a;
    int size;

    printf("What would you like the size of the array to be?: ");
    scanf("%d", &size);

    a = (int *) malloc(sizeof(int) * (size));


    if (!a){
        printf("Error allocating memory");
    }

    printf("Enter %d integers seperated by spaces: ", size);
    for(int i = 0; i< size; i++){
        scanf("%d", &a[i]);
    }

    print_array(a, size);
    reverse_array(a, size);
    smallest_array(a, size);
    sum_array(a, size);
    swap_array(a, size);
    sort_array(a, size);
   
}

