//Josh Bakelaar
//251139121
//CS2211
//4/6/2022

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include "readline.h"

#define NAME_LEN 50

struct athlete{
    int code;
    char name[NAME_LEN];
    int age;
    char gender;
    struct athlete *next;
};

// struct athlete *find_athlete(int code);
// void restore_athlete(struct athlete **aVar);
// void dump_athlete(struct athlete **aVar);
// void insert_athlete(struct athlete **aVar);
// void search_athlete(struct athlete **aVar);
// void update_athlete(struct athlete **aVar);
// void print_athlete(struct athlete **aVar);
// void erase_athlete(struct athlete **aVar);