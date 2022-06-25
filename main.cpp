#include "customErrorClass.h"
#include "bst.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]){
    C_bst bst;

    ifstream myFile;

    int input;
    
    try{
        myFile.open("assign.dat");

    if(myFile.is_open()){
        while(!myFile.eof()){
            myFile >> input;
            bst.insertValue(input);
        }
    }
    bst.sortTree();
    
    myFile.close();
    } catch (MyException &e){
        cout << e.what() << endl;
    }

    return 0;
}