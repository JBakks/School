//Josh Bakelaar
//251139121
//CS2211
//4/6/2022

#include "sport_registration.h"

struct registration *registrations = NULL;

/* dump: Dumps contents of the event_tbl to specified
 *       file. Prints error message and does not
 *       terminate program upon failure. Does not store
 *       next pointer.
 */
void dump_registration(struct registration **registration_tbl)
{
    FILE *fp;
    char filename[255];
    struct registration **node = registration_tbl;

    printf("Enter name of output file: ");
    read_line(filename, 255);

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "File %s could not be written\n", filename);
        return;
    }

    while (*node)
    {
        fwrite(*node, sizeof(struct registration) - sizeof(struct registration *), 1, fp);
        node = &(*node)->next;
    }
    fclose(fp);
    return;
}

/* restore: Restores contents from specified file. Does
 *          not terminate upon file open failure, but
 *          terminates upon malloc failure.
 */
void restore_registration(struct registration **registration_tbl)
{
    FILE *fp;
    char filename[255];
    struct registration buffer;
    struct registration *temp;
    struct registration **node;

    printf("Enter name of input file: ");
    read_line(filename, 255);

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Error: file %s cannot be opened\n", filename);
        return;
    }

    while (*registration_tbl)
    {
        temp = *registration_tbl;
        *registration_tbl = (*registration_tbl)->next;
        free(temp);
    }

    node = registration_tbl;

    while (fread(&buffer,sizeof(struct registration) - sizeof(struct registration *),1,fp) == 1)
    {
        if ((*node = malloc(sizeof(struct registration))) == NULL)
        {
            fprintf(stderr, "Error: malloc failed in restore\n");
            exit(EXIT_FAILURE);
        }
        (*node)->code = buffer.code;
        (*node)->eventCode = buffer.eventCode;
        (*node)->athleteCode = buffer.athleteCode;
        (*node)->next = NULL;
        node = &(*node)->next;
    }
    fclose(fp);
    return;
}

//To be implemented

//find_registration: Looks up registration code in the event list. returns a pointer to the node containing the code; if the code is not found it returns NULL.
struct registration *find_registration(int code){
    struct registration *r;

    for (r = registrations; r != NULL && code > r->code; r = r->next);

    if (r != NULL && code == r->code){
        return r;
    }

    return NULL;
}

//insert_registration: Prompts user for info about new registration then inserts it in the registration list, if it already exists it prints error
void insert_registration(struct registration **rVar){
    struct registration *cur, *prev, *new_node;
    struct event *e;
    struct athlete *a;
    int eCode, aCode;

    new_node = malloc(sizeof(struct registration));

    if(new_node == NULL){
        printf("Database is full; can't add more registrations");
        return;
    }

    //Registration Code
    printf("        Enter registration code: ");
    scanf("%d", &new_node->code);

    //Assign it to the new_node
    for(cur = registrations, prev = NULL; cur != NULL && new_node->code > cur->code; prev = cur, cur = cur -> next);

    //If registration code already exists prompt for new
    if(cur != NULL && new_node->code == cur->code){
        printf("Registration already exists.\n");
        free(new_node);
        return;
    }

    //Event Code
    printf("        Enter event code: ");
    scanf("%d", &eCode);

    e = find_event(eCode);
    if (e != NULL){
        printf(" Event found.\n");
        new_node->eventCode = eCode;
    }else{
        printf("Event not found.\n");
    }

    //Athlete Code
    printf("        Enter athlete code: ");
    scanf("%d", &aCode);

    a = find_athlete(aCode);
    if (a != NULL){
        printf(" Athlete found.\n");
        new_node->athleteCode = aCode;
    }else{
        printf("Athlete not found.\n");
    }

    new_node->next = cur;
    if(prev == NULL){
        registrations = new_node;
    }else{
        prev->next = new_node;
    }
}

//search_registration: Prompts the user to enter registration code, then looks it up. If it exists, print the info, if not print an error
void search_registration(struct registration **rVar){
    int code;
    struct registration *r;

    printf("        Enter registration code: ");
    scanf("%d", &code);
    r = find_registration(code);
    if (r != NULL){
        printf("Registration Code    Event Code                Athlete Code\n");
        printf("%-13d %-27d %-28d\n", r->code, r->eventCode, r->athleteCode);
    }else{
        printf("Registration not found.\n");
    }
}

//update_registration: Updates registration with new information, similar to inserting an registration you just change the node
void update_registration(struct registration **rVar){
    int code, change;
    struct event *e;
    struct athlete *a;
    int eCode, aCode;
    struct registration *r;

    printf("        Enter registration code: ");
    scanf("%d", &code);
    r = find_registration(code);
    if (r != NULL){
        //Event Code
        printf("        Enter event code: ");
        scanf("%d", &eCode);

        e = find_event(eCode);
        if (e != NULL){
            printf(" Event found.\n");
            r->eventCode = eCode;
        }else{
            printf("Event not found.\n");
            return;
        }

        //Athlete Code
        printf("        Enter athlete code: ");
        scanf("%d", &aCode);

        a = find_athlete(aCode);
        if (a != NULL){
            printf(" Athlete found.\n");
            r->athleteCode = aCode;
        }else{
            printf("Athlete not found.\n");
            return;
        }
    }else{
        printf("Registration not found\n");
    }
}

//print_registration: prints out each registration in the list, with all of their info
void print_registration(struct registration **rVar){
    struct registration *r;
    printf("Registration Code    Event Code                Athlete Code\n");
    
    for(r = registrations; r != NULL; r = r->next){
        printf("%-20d %-25d %-24d\n", r->code, r->eventCode, r->athleteCode);
    }
}

//erase_registration: erases the registration from the list
void erase_registration(struct registration **rVar){
    int code;
    struct registration *r, *cur, *prev;

    printf("        Enter registration code: ");
    scanf("%d", &code);

    for(cur = registrations, prev = NULL; cur != NULL && cur->code != code; prev = cur, cur = cur->next);

    if (cur == NULL){
        printf("Error registration not found");
    }
    if(prev == NULL){
        registrations = registrations->next;
    }else{
        prev->next = cur->next;
    }

    free(cur);
}
