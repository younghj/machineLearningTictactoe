#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cstdlib>

using namespace std;

struct node{
    int *board; //board
    int *tracker; //boardTracker
    int *zeros;
    node *next;
};

struct root{
    int data;
    node *head;
    node *tail;
};

#endif
