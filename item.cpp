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
#include <functional>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace item;
using namespace std;

Item::Item(string n, string d, function<bool()> f, vector<string> u) {
    name = std::move(n);
    desc = std::move(d);
    handle = f;
    useable = u;
    used = false;
}

bool Item::use(location::Location loc) {
    auto it = std::find(useable.begin(), useable.end(), loc.name);

    if (it == useable.end()) {
        return false;
    }

    if (handle()) {
        used = true;
    }

    return true;
}

void item::pickUp(std::string n, location::Location l, std::vector<Item>* i) {
    for (Item* loc: l.items) {
        if (loc->name == n) {
            i->emplace_back(*loc);
            loc->used = true;
        }
    }
}

