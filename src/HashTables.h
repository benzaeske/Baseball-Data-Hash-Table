#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <vector>
#include <string>

using namespace std;

struct PlayerEntry {
    string firstname;
    string lastname;
    int birth;
    string country;
    int weight;
    int height;
    string bats;
    string throws;
    vector<string> teams;
    PlayerEntry *next;

    PlayerEntry(){
    };

    PlayerEntry(string fname, string lname, int b, string c, int w, int h, string ba, string t) {
        firstname = fname;
        lastname = lname;
        birth = b;
        country = c;
        weight = w;
        height = h;
        bats = ba;
        throws = t;
        next = NULL;
    }
};

class HashTables{

    public:
        HashTables(int tSize);
        ~HashTables();
        void addEntry(string line);
        int searchCH(string first, string last);
        int searchOA(string first, string last);
        int hashSum(string name);
        int getCollisionsCH();
        int getCollisionsOA();
        int getSearchesCH();
        int getSearchesOA();
        int getTableSize();

    protected:

    private:
        int tableSize;
        int collisionsCH;
        int collisionsOA;
        int searchesCH;
        int searchesOA;
        PlayerEntry** hashTableCH;
        PlayerEntry** hashTableOA;
};


#endif // HASHTABLES_H
