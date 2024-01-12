//
// Created by Lyam Mosnier on 13/12/2023.
//

#ifndef TEXTADVENTURETHING_LOCATION_H
#define TEXTADVENTURETHING_LOCATION_H

#include <vector>
#include <functional>
#include <string>

namespace item {
class Item;  // Forward declaration
}

namespace location {
    class Location {
    private:
        bool arrival_set;

    public:
        bool code_req;
        std::string name;
        std::string desc;
        std::vector<Location*> children;
        std::vector<item::Item*> items;
        float code;
        bool blocked;
        std::function<bool()> on_arrival;

        Location(const std::string n, const std::string d);
        Location(const std::string n, const std::string d, std::function<bool()> f);
        Location(const std::string n, const std::string d, std::function<bool()> f, bool b, float c);
        Location(const std::string n, const std::string d, std::function<bool()> f, bool bc);

        Location(const std::string n, const std::string d, std::function<bool()> f, float c);

        Location go(const std::string locName);
        std::string go(const std::string locName, Location* current);

        void setArrival(std::function<bool()> f);
        bool arrival() const;

        void unblock();
        void block();

        std::vector<Location*> add_loc(Location* loc);
        std::vector<item::Item*> add_item(item::Item* loc);
    };
}

#endif //TEXTADVENTURETHING_LOCATION_H
