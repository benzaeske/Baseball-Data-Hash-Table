#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "HashTables.h"

using namespace std;

void displayMenu() {
    cout<<"=======Menu======="<<endl;
    cout<<"1. Query hash table"<<endl;
    cout<<"2. Quit program"<<endl;
}

int main(int argc, char* argv[]) {
    //create hash tables:
    char* arg2 = argv[2];
    int tableSize = atoi(arg2);
    HashTables tables = HashTables(tableSize);
    //Begin reading file:
    char* filename = argv[1];
    ifstream inFile;
    inFile.open(filename);
    string line;
    getline(inFile, line);
    while (getline(inFile, line)) {
        tables.addEntry(line);
    }
    cout<<"Hash table size: "<<tables.getTableSize()<<endl;
    cout<<"Collisions using open addressing: "<<tables.getCollisionsOA()<<endl;
    cout<<"Collisions using chaining: "<<tables.getCollisionsCH()<<endl;
    cout<<"Search operations using open addressing: "<<tables.getSearchesOA()<<endl;
    cout<<"Search operations using chaining: "<<tables.getSearchesCH()<<endl;
    cout<<endl;
    int choice = 0;
    while(choice!=2) {
        displayMenu();
        cin >> choice;
        if(choice == 1) {
            string first,last;
            cout<<"Enter the player's first name:"<<endl;
            cin>>first;
            cout<<"Enter the player's last name:"<<endl;
            cin>>last;
            int searchesCH;
            int searchesOA;
            searchesCH = tables.searchCH(first, last);
            searchesOA = tables.searchOA(first, last);
            cout<<"Search operations using chaining: "<<searchesCH<<endl;
            cout<<"Search operations using open addressing: "<<searchesOA<<endl;
        }
        else if(choice == 2) {
            cout<<"Program ended."<<endl;
        }
        else {
            displayMenu();
        }
    }
}
