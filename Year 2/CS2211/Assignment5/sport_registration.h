//Josh Bakelaar
//251139121
//CS2211
//4/6/2022

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include "readline.h"

#define NAME_LEN 50

struct registration{
    int code;
    int eventCode;
    int athleteCode;
    struct registration *next;
};

// struct registration *find_registration(int code);
// void restore_registration(struct registration **rVar);
// void dump_registration(struct registration **rVar);
// void insert_registration(struct registration **rVar);
// void search_registration(struct registration **rVar);
// void update_registration(struct registration **rVar);
// void print_registration(struct registration **rVar);
// void erase_registration(struct registration **rVar);
