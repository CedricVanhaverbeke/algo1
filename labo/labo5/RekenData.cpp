//
// Created by Cedric Vanhaverbeke on 2019-06-01.
//
#include <vector>
#include <memory>
#include <iostream>
using std::vector;
using std::pair;
using std::unique_ptr;
using std::ostream;

typedef struct  {
    enum{CHAR, DOUBLE} tag;
    union {
        double getal;
        char operatie;
    };
} RekenData;

ostream& operator<<(ostream & os, RekenData d){
    if(d.tag == d.DOUBLE){
        os << d.getal << " ";
    } else {
        os << d.operatie << " ";
    }
    return os;
}

bool isPlusMinus(char teken){
    return teken == '+' || teken == '-';
}

bool isTimesDevided(char teken){
    return teken == '*' || teken == '/';
}

bool isPower(char teken){
    return teken == '^';
}

bool isHaak(char teken){
    return teken == '(' || teken == ')';
}

bool isOperator(char teken){
    return isPlusMinus(teken) || isTimesDevided(teken) || isPower(teken) || isHaak(teken);
}

// Als de volgorde true is == links naar rechts
// Als de volgorde false is == rechts naar links
void geefVolgorde(vector<pair<RekenData, int>> & volgordeVector, int & plaats, bool volgorde ,std::function<bool (char)> func){
    if(volgorde){
        int i = 0;
        while(i < volgordeVector.size()){

            // Haken gaan we volledig skippen
            // Deze willen we zo lang mogelijk samenhouden
            if(isHaak(volgordeVector[i].first.operatie)){
                i++;
                while(volgordeVector[i].first.tag == volgordeVector[i].first.DOUBLE || !isHaak(volgordeVector[i].first.operatie)) {
                    i++;
                }
            }

            if(volgordeVector[i].first.tag == volgordeVector[i].first.CHAR){
                if(func(volgordeVector[i].first.operatie) ){
                    volgordeVector[i].second = plaats;
                    plaats++;
                }
            }
            i++;
        }
    }
}


