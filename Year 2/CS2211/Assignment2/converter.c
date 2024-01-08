//Josh Bakelaar
//251139121
//JBAKELA
//2/9/2022
//converter.c
//Makes simple conversions

#include <stdio.h>

int main(){
    int converter;
    char userInput;

    //Run while converter does not = 5
    while((int) converter != 5){
        printf("\nWhich converter do you want to do? (1 = Kilometre and Mile, 2 = Litres and Gallons, 3 = Hectares and Acres, 4 = Kilograms and Pounds, 5 = quit): ");
        scanf("%d", &converter);
        printf("\n");
        
        //Kilometer and Mile
        if( (int) converter == 1){
            //Promt the user
            printf("Which conversion do you want to do? (K = conversion from Kilometer to Mile, M = conversion from Mile to Kilometer): ");
            scanf(" %c", &userInput);
            
            //Kilometer to Miles
            if((char)userInput == 'K' || (char)userInput == 'k'){
                float kilometers;

                //Prompt User
                printf("Enter how many Kilometers: ");
                scanf("%f", &kilometers);
                printf("%f Kilometers is %f Miles.", (float) kilometers, (float) kilometers*0.621371);

            //Miles to Kilometers
            }else if((char)userInput == 'M' || (char)userInput == 'm'){
                float miles;

                //Prompt User
                printf("Enter how many Miles: ");
                scanf("%f", &miles);
                printf("%f Miles is %f Kilometers.", (float) miles, (float) miles/0.621371);
            }

        //Litres and Gallons
        }else if( (int) converter == 2){
            //Prompt the user
            printf("Which conversion do you want to do? (L = conversion from Litres to Gallons, G = conversion from Gallons to Litres): ");
            scanf(" %c", &userInput);

            //Litres to Gallons
            if((char)userInput == 'L' || (char)userInput == 'l'){
                float litres;

                //Promt User
                printf("Enter how many Litres: ");
                scanf("%f", &litres);
                printf("%f Litres is %f Gallons.", (float) litres, (float) litres*0.264172);
            }

            if((char)userInput == 'G' || (char)userInput == 'g'){
                float gallons;

                //Prompt User
                printf("Enter how many Gallons: ");
                scanf("%f", &gallons);
                printf("%f Gallons is %f Litres", (float) gallons, (float) gallons/0.264172);
            }
        //Hectares and Acres
        }else if( (int) converter == 3){
            //Prompt the user        
            printf("Which conversion do you want to do? (H = conversion from Hectares to Acres, A = conversion from Acres to Hectares): ");
            scanf(" %c", &userInput);

            //Hectares to Acres
            if((char)userInput == 'H' || (char)userInput == 'h'){
                float hectares;

                //Prompt user
                printf("Enter how many Hectares: ");
                scanf("%f", &hectares);
                printf("%f Hectares is %f Acres.", (float) hectares, (float) hectares*2.47105);
            }

            //Acres to Hectares
            if((char)userInput == 'A' || (char)userInput == 'a'){
                float acres;

                //Prompt user
                printf("Enter how many Acres: ");
                scanf("%f", &acres);
                printf("%f Acres is %f Hectares.", (float) acres, (float) acres/2.47105);
            }
            
        //Kilograms and Pounds
        }else if( (int) converter == 4){
            //Prompt the user
            printf("Which conversion do you want to do? (K = conversion from Kilograms to Pounds, P = conversion from Pounds to Kilograms): ");
            scanf(" %c", &userInput);

            //Kilograms to Pounds
            if((char)userInput == 'K' || (char)userInput == 'k'){
                float kilograms;

                //Prompt user
                printf("Enter how many Kilograms: ");
                scanf("%f", &kilograms);
                printf("%f Kilograms is %f Pounds.", (float) kilograms, (float) kilograms*2.20462);
            }
            //Pounds to Kilograms
            if((char)userInput == 'P' || (char)userInput == 'p'){
                float pounds;

                //Prompt user
                printf("Enter how many Pounds: ");
                scanf("%f", &pounds);
                printf("%f Pounds is %f Kilograms.", (float) pounds, (float) pounds/2.20462);

            }
           
        }else if(! (int) userInput == 5){
            //Invalid option
            printf("\nPlease enter a valid option\n");
            continue;
        }

        //Print a new line
        printf("\n");
    }
    printf("\nQuiting...");
    return 0;
 }
    

