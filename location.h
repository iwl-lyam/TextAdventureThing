//
// Created by Lyam Mosnier on 13/12/2023.
//

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "item.h"

#ifndef TEXTADVENTURETHING_LOCATION_H
#define TEXTADVENTURETHING_LOCATION_H

class Location {
private:
    bool arrival_set;

public:
    string name;
    string desc;
    vector<Location*> children;
    vector<Item> items;
    function<void()> on_arrival; // Use std::function instead of function pointer

    Location(const string n, const string d) : arrival_set(false), name(n), desc(d) {}

    Location(const string n, const string d, function<void()> f)
            : arrival_set(true), name(n), desc(d), on_arrival(f)  {}

    Location go(const string locName) {
        for (Location* loc : children) {
            if (loc->name == locName)
                return *loc;
        }
        return children.empty() ? *this : *children.at(0);
    }

    void setArrival(function<void()> f) {
        on_arrival = f;
        arrival_set = true;
    }

    void arrival() const {
        if (arrival_set) {
            on_arrival();
        } else {
            throw std::runtime_error("Arrival function not set");
        }
    }

    string go(const string locName, Location* current) {
        string init = current->name;
        for (Location* loc : children) {
            if (loc->name == locName) {
                *current = *loc;
                return "Moving to " + loc->name + "...";
            }
        }
        return "You can't go there.";
    }

    vector<Location*> add_loc(Location* loc) {
        children.push_back(loc);
        return children;
    }

    vector<Item> add_item(Item loc) {
        items.push_back(loc);
        return items;
    }
};

#endif //TEXTADVENTURETHING_LOCATION_H
