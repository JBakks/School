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

struct event{
    int code;
    char name[NAME_LEN];
    int size;
    char gender;
    struct event *next;
};

// struct event *find_event(int code);
// void restore_event(void);
// void dump_event(void);
// void insert_event(void);
// void search_event(void);
// void update_event(void);
// void print_event(void);
// void erase_event(void);
