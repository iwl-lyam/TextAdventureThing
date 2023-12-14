//
// Created by Lyam Mosnier on 13/12/2023.
//

#include <string>
#include <iostream>
#include <utility>

using namespace std;

#ifndef TEXTADVENTURETHING_ITEM_H
#define TEXTADVENTURETHING_ITEM_H

class Item {
public:

    string name;
    string desc;
    bool used;

    Item(string n, string d) {
        name = std::move(n);
        desc = std::move(d);
        used = false;
    }

    void use() {
        used = true;
    }
};

#endif //TEXTADVENTURETHING_ITEM_H
