#include "location.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <functional> // Add this include for std::function
#include <string>     // Add this include for std::string
#include <vector>     // Add this include for std::vector
#include <thread>

using namespace std::chrono;
using std::chrono::system_clock;
using namespace std::this_thread; // sleep_for, sleep_until


using namespace location;

Location::Location(const std::string n, const std::string d) : arrival_set(false), name(n), desc(d), code_req(false) {}
Location::Location(const std::string n, const std::string d, std::function<bool()> f)
            : arrival_set(true), name(n), desc(d), on_arrival(f), code_req(false)  {}
Location::Location(const std::string n, const std::string d, std::function<bool()> f, bool b, float c)
        : arrival_set(true), name(n), desc(d), on_arrival(f), blocked(b), code(c), code_req(true)  {}
Location::Location(const std::string n, const std::string d, std::function<bool()> f, bool b)
: arrival_set(true), name(n), desc(d), on_arrival(f), blocked(b), code_req(false)  {}
Location::Location(const std::string n, const std::string d, std::function<bool()> f, float c)
: arrival_set(true), name(n), desc(d), on_arrival(f), code(c), code_req(true)  {}

Location Location::go(const std::string locName) {
    for (Location* loc : children) {
        if (loc->name == locName) {
            loc->arrival();
            return *loc;
        }
    }
    return children.empty() ? *this : *children.at(0);
}

void Location::setArrival(std::function<bool()> f) {
    on_arrival = f;
    arrival_set = true;
}

bool Location::arrival() const {
    if (arrival_set) {
        return on_arrival();
    } else {
        throw std::runtime_error("Arrival function not set");
    }
}

void Location::unblock() {
    blocked = false;
}

void Location::block() {
    blocked = true;
}

std::string Location::go(const std::string locName, Location* current) {
    std::string init = current->name;
    for (Location* loc : children) {
        if ((loc->name == locName && (loc->blocked == false))) {
            std::cout << "Moving to " + loc->name + "..." << std::endl;
            if (loc->arrival()) {
              sleep_for(1s);
              loc->unblock();
              *current = *loc;
              return "Successfully moved to "+locName;
            } else {
              return "Failed to move to "+locName;
            }
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