//
// Created by Lyam Mosnier on 13/12/2023.
//

#ifndef TEXTADVENTURETHING_ITEM_H
#define TEXTADVENTURETHING_ITEM_H

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <utility>

namespace location {
class Location;  // Forward declaration
}

using namespace std;

//class Item {
//public:
//
//    string name;
//    string desc;
//    bool used;
//
//    Item(string n, string d) {
//        name = std::move(n);
//        desc = std::move(d);
//        used = false;
//    }
//};

namespace item {
    class Item {
    public:
        string name;
        string desc;
        bool used;
        std::function<bool()> handle;
        vector<string> useable;


        Item(string n, string d, std::function<bool()> f, vector<string> u);

        bool use(location::Location loc);
    };

    void pickUp(string n, location::Location l, vector<Item>* i);
}

#endif //TEXTADVENTURETHING_ITEM_H
