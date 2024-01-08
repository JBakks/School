//Josh Bakelaar
//251139121
//CS2211
//4/6/2022

#include "sport_athlete.h"

struct athlete *athletes = NULL;

/* dump: Dumps contents of the athlete_tbl to specified
 *       file. Prints error message and does not
 *       terminate program upon failure. Does not store
 *       next pointer.
 */
void dump_athlete(struct athlete **athlete_tbl)
{
    FILE *fp;
    char filename[255];
    struct athlete **node = athlete_tbl;

    printf("Enter name of output file: ");
    read_line(filename, 255);

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        fprintf(stderr, "File %s could not be written\n", filename);
        return;
    }

    while (*node)
    {
        fwrite(*node, sizeof(struct athlete) - sizeof(struct athlete *), 1, fp);
        node = &(*node)->next;
    }
    fclose(fp);
    return;
}

/* restore: Restores contents from specified file. Does
 *          not terminate upon file open failure, but
 *          terminates upon malloc failure.
 */
void restore_athlete(struct athlete **athlete_tbl)
{
    FILE *fp;
    char filename[255];
    struct athlete buffer;
    struct athlete *temp;
    struct athlete **node;

    printf("Enter name of input file: ");
    read_line(filename, 255);

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Error: file %s cannot be opened\n", filename);
        return;
    }

    while (*athlete_tbl)
    {
        temp = *athlete_tbl;
        *athlete_tbl = (*athlete_tbl)->next;
        free(temp);
    }

    node = athlete_tbl;

    while (fread(&buffer,sizeof(struct athlete) - sizeof(struct athlete *),1,fp) == 1)
    {
        if ((*node = malloc(sizeof(struct athlete))) == NULL)
        {
            fprintf(stderr, "Error: malloc failed in restore\n");
            exit(EXIT_FAILURE);
        }
        (*node)->code = buffer.code;
        strcpy((*node)->name, buffer.name);
        (*node)->age = buffer.age;
        (*node)->gender = buffer.gender;
        (*node)->next = NULL;
        node = &(*node)->next;
    }
    fclose(fp);
    return;
}

//To be implemented
//find_athlete: Looks up athlete code in the athlete list. returns a pointer to the node containing the code; if the code is not found it returns NULL.
struct athlete *find_athlete(int code){
    struct athlete *a;

    for (a = athletes; a != NULL && code > a->code; a = a->next);

    if (a != NULL && code == a->code){
        return a;
    }

    return NULL;
}

//insert_athlete: Prompts user for info about new athlete then inserts it in the athlete list, if it already exists it prints error
void insert_athlete(struct athlete **eVar){
    struct athlete *cur, *prev, *new_node;

    new_node = malloc(sizeof(struct athlete));

    if(new_node == NULL){
        printf("Database is full; can't add more athletes");
        return;
    }

    //Athlete Code
    printf("        Enter athlete code: ");
    scanf("%d", &new_node->code);

    //Assign it to the new_node
    for(cur = athletes, prev = NULL; cur != NULL && new_node->code > cur->code; prev = cur, cur = cur -> next);

    //If athlete code already exists prompt for new
    if(cur != NULL && new_node->code == cur->code){
        printf("Athlete already exists.\n");
        free(new_node);
        return;
    }

    //Athlete Name
    printf("        Enter Athlete name: ");
    read_line(new_node->name, NAME_LEN);

    //Athlete age
    printf("        Enter age of athlete: ");
    scanf("%d", &new_node->age);

    while(new_node->age < 16 || new_node->age > 99){
        printf("Only integers 16-99 are acceptable\n");
        printf("        Enter age of athlete: ");
        scanf("%d", &new_node->age);
    }

    //Athlete gender
    printf("        Enter athlete gender: ");
    scanf(" %c", &new_node->gender);

    if(new_node->gender == 'M' || new_node->gender == 'W' || new_node->gender == 'X' ){
    }else{
        printf("Acceptable characters for gender are W, M, X\n");
        printf("        Enter athlete gender: ");
        scanf(" %c", &new_node->gender);
    }

    new_node->next = cur;
    if(prev == NULL){
        athletes = new_node;
    }else{
        prev->next = new_node;
    }
}

//search_athlete: Prompts the user to enter athlete code, then looks it up. If it exists, print the info, if not print an error
void search_athlete(struct athlete **eVar){
    int code;
    struct athlete *a;

    printf("        Enter athlete code: ");
    scanf("%d", &code);
    a = find_athlete(code);
    if (a != NULL){
        printf("Athlete Code    Athlete Name                  Age                  Gender\n");
        printf("%-15d %-29s %-20d %c\n", a->code, a->name, a->age, a->gender);
    }else{
        printf("Athlete not found.\n");
    }
}

//update_athlete: Updates athlete with new information, similar to inserting an athlete you just change the node
void update_athlete(struct athlete **eVar){
    int code, change;
    struct athlete *a;

    printf("        Enter athlete code: ");
    scanf("%d", &code);
    a = find_athlete(code);
    if (a != NULL){
       //Athlete Name
        printf("        Enter Athlete name: ");
        read_line(a->name, NAME_LEN);

        //Athlete age
        printf("        Enter age of athlete: ");
        scanf("%d", &a->age);

        while(a->age < 16 || a->age > 99){
            printf("Only integers 16-99 are acceptable\n");
            printf("        Enter age of athlete: ");
            scanf("%d", &a->age);
        }

        //Athlete gender
        printf("        Enter athlete gender: ");
        scanf(" %c", &a->gender);

        if(a->gender == 'M' || a->gender == 'W' || a->gender == 'X' ){
        }else{
            printf("Acceptable characters for gender are W, M, X\n");
            printf("        Enter athlete gender: ");
            scanf(" %c", &a->gender);
        }
    }else{
        printf("Athlete not found\n");
    }
}

//print_athlete: prints out each athlete in the list, with all of their info
void print_athlete(struct athlete **eVar){
    struct athlete *a;
    printf("Athlete Code    Athlete Name                  Age                  Gender\n");
    for(a = athletes; a != NULL; a = a->next){
        printf("%-15d %-29s %-20d %c\n", a->code, a->name, a->age, a->gender);
    }
}

//erase_athlete: erases the athlete from the list
void erase_athlete(struct athlete **eVar){
    int code;
    struct athlete *e, *cur, *prev;

    printf("        Enter athlete code: ");
    scanf("%d", &code);

    for(cur = athletes, prev = NULL; cur != NULL && cur->code != code; prev = cur, cur = cur->next);

    if (cur == NULL){
        printf("Error athlete not found");
    }
    if(prev == NULL){
        athletes = athletes->next;
    }else{
        prev->next = cur->next;
    }

    free(cur);
}
