//Josh Bakelaar
//251139121
//3/22/2022
//sport_db.c
//Create a database for the 2211 Winter Olympics
//Be able to insert, update, search, and print events

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define NAME_LEN 50
#define MAX_EVENTS 100

//Structure for the events
struct event{
    int eventCode;
    char eventName[NAME_LEN+1];
    int eventCompetitors;
    char gender[2];
} events[MAX_EVENTS];

//number of events currently stored
int num_events = 0;

//Skips leading white space characters, then reads the remainder of the iput line and store it as a string. Returns the number of characters stored.
int read_line(char str[], int n){
    int ch, i = 0;
    while (isspace(ch = getchar()))
        ;
    while (ch != '\n' && ch != EOF) {
        if (i < n){
            str[i++] = ch;
        }
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}

//Looks up event number in events array. returns index if event num is found; otherwise, return -1
int findEvent(int num){
    //loop through array until you match the event
    for(int i = 0; i < num_events; i++){
        if(events[i].eventCode == num){
            return i;
        }
    }
    return -1;
}

//Prompts user for information about a new event and inserts it into the array. Prints error if the number already exists/ array is full
void insertEvent(){
    int eventCode, eventCompetitors;
    bool gender = false;

    //if event list is full, print error message
    if(num_events == MAX_EVENTS){
        printf("Event list is full; can't add more events. \n");
        return;
    }

    //Event Code
    printf("        Enter event code: ");
    scanf("%d", &eventCode);
    //Only accept 0-99
    while(eventCode > 99){
        printf("Only integers from 0-99 are accepted\n");
        printf("        Enter event code: ");
        scanf("%d", &eventCode);
    }
    //If code already exists print error
    if(findEvent(eventCode) >= 0){
        printf("Event code already exists. \n");
        return;
    }
    events[num_events].eventCode = eventCode;
    
    //Event Name
    printf("        Enter event name: ");
    read_line(events[num_events].eventName, NAME_LEN);

    //Event Competitiors
    printf("        Enter number of competitors: ");
    scanf("%d", &eventCompetitors);
    //Only accept 10-99 competitors 
    while(eventCompetitors > 99 || eventCompetitors < 10){
        printf("Only integers from 10-99 are accepted\n");
        printf("        Enter number of competitors: ");
        scanf("%d", &eventCompetitors);
    }
    events[num_events].eventCompetitors = eventCompetitors;

    //Event Gender
    printf("        Enter the gender: ");
    scanf(" %c", &events[num_events].gender);

    //Compare with each valid response and change boolean to true
    if(strcmp(events[num_events].gender, "W") == 0){
        gender = true;
    }
    if(strcmp(events[num_events].gender, "M") == 0){
        gender = true;
    }
    if(strcmp(events[num_events].gender, "X") == 0){
        gender = true;
    }   
    //Until the boolean is true keep getting characters
    while(!gender){
        printf("Acceptable characters for gender are W, M, X\n");
        printf("        Enter the gender: ");
        scanf(" %c", &events[num_events].gender);

        if(strcmp(events[num_events].gender, "W") == 0){
            gender = true;
        }
        if(strcmp(events[num_events].gender, "M") == 0){
            gender = true;
        }
        if(strcmp(events[num_events].gender, "X") == 0){
            gender = true;
        }
    }
    //Increment the number of events
    num_events++;
}

//Searches for a event code, then returns information about event. If not found print error
void searchEvent(){
    int i, code, eventCode;

    printf("        Enter event code: ");
    scanf("%d", &code);
    //Use findevent method to find the spot in the array
    i = findEvent(code);

    //if valid then print info
    if(i >= 0){
        printf("Event Code    Event Name                  Competitors                  Gender\n");
        printf("%-13d %-27s %-28d %s\n", events[i].eventCode, events[i].eventName, events[i].eventCompetitors, events[i].gender);
    }else{
        printf("Event not found. \n");
    }
}

//Updates event with new information, similar to inserting an event you just change the current spot
void updateEvent(){
    int i, code, eventCode, eventCompetitors;
    bool gender = false;

    printf("        Enter event code: ");
    scanf("%d", &code);
    i = findEvent(code);
    
    if(i >= 0){
        //Event Name
        printf("        Enter event name: ");
        read_line(events[i].eventName, NAME_LEN);

        //Event Competitors (same as insert)
        printf("        Enter number of competitors: ");
        scanf("%d", &eventCompetitors);
        while(eventCompetitors > 99 || eventCompetitors < 10){
            printf("Only integers from 10-99 are accepted\n");
            printf("        Enter number of competitors: ");
            scanf("%d", &eventCompetitors);
        }
        events[i].eventCompetitors = eventCompetitors;

        //Event Gender (same as insert)
        printf("        Enter the gender: ");
        scanf(" %c", &events[i].gender);

        if(strcmp(events[i].gender, "W") == 0){
            gender = true;
        }
        if(strcmp(events[i].gender, "M") == 0){
            gender = true;
        }
        if(strcmp(events[i].gender, "X") == 0){
            gender = true;
        }

        while(!gender){
            printf("Acceptable characters for gender are W, M, X\n");
            printf("        Enter the gender: ");
            scanf(" %c", &events[i].gender);

            if(strcmp(events[i].gender, "W") == 0){
                gender = true;
            }
            if(strcmp(events[i].gender, "M") == 0){
                gender = true;
            }
            if(strcmp(events[i].gender, "X") == 0){
                gender = true;
            }
        }
    }else{
        printf("Event not found, please try again");
    }
}

//Print information about all events
void printEvents(){
    int i;

    printf("Event Code    Event Name                  Competitors                  Gender\n");
    for(i = 0; i < num_events; i++){
        printf("%-13d %-27s %-28d %s\n", events[i].eventCode, events[i].eventName, events[i].eventCompetitors, events[i].gender);
    }
}

//Driver code
int main () {
    char code;

    //print banner
    printf("*************************\n");
    printf("* 2211 Winter Olympics! *\n");
    printf("*************************\n\n");
    
    //Go until 0 is returned
    for(;;){
        //get op code
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n');

        switch (code){
            case 'i': insertEvent();
                      break;
            case 's': searchEvent();
                      break;
            case 'u': updateEvent();
                      break;
            case 'p': printEvents();
                      break;
            case 'q': return 0;
            default:  printf("Illegal code\n");
        }
        printf("\n");
    }
}
