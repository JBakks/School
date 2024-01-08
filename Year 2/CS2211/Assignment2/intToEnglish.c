//Josh Bakelaar
//251139121
//JBAKELA
//2/9/2022
//intToEnglish.c
//turns ints (1-999) into the english word

#include <stdio.h>

int main(){

    int input = 1;
    const char *ones[10]; ones[0] = ""; ones[1] = "one"; ones[2] =  "two"; ones[3] = "three"; ones[4] = "four"; ones[5] = "five"; ones[6] = "six"; ones[7] = "seven"; ones[8] = "eight"; ones[9] = "nine"; 
    const char *teens[10]; teens[0] = "ten"; teens[1] = "eleven"; teens[2] = "twelve"; teens[3] = "thirteen"; teens[4] = "fourteen"; teens[5] = "fifteen"; teens[6] = "sixteen"; teens[7] = "seventeen"; teens[8] = "eighteen"; teens[9] = "nineteen";
    const char *tens[10]; tens[0] = ""; tens[1] = ""; tens[2] = "twenty"; tens[3] = "thirty"; tens[4] = "forty"; tens[5] = "fifty"; tens[6] = "sixty"; tens[7] = "seventy"; tens[8] = "eighty"; tens[9] ="ninety";

    //run until a 0 is typed
    while(input != 0){
        //prompt user
        printf("Please enter a value (1-999, 0 to quit): ");
        scanf("%d", &input);
        
	//if input is 0 break
	if(input == 0){
	    break;
	}
        //If input is too big prompt for a new num
        if(input > 999){
            printf("Number is too big!\n");
            continue;
        }

        //If input is too small prompt for a new num
        if(input < 0){
            printf("Number is too small!\n");
            continue;
        }

        //if below 10 grab from ones array
        if (input < 10){
            printf("You entered the number %s", ones[input]);
        //if below 20 but above 10 grab from teens
        }else if(input < 20){
            printf("You entered the number %s", teens[input - 10]);
        //if below 100 but above 19
        }else if (input < 100){
	    if(input%10 == 0){
	        printf("You entered the number %s", tens[input/10]);
	    }else{
                printf("You entered the number %s-%s", tens[input/10], ones[input%10]);
            }
	//if above 99 but below 1000
        }else if (input < 1000){
            if((input/10)%10 == 0){
                printf("You entered the number %s hundred and %s", ones[input/100], ones[input%10]);
            }else{
                printf("You entered the number %s hundred and %s-%s", ones[input/100], tens[input%10], ones[input%10]);
            }
        }

        //print a new line
        printf("\n");
    }

    return 0;
}
