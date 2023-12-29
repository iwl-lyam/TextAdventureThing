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

#include "item.h"
#include "location.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>

using namespace item;
using namespace std;

Item::Item(string n, string d) {
    name = std::move(n);
    desc = std::move(d);
    used = false;
}

void item::pickUp(std::string n, location::Location l, std::vector<Item>* i) {
    for (Item* loc : l.items) {
        if (loc->name == n) {
            i->emplace_back(*loc);
        }
    }
}

