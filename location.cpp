#include "location.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <functional> // Add this include for std::function
#include <string>     // Add this include for std::string
#include <vector>     // Add this include for std::vector

using namespace location;

Location::Location(const std::string n, const std::string d) : arrival_set(false), name(n), desc(d) {}
Location::Location(const std::string n, const std::string d, std::function<void()> f)
            : arrival_set(true), name(n), desc(d), on_arrival(f)  {}

Location Location::go(const std::string locName) {
    for (Location* loc : children) {
        if (loc->name == locName)
            return *loc;
    }
    return children.empty() ? *this : *children.at(0);
}

void Location::setArrival(std::function<void()> f) {
    on_arrival = f;
    arrival_set = true;
}

void Location::arrival() const {
    if (arrival_set) {
        on_arrival();
    } else {
        throw std::runtime_error("Arrival function not set");
    }
}

std::string Location::go(const std::string locName, Location* current) {
    std::string init = current->name;
    for (Location* loc : children) {
        if (loc->name == locName) {
            *current = *loc;
            return "Moving to " + loc->name + "...";
        }
    }
    return "You can't go there.";
}

std::vector<Location*> Location::add_loc(Location* loc) {
    children.push_back(loc);
    return children;
}

std::vector<item::Item*> Location::add_item(item::Item* loc) {
    items.push_back(loc);
    return items;
}


//class Location {
//private:
//    bool arrival_set;
//
//public:
//    string name;
//    string desc;
//    vector<Location*> children;
//    vector<Item*> items;
//    function<void()> on_arrival; // Use std::function instead of function pointer
//
//    Location(const string n, const string d) : arrival_set(false), name(n), desc(d) {}
//
//    Location(const string n, const string d, function<void()> f)
//            : arrival_set(true), name(n), desc(d), on_arrival(f)  {}
//
//    Location go(const string locName) {
//        for (Location* loc : children) {
//            if (loc->name == locName)
//                return *loc;
//        }
//        return children.empty() ? *this : *children.at(0);
//    }
//
//    void setArrival(function<void()> f) {
//        on_arrival = f;
//        arrival_set = true;
//    }
//
//    void arrival() const {
//        if (arrival_set) {
//            on_arrival();
//        } else {
//            throw std::runtime_error("Arrival function not set");
//        }
//    }
//
//    string go(const string locName, Location* current) {
//        string init = current->name;
//        for (Location* loc : children) {
//            if (loc->name == locName) {
//                *current = *loc;
//                return "Moving to " + loc->name + "...";
//            }
//        }
//        return "You can't go there.";
//    }
//
//    vector<Location*> add_loc(Location* loc) {
//        children.push_back(loc);
//        return children;
//    }
//
//    vector<Item*> add_item(Item* loc) {
//        items.push_back(loc);
//        return items;
//    }
//};