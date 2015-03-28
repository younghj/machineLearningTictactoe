#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <array>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef vector< array<int,9> > gameArray;

struct node{
    int *data; //board
    int *features; //boardTracker
    node *next;
};

struct root{
    int data;
    node *head;
    node *tail;
};

#endif
