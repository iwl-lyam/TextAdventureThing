//
// Created by Lyam Mosnier on 13/12/2023.
//

#include <vector>
#include <functional>
#include <string>

namespace item {
class Item;  // Forward declaration
}

#ifndef TEXTADVENTURETHING_LOCATION_H
#define TEXTADVENTURETHING_LOCATION_H

namespace location {
    class Location {
    private:
        bool arrival_set;

    public:
        std::string name;
        std::string desc;
        std::vector<Location*> children;
        std::vector<item::Item*> items;
        bool blocked;
        std::function<void()> on_arrival;

        Location(const std::string n, const std::string d);
        Location(const std::string n, const std::string d, std::function<void()> f);
        Location(const std::string n, const std::string d, std::function<void()> f, bool b);

        Location go(const std::string locName);
        std::string go(const std::string locName, Location* current);

        void setArrival(std::function<void()> f);
        void arrival() const;

        void unblock();
        void block();

        std::vector<Location*> add_loc(Location* loc);
        std::vector<item::Item*> add_item(item::Item* loc);
    };
}

#endif //TEXTADVENTURETHING_LOCATION_H
