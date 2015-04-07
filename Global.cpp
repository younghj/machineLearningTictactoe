#include "Global.h"


int* copyArray(int array[], int length){
    int* temp = new int[length];
    for(int i=0; i < length; i++) temp[i]=array[i];
    return temp;
}

void deleteNode(node * dyingNode){
    if(dyingNode->board!=NULL)
        delete dyingNode->board;
    if(dyingNode->tracker!=NULL)
        delete dyingNode->tracker;
    if(dyingNode->zeros!=NULL)
        delete dyingNode->zeros;
    if(dyingNode->next!=NULL)
        deleteNode(dyingNode->next);
    delete dyingNode;
}

void deleteRoot(root * dyingRoot){
    deleteNode(dyingRoot->head);
    delete dyingRoot;
}

void drawNode(node * outputNode){
    cout << "board:" ;
    for(int i=0; i<9;i++) cout << outputNode->board[i] << " ";
    cout << endl;
    cout << "tracker:" ;
    for(int i=0; i<8;i++) cout << outputNode->tracker[i] << " ";
    cout << endl;
    cout << "zeros:" ;
    for(int i=0; i<8;i++) cout << outputNode->zeros[i] << " ";
    cout << endl;
    cout << "set position:" << outputNode->data << endl;

    if(outputNode->next!=NULL){
        cout << "NEXT NODE---------------------" << endl << endl;
        drawNode(outputNode->next);
    }
    else cout << "END NODE" << endl;
}
