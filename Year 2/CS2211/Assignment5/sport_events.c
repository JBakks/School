//Josh Bakelaar
//251139121
//CS2211
//4/6/2022

#include "sport_events.h"

struct event *events = NULL;

/* dump: Dumps contents of the event_tbl to specified
 *       file. Prints error message and does not
 *       terminate program upon failure. Does not store
 *       next pointer.
 */
void dump_event(struct event **event_tbl)
{
    FILE *fp;
    char filename[255];
    struct event **node = event_tbl;

    printf("Enter name of output file: ");
    read_line(filename, 255);

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "File %s could not be written\n", filename);
        return;
    }

    while (*node)
    {
        fwrite(*node, sizeof(struct event) - sizeof(struct event *), 1, fp);
        node = &(*node)->next;
    }
    fclose(fp);
    return;
}

/* restore: Restores contents from specified file. Does
 *          not terminate upon file open failure, but
 *          terminates upon malloc failure.
 */
void restore_event(struct event **event_tbl)
{
    FILE *fp;
    char filename[255];
    struct event buffer;
    struct event *temp;
    struct event **node;

    printf("Enter name of input file: ");
    read_line(filename, 255);

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Error: file %s cannot be opened\n", filename);
        return;
    }

    while (*event_tbl)
    {
        temp = *event_tbl;
        *event_tbl = (*event_tbl)->next;
        free(temp);
    }

    node = event_tbl;

    while (fread(&buffer,sizeof(struct event) - sizeof(struct event *),1,fp) == 1)
    {
        if ((*node = malloc(sizeof(struct event))) == NULL)
        {
            fprintf(stderr, "Error: malloc failed in restore\n");
            exit(EXIT_FAILURE);
        }
        (*node)->code = buffer.code;
        strcpy((*node)->name, buffer.name);
        (*node)->size = buffer.size;
        (*node)->gender = buffer.gender;
        (*node)->next = NULL;
        node = &(*node)->next;
    }
    fclose(fp);
    return;
}

//To be implemented

//find_event: Looks up event code in the event list. returns a pointer to the node containing the code; if the code is not found it returns NULL.
struct event *find_event(int code){
    struct event *e;

    for (e = events; e != NULL && code > e->code; e = e->next);

    if (e != NULL && code == e->code){
        return e;
    }

    return NULL;
}

//insert_event: Prompts user for info about new event then inserts it in the event list, if it already exists it prints error
void insert_event(struct event **eVar){
    struct event *cur, *prev, *new_node;

    new_node = malloc(sizeof(struct event));

    if(new_node == NULL){
        printf("Database is full; can't add more events");
        return;
    }

    //Event Code
    printf("        Enter event code: ");
    scanf("%d", &new_node->code);

    while(new_node->code < 0){
        printf("Code must be greater than or equal to 0\n");
        printf("        Enter event code: ");
        scanf("%d", &new_node->code);
    }

    //Assign it to the new_node
    for(cur = events, prev = NULL; cur != NULL && new_node->code > cur->code; prev = cur, cur = cur -> next);

    //If event code already exists prompt for new
    if(cur != NULL && new_node->code == cur->code){
        printf("Event already exists.\n");
        free(new_node);
        return;
    }

    //Event Name
    printf("        Enter event name: ");
    read_line(new_node->name, NAME_LEN);

    //Event competitors
    printf("        Enter number of competitors: ");
    scanf("%d", &new_node->size);

    while(new_node->size < 10 || new_node->size > 99){
        printf("Only integers 10-99 are acceptable\n");
        printf("        Enter number of competitors: ");
        scanf("%d", &new_node->size);
    }

    //Event gender
    printf("        Enter the gender: ");
    scanf(" %c", &new_node->gender);

    if(new_node->gender == 'M' || new_node->gender == 'W' || new_node->gender == 'X' ){
    }else{
        printf("Acceptable characters for gender are W, M, X\n");
        printf("        Enter the gender: ");
        scanf(" %c", &new_node->gender);
    }

    new_node->next = cur;
    if(prev == NULL){
        events = new_node;
    }else{
        prev->next = new_node;
    }
}

//search_event: Prompts the user to enter event code, then looks it up. If it exists, print the info, if not print an error
void search_event(struct event **eVar){
    int code;
    struct event *e;

    printf("        Enter event code: ");
    scanf("%d", &code);
    e = find_event(code);
    if (e != NULL){
        printf("Event Code    Event Name                  Competitors                  Gender\n");
        printf("%-13d %-27s %-28d %c\n", e->code, e->name, e->size, e->gender);
    }else{
        printf("Event not found.\n");
    }
}

//update_event: Updates event with new information, similar to inserting an event you just change the node
void update_event(struct event **eVar){
    int code, change;
    struct event *e;

    printf("        Enter event code: ");
    scanf("%d", &code);
    e = find_event(code);
    if (e != NULL){
        //Event Name
        printf("        Enter event name: ");
        read_line(e->name, NAME_LEN);

        //Event competitors
        printf("        Enter number of competitors: ");
        scanf("%d", &e->size);

        while(e->size < 10 || e->size > 99){
            printf("Only integers 10-99 are acceptable\n");
            printf("        Enter number of competitors: ");
            scanf("%d", &e->size);
        }

        //Event gender
        printf("        Enter the gender: ");
        scanf(" %c", &e->gender);

        if(e->gender == 'M' || e->gender == 'W' || e->gender == 'X' ){
        }else{
            printf("Acceptable characters for gender are W, M, X\n");
            printf("        Enter the gender: ");
            scanf(" %c", &e->gender);
        }
    }else{
        printf("Event not found\n");
    }
}

//print_event: prints out each event in the list, with all of their info
void print_event(struct event **eVar){
    struct event *e;
    printf("Event Code    Event Name                  Competitors                  Gender\n");
    
    for(e = events; e != NULL; e = e->next){
        printf("%-13d %-27s %-28d %c\n", e->code, e->name, e->size, e->gender);
    }
}

//erase_event: erases the event from the list
void erase_event(struct event **eVar){
    int code;
    struct event *e, *cur, *prev;

    printf("        Enter event code: ");
    scanf("%d", &code);

    for(cur = events, prev = NULL; cur != NULL && cur->code != code; prev = cur, cur = cur->next);

    if (cur == NULL){
        printf("Error event not found");
    }
    if(prev == NULL){
        events = events->next;
    }else{
        prev->next = cur->next;
    }

    free(cur);
}
