#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct node{
    int data;
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

struct trainingSet{
    double y;
    int* features;
    trainingSet* next;
};

int* copyArray(int array[], int length);
void deleteNode(node * dyingNode);
void deleteRoot(root * dyingRoot);

void drawNode(node * outputNode);


#endif
