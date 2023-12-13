//
// Created by Lyam Mosnier on 13/12/2023.
//

#include <string>
#include <iostream>

using namespace std;

#ifndef TEXTADVENTURETHING_ITEM_H
#define TEXTADVENTURETHING_ITEM_H

class Item {
public:

    string name;
    string desc;
    string clue;
    string password;
    string correct;
    string incorrect;

    Item(string n, string d, string c, string p, string co, string ic) {
        name = n;
        desc = d;
        clue = c;
        password = p;
        correct = co;
        incorrect = ic;
    }
};

#endif //TEXTADVENTURETHING_ITEM_H
