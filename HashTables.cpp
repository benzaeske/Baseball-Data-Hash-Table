#include "HashTables.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

HashTables::HashTables(int tSize) {
    tableSize = tSize;
    hashTableCH = new PlayerEntry*[tableSize];
    hashTableOA = new PlayerEntry*[tableSize];
    collisionsCH = 0;
    collisionsOA = 0;
    searchesOA = 0;
    searchesCH = 0;
};

HashTables::~HashTables(){

};

void HashTables::addEntry(string line) {
    string yearS,team,league,playerID,salaryS,firstname,lastname,birthS,country,weightS,heightS,bats,throws;
    int birth,weight,height;
        istringstream tokenStream(line);
        getline(tokenStream,yearS,',');
        getline(tokenStream,team,',');
        getline(tokenStream,league,',');
        getline(tokenStream,playerID,',');
        getline(tokenStream,salaryS, ',');
        getline(tokenStream,firstname,',');
        getline(tokenStream,lastname,',');
        getline(tokenStream,birthS,',');
        getline(tokenStream,country,',');
        getline(tokenStream,weightS,',');
        getline(tokenStream,heightS,',');
        getline(tokenStream,bats,',');
        getline(tokenStream,throws,',');
        birth = stoi(birthS);
        weight = stoi(weightS);
        height = stoi(heightS);
        string key = firstname + lastname;
        string teamData = yearS + "," + team + "," + league + "," + salaryS;
        int index = hashSum(key);

        //Insert algorithm for chaining:

        PlayerEntry *newEntryCH = new PlayerEntry(firstname, lastname, birth, country, weight, height, bats, throws);
        newEntryCH->teams.push_back(teamData);
        if(hashTableCH[index]==NULL) {
            hashTableCH[index] = newEntryCH;
        }
        else {
            searchesCH++;
            if(hashTableCH[index]->birth==birth && hashTableCH[index]->height==height && hashTableCH[index]->firstname==firstname
               && hashTableCH[index]->lastname==lastname) {
                hashTableCH[index]->teams.push_back(teamData);
            }
            else {
                bool collisionCH = true;
                PlayerEntry *tmp = hashTableCH[index];
                while(tmp->next!=NULL) {
                    searchesCH++;
                    if(tmp->next->birth == birth && tmp->next->height == height && tmp->next->firstname == firstname
                       && tmp->next->lastname == lastname) {
                        tmp->next->teams.push_back(teamData);
                        collisionCH=false;
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp->birth == birth && tmp->height == height && tmp->firstname == firstname
                       && tmp->lastname == lastname) {
                        tmp->teams.push_back(teamData);
                        collisionCH=false;
                }
                if(collisionCH) {
                    tmp->next = newEntryCH;
                    collisionsCH++;
                }
            }
        }

        //Insert algorithm for open addressing:

        PlayerEntry *newEntryOA = new PlayerEntry(firstname, lastname, birth, country, weight, height, bats, throws);
        newEntryOA->teams.push_back(teamData);
        if(hashTableOA[index]!=NULL) {
            if(hashTableOA[index]->firstname == firstname && hashTableOA[index]->lastname == lastname
               && hashTableOA[index]->birth==birth) {
                hashTableOA[index]->teams.push_back(teamData);
            }
            else {
                int index2 = index + 1;
                if(index2==tableSize) {
                    index2=0;
                }
                bool collision = true;
                while(hashTableOA[index2]!=NULL) {
                    searchesOA++;
                    if(hashTableOA[index2]->firstname == firstname && hashTableOA[index2]->lastname == lastname
                       && hashTableOA[index2]->birth==birth) {
                        hashTableOA[index2]->teams.push_back(teamData);
                        collision=false;
                        break;
                    }
                    else {
                        if(index2==tableSize) {
                            index2=0;
                        }
                        else if(index2==index) {
                            cout<<"no space"<<endl;
                            break;
                        }
                        else {
                            index2++;
                        }
                    }
                }
                if(collision) {
                    collisionsOA++;
                    hashTableOA[index2] = newEntryOA;
                }
            }
        }
        else {
            hashTableOA[index] = newEntryOA;
        }
};

int HashTables::searchCH(string first, string last) {
    int searches = 0;
    string key = first + last;
    int index = hashSum(key);
    if(hashTableCH[index]!=NULL) {
        if(hashTableCH[index]->firstname==first && hashTableCH[index]->lastname==last) {
            searches++;
            cout<<"First name: "<<hashTableCH[index]->firstname<<endl;
            cout<<"Last name: "<<hashTableCH[index]->lastname<<endl;
            cout<<"Year born: "<<hashTableCH[index]->birth<<endl;
            cout<<"Country born: "<<hashTableCH[index]->country<<endl;
            cout<<"Weight: "<<hashTableCH[index]->weight<<endl;
            cout<<"Height: "<<hashTableCH[index]->height<<endl;
            cout<<"Bats: "<<hashTableCH[index]->bats<<endl;
            cout<<"Throws: "<<hashTableCH[index]->throws<<endl;
            cout<<"Teams and salary:"<<endl;
            for(int i = 0; i < hashTableCH[index]->teams.size(); i++) {
                cout<<hashTableCH[index]->teams[i]<<endl;
            }
        }
        else {
            PlayerEntry *tmp = hashTableCH[index]->next;
            while(tmp!=NULL) {
                searches++;
                if(tmp->firstname==first && tmp->lastname==last) {
                    cout<<"First name: "<<tmp->firstname<<endl;
                    cout<<"Last name: "<<tmp->lastname<<endl;
                    cout<<"Year born: "<<tmp->birth<<endl;
                    cout<<"Country born: "<<tmp->country<<endl;
                    cout<<"Weight: "<<tmp->weight<<endl;
                    cout<<"Height: "<<tmp->height<<endl;
                    cout<<"Bats: "<<tmp->bats<<endl;
                    cout<<"Throws: "<<tmp->throws<<endl;
                    cout<<"Teams and salary:"<<endl;
                    for(int i = 0; i < tmp->teams.size(); i++) {
                            cout<<tmp->teams[i]<<endl;
                    }
                    return searches;
                }
                tmp = tmp->next;
            }
            cout<<"Player not found."<<endl;
        }
    }
    else {
        cout<<"Player not found."<<endl;
    }
    return searches;
};

int HashTables::searchOA(string first, string last) {
    string key = first + last;
    int index = hashSum(key);
    int indexO = index;
    int searches = 0;
    if(hashTableOA[index]==NULL) {
        return 0;
    }
    while(hashTableOA[index]!=NULL) {
        searches++;
        if(hashTableOA[index]->firstname == first && hashTableOA[index]->lastname == last) {
            break;
        }
        index++;
        if(index==tableSize) {
            index=0;
        }
        else if(index==indexO) {
            break;
        }
    }
    return searches;
};

int HashTables::hashSum(string name) {
    int sum = 0;
    for(int i = 0; i < name.size(); i++) {
        sum += name[i];
    }
    sum = sum % tableSize;
    return sum;
};

int HashTables::getCollisionsCH() {
    return collisionsCH;
};

int HashTables::getCollisionsOA() {
    return collisionsOA;
};

int HashTables::getSearchesCH() {
    return searchesCH;
}

int HashTables::getSearchesOA() {
    return searchesOA;
}

int HashTables::getTableSize() {
    return tableSize;
};


